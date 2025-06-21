#ifndef entropy_hpp
#define entropy_hpp

#include <RcppArmadillo.h>

namespace entropy {
    template <typename pk, typename qk>
    class task {
        protected:
        arma::Mat<pk> p_matrix;
        arma::Mat<qk> q_matrix;

        arma::Col<pk> p_vector;
        arma::Col<qk> q_vector;
        arma::Col<double> sample_weights;

        double n_obs;

        public:
        task(const Rcpp::NumericMatrix& actual, const Rcpp::NumericMatrix& response) : 
            p_matrix(const_cast<pk*>(actual.begin()), actual.nrow(), actual.ncol(), false, false),
            q_matrix(const_cast<qk*>(response.begin()), response.nrow(), response.ncol(), false, false) {

                // flatten both matrices
                // NOTE: It might be possible to do 
                // in one step if we just pass pointers
                // to constructors instead
                p_vector = arma::Col<pk>(
                    p_matrix.memptr(),
                    p_matrix.n_elem,
                    false,
                    false
                );

                q_vector = arma::Col<pk>(
                    q_matrix.memptr(),
                    q_matrix.n_elem,
                    false,
                    false
                );

                // calculate number of 
                // observations
                n_obs = p_matrix.n_rows;

            }

        task(const Rcpp::NumericMatrix& actual) : 
            p_matrix(const_cast<pk*>(actual.begin()), actual.nrow(), actual.ncol(), false, false) {

                // flatten both matrices
                // NOTE: It might be possible to do 
                // in one step if we just pass pointers
                // to constructores instead
                p_vector = arma::Col<pk>(
                    p_matrix.memptr(),
                    p_matrix.n_elem,
                    false,
                    false
                );

                // calculate number of 
                // observations
                n_obs = p_matrix.n_rows;

            }

        task(const Rcpp::IntegerVector& actual, const Rcpp::NumericMatrix& response) :
            q_matrix(const_cast<qk*>(response.begin()), response.nrow(), response.ncol(), false, false),
            p_vector(const_cast<pk*>(actual.begin()), actual.size(), false, false) {

                // actual number of observations
                n_obs = actual.size();
                
                // convert values
                p_vector = arma::Col<pk>(p_vector.memptr(), actual.size(), false, false);
                q_matrix = arma::Mat<qk>(q_matrix.memptr(), q_matrix.n_elem, false, false);
                
            }

        task(const Rcpp::IntegerVector& actual, const Rcpp::NumericMatrix& response, const Rcpp::NumericVector& w) :
            q_matrix(const_cast<qk*>(response.begin()), response.nrow(), response.ncol(), false, false),
            p_vector(const_cast<pk*>(actual.begin()), actual.size(), false, false),
            sample_weights(const_cast<double*>(w.begin()), w.size(), false, false) {

                // actual number of observations
                n_obs = actual.size();
                
                // convert values
                p_vector = arma::Col<pk>(p_vector.memptr(), actual.size(), false, false);
                sample_weights = arma::Col<double>(sample_weights.memptr(), sample_weights.size(), false, false);
                q_matrix = arma::Mat<qk>(q_matrix.memptr(), q_matrix.n_elem, false, false);
                
            }

        // constructor for vector vs vector
        task(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response) :
            p_vector(const_cast<pk*>(actual.begin()), actual.size(), false, false),
            q_vector(const_cast<qk*>(response.begin()), response.size(), false, false) {

                // convert vectors
                // to arma vectors
                p_vector = arma::Col<pk>(p_vector.memptr(), p_vector.size(), false, false);
                q_vector = arma::Col<qk>(q_vector.memptr(), q_vector.size(), false, false);

                // calculate number
                // of obs
                n_obs = p_vector.n_elem;

            }

        // constructor for vector vs vector (Weighted)
        task(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, const Rcpp::NumericVector& w) :
            p_vector(const_cast<pk*>(actual.begin()), actual.size(), false, false),
            q_vector(const_cast<qk*>(response.begin()), response.size(), false, false),
            sample_weights(const_cast<double*>(w.begin()), w.size(), false, false) {

                // convert vectors
                // to arma vectors
                p_vector = arma::Col<pk>(p_vector.memptr(), p_vector.size(), false, false);
                q_vector = arma::Col<qk>(q_vector.memptr(), q_vector.size(), false, false);
                sample_weights = arma::Col<double>(sample_weights.memptr(), sample_weights.size(), false, false);

                // calculate number
                // of obs
                n_obs = p_vector.n_elem;

            }


            // virtual Rcpp::NumericVector row(bool normalize = false) const noexcept = 0;
            // virtual Rcpp::NumericVector column(bool normalize = false) const noexcept = 0;
            // virtual Rcpp::NumericVector total(bool normalize = false) const noexcept = 0;
    };
}

#endif