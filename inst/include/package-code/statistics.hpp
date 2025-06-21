#include <RcppArmadillo.h>

namespace statistic {

    template <typename T>
    class quantile {
        public:
        static inline arma::Col<T> unweighted(
            const arma::Col<T>& x, 
            const arma::Col<T>& alpha) {

                return arma::quantile(x, alpha);
        }

        static inline arma::Col<T> weighted(
            const arma::Col<T>& x,
            const arma::Col<T>& w,
            const arma::Col<T>& alpha) {

                arma::uword n = x.n_elem;
                arma::uword m = alpha.n_elem;
                arma::Col<T> res(m, arma::fill::zeros);

                arma::uvec sorted_idx = arma::sort_index(x, "ascend");
                T total_weight = arma::accu(w);

                arma::uvec sorted_alpha_idx = arma::sort_index(alpha, "ascend");
                arma::Col<T> sorted_alpha = alpha(sorted_alpha_idx);


                arma::Col<T> res_sorted(m, arma::fill::zeros);

                T cumulative_weight = 0;
                arma::uword q = 0;
                for (arma::uword i = 0; i < n && q < m; ++i) {
                    arma::uword idx = sorted_idx(i);
                    cumulative_weight += w(idx);

                    while (q < m && cumulative_weight >= sorted_alpha(q) * total_weight) {
                        res_sorted(q) = x(idx);
                        ++q;
                    }
                }

                for (arma::uword j = 0; j < m; ++j) {
                    res(sorted_alpha_idx(j)) = res_sorted(j);
                }

                return res;
        }
    };

    template <typename T>
    class IQR {
        public:
        static inline T unweighted(const arma::Col<T>& x) {
            arma::Col<T> alpha = { static_cast<T>(0.25), static_cast<T>(0.75) };
            arma::Col<T> q = quantile<T>::unweighted(x, alpha);
            return q(1) - q(0);
        }

        static inline T weighted(
            const arma::Col<T>& x, 
            const arma::Col<T>& w) {
                arma::Col<T> alpha = { static_cast<T>(0.25), static_cast<T>(0.75) };
                arma::Col<T> q = quantile<T>::weighted(x, w, alpha);
                return q(1) - q(0);
        }
    };

    template <typename T>
    class range {
    public:

        static inline T unweighted(const arma::Col<T>& x) {
        return arma::max(x) - arma::min(x);
        }

        static inline T weighted(const arma::Col<T>& x, const arma::Col<T>& w) {
        return arma::max(x % w) - arma::min(x % w);
        }
    };
}