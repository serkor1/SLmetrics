#ifndef CLASSIFICATION_PRECISIONRECALLCURVE_H
#define CLASSIFICATION_PRECISIONRECALLCURVE_H

#include "SLmetrics.h"
#include <vector>
#include <optional>

namespace metric {

    /**
     * @class precision_recall_curve
     * @brief Calculates precision-recall curves and AUC (average precision).
     *        Inherits most machinery (sorting, flattening, integration) from
     *        classification::curve_base.
     */
    class precision_recall_curve : public classification::curve_base {
        using base = classification::curve_base;
    public:
        using base::base;

        // --- class-wise Average Precision (area under PR curve) ---
        Rcpp::NumericVector class_wise() override {
            arma::uword K = this->n_cols_;
            Rcpp::NumericVector aps(K);
            aps.attr("names") = this->class_levels_;

            for (arma::uword c = 0; c < K; ++c) {
                arma::uvec order = sort_index(c);
                double tp = 0.0, fp = 0.0;
                double prev_rec = 0.0, prev_prec = 1.0;
                double ap = 0.0;

                // total positives (weighted)
                double P = 0.0;
                for (arma::uword i = 0; i < n_rows_; ++i) {
                    if (actual_ptr[i] == static_cast<int>(c + 1)) {
                        P += (weights_ptr ? weights_ptr[i] : 1.0);
                    }
                }
                if (P == 0.0) {
                    aps[c] = NA_REAL;
                    continue;
                }

                for (arma::uword idx : order) {
                    double w = weights_ptr ? weights_ptr[idx] : 1.0;
                    if (actual_ptr[idx] == static_cast<int>(c + 1)) {
                        tp += w;
                    } else {
                        fp += w;
                    }
                    double rec  = tp / P;
                    double prec = tp / (tp + fp);
                    ap += integration_fn_(prev_rec, prev_prec, rec, prec);
                    prev_rec  = rec;
                    prev_prec = prec;
                }
                aps[c] = ap;
            }
            return aps;
        }

        // --- micro-averaged average precision ---
        double micro_average() override {
            arma::mat all = flatten_all_mat();
            arma::colvec is_pos = all.col(1);
            arma::colvec wts    = all.col(2);

            double P = arma::dot(is_pos, wts);
            if (P == 0.0) return Rcpp::NumericVector::get_na();

            double tp = 0.0, fp = 0.0;
            double prev_rec = 0.0, prev_prec = 1.0;
            double ap = 0.0;

            for (arma::uword i = 0; i < all.n_rows; ++i) {
                double w = wts[i];
                if (is_pos[i] > 0.5) tp += w;
                else              fp += w;

                double rec  = tp / P;
                double prec = tp / (tp + fp);
                ap += integration_fn_(prev_rec, prev_prec, rec, prec);
                prev_rec  = rec;
                prev_prec = prec;
            }
            return ap;
        }

        // curve: returns a DataFrame with (threshold, level, label, recall, precision)
        Rcpp::DataFrame curve(const std::optional<Rcpp::NumericVector>& th_in) override {
            const R_xlen_t per_class = th_in ? (th_in->size() + 2) 
                                              : (n_rows_ + 2);
            const R_xlen_t total     = per_class * n_cols_;

            Rcpp::NumericVector thr(total), rec(total), prec(total);
            Rcpp::IntegerVector    lvl(total);
            Rcpp::CharacterVector  lbl(total);

            R_xlen_t pos = 0;
            for (arma::uword c = 0; c < n_cols_; ++c) {
                arma::uvec order = sort_index(c);
                const std::size_t M = th_in ? (th_in->size() + 2) 
                                            : (order.n_elem + 2);

                arma::Col<double> tp(M, arma::fill::zeros),
                                   fp(M, arma::fill::zeros),
                                   cuts(M);

                // +Inf start
                tp[0] = 0; fp[0] = 0; cuts[0] = R_PosInf;

                if (th_in) {
                    arma::uword j = 0;
                    for (std::size_t i = 1; i < M-1; ++i) {
                        double cut = (*th_in)[i-1];
                        while (j < order.n_elem &&
                               response_ptr[c*n_rows_ + order[j]] >= cut) {
                            double w = weights_ptr ? weights_ptr[order[j]] : 1.0;
                            if (actual_ptr[order[j]] == int(c+1)) tp[i] += w;
                            else                                  fp[i] += w;
                            ++j;
                        }
                        tp[i]   = tp[i-1];
                        fp[i]   = fp[i-1];
                        cuts[i] = cut;
                    }
                } else {
                    for (std::size_t i = 1; i < M-1; ++i) {
                        arma::uword idx = order[i-1];
                        double w        = weights_ptr ? weights_ptr[idx] : 1.0;
                        tp[i]   = tp[i-1] + (actual_ptr[idx] == int(c+1) ? w : 0.0);
                        fp[i]   = fp[i-1] + (actual_ptr[idx] != int(c+1) ? w : 0.0);
                        cuts[i] = response_ptr[c*n_rows_ + idx];
                    }
                }

                // -Inf end
                tp[M-1] = tp[M-2];
                fp[M-1] = fp[M-2];
                cuts[M-1] = R_NegInf;

                // total positives for normalization
                double P = tp.back();

                for (std::size_t i = 0; i < M; ++i) {
                    thr[pos] = cuts[i];
                    rec[pos] = (P > 0.0 ? tp[i] / P : 0.0);
                    prec[pos] = (tp[i] + fp[i] > 0.0 ? tp[i] / (tp[i] + fp[i]) : 1.0);
                    lvl[pos] = c + 1;
                    lbl[pos] = class_levels_[c];
                    ++pos;
                }
            }

            Rcpp::DataFrame out = Rcpp::DataFrame::create(
                Rcpp::Named("threshold") = thr,
                Rcpp::Named("level")     = lvl,
                Rcpp::Named("label")     = lbl,
                Rcpp::Named("recall")    = rec,
                Rcpp::Named("precision") = prec
            );
            out.attr("class") = Rcpp::CharacterVector::create("prROC", "data.frame");
            return out;
        }
    };

} // namespace metric

#endif // CLASSIFICATION_PRECISIONRECALLCURVE_H
