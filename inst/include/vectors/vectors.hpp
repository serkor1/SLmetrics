
/*
 * https://stackoverflow.com/questions/18804402/add-a-method-to-existing-c-class-in-other-file
 */
#include <armadillo>
#include <Rcpp.h>

namespace vctr {

    template <typename T>
    struct rcpp_vector;

    template <>
    struct rcpp_vector <double> {
        typedef Rcpp::NumericVector R_vctr ;
    };

    template <>
    struct rcpp_vector <int> {
        typedef Rcpp::IntegerVector R_vctr ;
    };

    // define alias
    typedef arma::Col<double> dbl_vctr;
    typedef arma::Col<int> int_vctr;

    template <typename T>
    class vctr_class : public arma::Col<T> {
        public:

        // inherit constructers from
        // arma::Col<T>
        using arma::Col<T>::Col;

        //operator const arma::Col<T>&() const { return *this; }

        // convert to arma::Col
        vctr_class(const typename rcpp_vector<T>::R_vctr& x)
            : arma::Col<T>(const_cast<T*>(x.begin()), x.size(), false, false) {}

    };


};



// namespace vctr {

//     template <typename T>
//     struct rcpp_vector;

//     template <>
//     struct rcpp_vector <double> {
//         typedef Rcpp::NumericVector R_vctr ;
//     };

//     template <>
//     struct rcpp_vector <int> {
//         typedef Rcpp::IntegerVector R_vctr ;
//     };


//     template <typename T>
//     class vctr_class : public arma::Col<T> {
//         public:

//         // inherit constructers from
//         // arma::Col<T>
//         using arma::Col<T>::Col;

//         //operator const arma::Col<T>&() const { return *this; }

//         // convert to arma::Col
//         vctr_class(const typename rcpp_vector<T>::R_vctr& x)
//             : arma::Col<T>(const_cast<T*>(x.begin()), x.size(), false, false) {}

//         // sort vector
//         vctr_class& sort() {
//             // 0) sort the vector
//             // and store
//             *this = vctr_class<T> (
//                 arma::sort(static_cast<const arma::Col<T>&>( *this ))
//             );

//             return *this;
//         }

//         // mean vector
//         // NOTE: Has to be with and
//         // without OpenMP
//         double mean() const {
//             return arma::mean(
//                     static_cast<const arma::Col<T>&>(*this)
//                 );
//         }

//         // var vector
//         // NOTE: Has to be with and
//         // without OpenMP
//         double var() const {
//             return arma::var(
//                     static_cast<const arma::Col<T>&>(*this)
//                 );
//         }

//     }; // end of vctr_class

//       // Operands
//     template <typename T>
//      arma::Col<T> operator-(const vctr_class<T>& lhs, const vctr_class<T>& rhs) {
//         return  static_cast<const arma::Col<T>&>(lhs) - static_cast<const arma::Col<T>&>(rhs);
//     }

//     template <typename T>
//      arma::Col<T> operator+(const vctr_class<T>& lhs, const vctr_class<T>& rhs) {
//         return  static_cast<const arma::Col<T>&>(lhs) + static_cast<const arma::Col<T>&>(rhs);
//     }

//     template <typename T>
//     inline T dot(const vctr_class<T>& a, const vctr_class<T>& b) {
//         return arma::dot(static_cast<const arma::Col<T>&>(a),
//                          static_cast<const arma::Col<T>&>(b));
//     }

//     // type alias for common
//     // classes
//     using dbl_vctr = vctr_class<double>;
//     using int_vctr = vctr_class<int>;
// }