#ifndef CLASSIFICATION_RECEIVEROPERATORCURVE_H
#define CLASSIFICATION_RECEIVEROPERATORCURVE_H

#include "SLmetrics.h"
#include <vector>
#include <optional>

namespace metric {
    /**
     * @class roc_curve
     * @brief This class calculates the AUC and constructs the
     * Receiver Operating Characteristics curve. It currently supports
     * micro and macro averages.
     * 
     * The underlying algorithm is One vs Rest
     *
     * @todo Explicit handling of NaN similar to na.rm.
     */
    class roc_curve : public classification::curve_base {
        using base = classification::curve_base;
        public:
        // inherit the base constructor
        using base::base;

        // class-wise AUC
        Rcpp::NumericVector class_wise() override {
            arma::uword K = this -> n_cols_;
            Rcpp::NumericVector aucs(K);
            aucs.attr("names") = this -> class_levels_;

            for (arma::uword c = 0; c < K; ++c) {
                arma::uvec order = this->sort_index(c);

                double tp = 0.0, fp = 0.0;
                double prev_tp = 0.0, prev_fp = 0.0;
                double raw_area = 0.0;

                for (arma::uword idx : order) {
                    double w = weights_ptr ? weights_ptr[idx] : 1.0;
                    if (actual_ptr[idx] == static_cast<int>(c+1)) {
                        tp += w;
                    } else {
                        fp += w;
                    }
                    raw_area += integration_fn_(prev_fp, prev_tp, fp, tp);
                    prev_fp = fp;
                    prev_tp = tp;
                }

                double P = tp;
                double N = fp;
                if (P == 0.0 || N == 0.0) {
                    aucs[c] = NA_REAL;
                } else {
                    aucs[c] = raw_area / (P * N);
                }
            }

            return aucs;
        }

        // micro-averaged AUC
       double micro_average() override {
            arma::mat all = this -> flatten_all_mat();
            arma::colvec is_pos = all.col(1);
            arma::colvec wts    = all.col(2);

            double P = arma::dot(is_pos, wts);
            double N = arma::dot(arma::ones<arma::colvec>(is_pos.n_elem) - is_pos, wts);
            if (P == 0.0 || N == 0.0) return Rcpp::NumericVector::get_na();

            double tp = 0.0, fp = 0.0;
            double prev_tpr = 0.0, prev_fpr = 0.0;
            double auc = 0.0;

            for (arma::uword i = 0; i < all.n_rows; ++i) {
                double w = wts[i];
                if (is_pos[i] > 0.5) tp += w; else fp += w;

                double tpr = tp / P;
                double fpr = fp / N;
                auc += integration_fn_(prev_fpr, prev_tpr, fpr, tpr);
                prev_fpr = fpr;
                prev_tpr = tpr;
            }
            return auc;
        }

        Rcpp::DataFrame curve(const std::optional<Rcpp::NumericVector>& th_in) override {
            
            // 1) calculate total lengths
            // based on thresholds
            const R_xlen_t per_class = th_in ? (th_in -> size() + 2) : (n_rows_ + 2);
            const R_xlen_t total     = per_class * n_cols_;

            // 2) preallocate R outputs
            Rcpp::NumericVector thr(total), tpr(total), fpr(total);
            Rcpp::IntegerVector    lvl(total);
            Rcpp::CharacterVector  lbl(total);

            R_xlen_t pos = 0;
            for (arma::uword c = 0; c < n_cols_; ++c) {
                // 2.1) sort values
                arma::uvec order = sort_index(c);

                // 2.2) Determine exact buffer length: +Inf, thresholds..., -Inf
                // NOTE: Might be redundant.
                const std::size_t M = th_in ? (th_in -> size() + 2) : (order.n_elem + 2);

                // 2.3) initialize vectors
                arma::Col<double> raw_tp(M), raw_fp(M), cuts(M);

                // 2.4) Initialize first point at +Inf
                raw_tp[0] = 0.0;
                raw_fp[0] = 0.0;
                cuts[0] = R_PosInf;

                // 2.4) accumulate conditionally
                // on threshold values
                if (th_in) {
                    // 2.4.a)
                    arma::uword j = 0;
                    for (std::size_t i = 1; i < M-1; ++i) {
                        double cut = (*th_in)[i-1];
                        // accumulate all scores >= cut
                        while (j < order.n_elem &&
                               response_ptr[c*n_rows_ + order[j]] >= cut) {
                            double w = weights_ptr ? weights_ptr[order[j]] : 1.0;
                            if (actual_ptr[order[j]] == int(c+1)) raw_tp[i] += w;
                            else                                   raw_fp[i] += w;
                            ++j;
                        }
                        raw_tp[i] = raw_tp[i-1];
                        raw_fp[i] = raw_fp[i-1];
                        cuts   [i] = cut;
                    }
                } else {
                    // 2.4.b)
                    for (std::size_t i = 1; i < M-1; ++i) {
                        arma::uword idx = order[i-1];
                        double w = weights_ptr ? weights_ptr[idx] : 1.0;
                        raw_tp[i] = raw_tp[i-1] + (actual_ptr[idx] == int(c+1) ? w : 0.0);
                        raw_fp[i] = raw_fp[i-1] + (actual_ptr[idx] != int(c+1) ? w : 0.0);
                        cuts[i] = response_ptr[c*n_rows_ + idx];
                    }
                }

                // 2.5) final point at (1,1) with threshold = -Inf
                raw_tp[M-1] = raw_tp[M-2];
                raw_fp[M-1] = raw_fp[M-2];
                cuts   [M-1] = R_NegInf;

                // 2.6) Normalize and fill R outputs
                const double P = raw_tp.back();
                const double N = raw_fp.back();
                for (std::size_t i = 0; i < M; ++i) {
                    thr[pos] = cuts[i];
                    tpr[pos] = (P > 0.0 ? raw_tp[i] / P : 0.0);
                    fpr[pos] = (N > 0.0 ? raw_fp[i] / N : 0.0);
                    lvl[pos] = c + 1;
                    lbl[pos] = class_levels_[c];
                    ++pos;
                }
            }

            // 3) Return DataFrame
            // with class attributes
            Rcpp::DataFrame output = Rcpp::DataFrame::create(
                Rcpp::Named("threshold") = thr,
                Rcpp::Named("level")     = lvl,
                Rcpp::Named("label")     = lbl,
                Rcpp::Named("fpr")       = fpr,
                Rcpp::Named("tpr")       = tpr
            );
            output.attr("class") = Rcpp::CharacterVector::create("ROC","data.frame");

            return output;
        }

    };

} // namespace metric

#endif // CLASSIFICATION_RECEIVEROPERATORCURVE_H
