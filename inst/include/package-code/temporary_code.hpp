#include <armadillo>
#include <Rcpp.h>
#include <optional>
#include <functional>

namespace classification {

    // Aggregation levels for AUC computation
    enum class aggregation_level : int {
        CLASS_WISE = 0,
        MICRO      = 1,
        MACRO      = 2
    };

    // Integration methods for area calculation
    enum class integration_method : int {
        TRAPEZOIDAL = 0,
        STEP        = 1
    };

    class curve_base {
    protected:
        // Raw data
        arma::Col<int> actual_;
        arma::mat response_;
        std::optional<arma::Col<double>> weights_;
        std::optional<arma::Mat<int>> indices_;

        // Pointers
        const int*    __restrict__ actual_ptr     = nullptr;
        const double* __restrict__ response_ptr   = nullptr;
        const double* __restrict__ weights_ptr    = nullptr;
        const int*    __restrict__ indices_ptr    = nullptr;

        // Dimensions and
        // settings
        arma::uword   n_rows_;
        arma::uword   n_cols_;
        bool          is_sorted_;
        Rcpp::CharacterVector class_levels_;
        std::function<double(double,double,double,double)> integration_fn_;

        // Compute a sort‐index for one column
        arma::uvec sort_index(arma::uword col) {
            if (is_sorted_) {
                // already provided in indices_
                arma::Col<int> tmp = indices_->col(col);
                return arma::conv_to<arma::uvec>::from(tmp) - 1;
            }
            return arma::sort_index(response_.col(col), "descend");
        }

        // Flatten into (score, is_pos, weight) triplets across all classes
        arma::mat flatten_all_mat() {
            // 1) Vector of all scores
            arma::Col<double> scores = arma::vectorise(response_);

            // 2a) Broadcast actual labels across cols
            arma::Mat<int> labels_i = arma::repmat(actual_, /*n_rows=*/1, /*n_cols=*/n_cols_);

            // 2b) class indices 1..K, expanded to each row
            arma::Row<int>           class_i     = arma::linspace<arma::Row<int>>(1, n_cols_, n_cols_);
            arma::Mat<int>           class_i_mat = arma::repmat(class_i, /*n_rows=*/n_rows_, /*n_cols=*/1);

            // 2c) mask positives
            arma::Mat<arma::uword> is_pos_i    = (labels_i == class_i_mat);
            arma::Col<double>      is_pos      = arma::conv_to<arma::Col<double>>::from(
                                                    arma::vectorise(is_pos_i)
                                                );

            // 3) Expand weights
            arma::Col<double> base_w = weights_
                                    ? *weights_
                                    : arma::Col<double>(n_rows_, arma::fill::ones);
            arma::Mat<double> wmat   = arma::repmat(base_w, /*n_rows=*/1, /*n_cols=*/n_cols_);
            arma::Col<double> weights = arma::vectorise(wmat);

            // 4) Build output matrix
            arma::mat out(scores.n_elem, /*n_cols=*/3);
            out.col(0) = scores;
            out.col(1) = is_pos;
            out.col(2) = weights;

            // 5) Sort by descending score
            arma::uvec idx = arma::sort_index(scores, "descend");
            return out.rows(idx);
        }

        // arma::mat flatten_all_mat() {
        //     // 1) Vector of all scores
        //     arma::Col<double> scores = arma::vectorise(response_);

        //     // 2a) Broadcast actual labels across cols
        //     arma::Mat<int> labels_i = arma::repmat(actual_, /*n_rows=*/1, /*n_cols=*/n_cols_);
        //     // 2b) class indices 1..K
        //     arma::Row<int> class_i = arma::linspace<arma::Row<int>>(1, n_cols_, n_cols_);
        //     // 2c) mask positives
        //     arma::Mat<arma::uword> is_pos_i = (labels_i == class_i);
        //     arma::Col<double>      is_pos   = arma::conv_to<arma::Col<double>>::from(
        //                                         arma::vectorise(is_pos_i)
        //                                     );

        //     // 3) Expand weights
        //     arma::Col<double> base_w = weights_
        //                                ? *weights_
        //                                : arma::Col<double>(n_rows_, arma::fill::ones);
        //     arma::Mat<double> wmat   = arma::repmat(base_w, /*n_rows=*/1, /*n_cols=*/n_cols_);
        //     arma::Col<double> weights = arma::vectorise(wmat);

        //     // 4) Build output matrix
        //     arma::mat out(scores.n_elem, /*n_cols=*/3);
        //     out.col(0) = scores;
        //     out.col(1) = is_pos;
        //     out.col(2) = weights;

        //     // 5) Sort by descending score
        //     arma::uvec idx = arma::sort_index(scores, "descend");
        //     return out.rows(idx);
        // }

    public:
        curve_base(
            const Rcpp::IntegerVector&      actual,
            const Rcpp::NumericMatrix&      response,
            integration_method              method,
            std::optional<Rcpp::NumericVector> weights  = std::nullopt,
            std::optional<Rcpp::IntegerMatrix> indices = std::nullopt
        )
        : actual_(const_cast<int*>(actual.begin()), actual.size(), /*copy_aux_mem*/false, /*strict*/false),
          response_(const_cast<double*>(response.begin()), response.nrow(), response.ncol(), false, false),
          n_rows_(actual.size()),
          n_cols_(response.ncol()),
          class_levels_(actual.attr("levels"))
        {
            // Pointers to raw data
            actual_ptr   = actual_.memptr();
            response_ptr = response_.memptr();

            // Optional weights
            if (weights) {
                weights_.emplace(weights -> begin(), weights -> size(), false, false);
                weights_ptr = weights_ -> memptr();
            }

            // Optional indices
            if (indices) {
                indices_.emplace(indices -> begin(), indices -> nrow(), indices -> ncol(), false, false);
                indices_ptr = indices_ -> memptr();
            }

            is_sorted_ = indices_.has_value();

            // Pick integration function
            if (method == integration_method::TRAPEZOIDAL) {
                integration_fn_ = [](double x1, double y1, double x2, double y2) {
                    return (x2 - x1) * 0.5 * (y1 + y2);
                };
            } else {
                integration_fn_ = [](double x1, double /*y1*/, double x2, double y2) {
                    return (x2 - x1) * y2;
                };
            }
        }

        virtual ~curve_base() = default;

        // Pure virtuals to implement in subclasses:
        virtual Rcpp::NumericVector class_wise() = 0;
        virtual double micro_average() = 0;
        virtual Rcpp::DataFrame curve(const std::optional<Rcpp::NumericVector>& thresholds) = 0;

        // Macro‐average computed from class‐wise AUCs
        double macro_average() {
            Rcpp::NumericVector auc_values = class_wise();
            double sum = 0.0;
            int    n   = 0;
            for (double v : auc_values) {
                sum += v;
                ++n;
            }
            return (n > 0 ? sum / n : 0.0);
        }
    };

} // namespace classification