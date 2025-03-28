#ifndef regression_tasks_hpp
#define regression_tasks_hpp

#include <armadillo>
#include <Rcpp.h>
#include "templates.hpp"

namespace regression {
    template <typename T>
    class task {
    protected:
        arma::Col<T> actual_;
        arma::Col<T> predicted_;
        
    public:
        task(const vctr_t<T>& actual, const vctr_t<T>& predicted)
        : actual_(
              const_cast<T*>(actual.begin()),
              actual.size(),
              false,
              false
          )
        , predicted_(
              const_cast<T*>(predicted.begin()),
              predicted.size(),
              false,
              false
          )
        {}
        
        virtual ~task() = default;
        

        const arma::Col<T>& actual() const { return actual_; }
        const arma::Col<T>& predicted() const { return predicted_; }
        
        virtual T compute() const = 0;
    };
}

#endif