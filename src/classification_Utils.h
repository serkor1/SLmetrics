#ifndef CLASSIFICATION_HELPERS_H
#define CLASSIFICATION_HELPERS_H

#include <Rcpp.h>
#include <Eigen/Dense>

class classification {
public:

    /*
        Note to future self:
            
            1.) These are just signatures. So in essence it doesn't matter
            what you call them. The imporant thing is that they are distinguishable

            2.) All functions have the same signature
                2.1) A Matrix (passed via helpers)
                2.2) Booleans to determine behaviour inside
                the respective functions. For example:
                    + boolean 1: Controls missing values
                    + boolean 2: Controls wether  micro/macro values are
                    to be rerrturned
                    + boolean k: Other behaviour that I can't think of as of now.

            It seems somewhat redundant and excessive to do it like this, but until a better
            solution is found, this is what we do.

            Warning: ALL signatures has to be used (I think)
    */

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const {
        return Rcpp::NumericVector();
    };
    
    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro, bool na_rm) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool do_micro, bool na_rm, double beta) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm, double beta) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta, bool na_rm) const {
        return Rcpp::NumericVector();
    };

    virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, double beta, bool do_micro, bool na_rm) const {
        return Rcpp::NumericVector();
    };

    virtual ~classification() = default;
};

#endif // CLASSIFICATION_HELPERS_H
