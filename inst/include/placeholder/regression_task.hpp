/**
 * @file regression_tasks.hpp
 * @brief Declarations for regression tasks and their base class `task`.
 *
 * This file contains the definition of the abstract base template class 
 * `regression::task`, which provides an interface for computing error metrics
 * in regression problems. Derived classes must implement the `compute()` 
 * function, which calculates the specific error metric.
 */
#ifndef regression_tasks_hpp
#define regression_tasks_hpp

#include <armadillo>
#include <Rcpp.h>
#include "templates.hpp"

namespace regression {
    /**
     * @class task
     * @brief An abstract base class that encapsulates the common interface for regression tasks.
     *
     * This class holds references to the actual and predicted values (as Armadillo columns)
     * and provides the interface for computing a metric via the purely virtual function 
     * `compute()`. Concrete metric classes (e.g. RMSE, MSE, etc.) should inherit from 
     * this class and implement the `compute()` method.
     *
     * @tparam T Numeric type, typically `double` or `int`.
     */
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