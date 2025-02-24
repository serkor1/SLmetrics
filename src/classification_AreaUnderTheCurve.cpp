#include "classification_AreaUnderTheCurve.h"
#include <Rcpp.h>

using namespace Rcpp;

//' @rdname roc.auc
//' @method roc.auc numeric
//' @export
// [[Rcpp::export(roc.auc.numeric)]]
Rcpp::NumericVector roc_auc(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response,
    int method = 0,
    bool ordered = false) {
        
        // Basic checks
        std::size_t n = actual.size();
        if (n == 0 || n != (std::size_t)response.size()) {
            Rcpp::stop("'actual' and 'response' must have the same non-zero length.");
        }

        Rcpp::CharacterVector levels = actual.attr("levels");
        int n_classes = levels.size();
        Rcpp::NumericVector output(n_classes, R_NaReal);

        // 1) Prepare idx
        std::vector<std::size_t> idx = prepare_index(response, ordered);

        // 2) Pick area update function pointer once
        double (*updateArea)(double,double,double,double) 
            = (method == 0) ? trapeziod_area : step_area;

        // 3) For each class => one-vs.-rest
        const int* ptr_actual = actual.begin();
        for (int c = 0; c < n_classes; ++c) {
            int class_label = c + 1;
            // Count positives
            double positives = count_positives(actual, idx, class_label);
            double negatives = n - positives;
            if (positives == 0.0 || negatives == 0.0) {
            // AUC undefined if no positives or no negatives
            continue; 
            }

            double area     = 0.0;
            double tp       = 0.0;
            double fp       = 0.0;
            double prev_tpr = 0.0;
            double prev_fpr = 0.0;

            for (std::size_t i = 1; i <= n; i++) {
            std::size_t id = idx[i - 1];
            if (ptr_actual[id] == class_label) {
                tp += 1.0;
            } else {
                fp += 1.0;
            }
            double cur_tpr = (tp / positives);
            double cur_fpr = (fp / negatives);

            area += updateArea(prev_fpr, prev_tpr, cur_fpr, cur_tpr);

            prev_tpr = cur_tpr;
            prev_fpr = cur_fpr;
            }

            output[c] = area;
        }

        // optional: name the output
        output.attr("names") = levels;
        return output;

}

//' @rdname roc.auc
//' @method roc.auc matrix
//' @export
// [[Rcpp::export(roc.auc.matrix)]]
Rcpp::NumericVector roc_auc_matrix(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    int method = 0,
    bool ordered = false) {
        /*
            Note to future self:
                - This function was originally running on 380ms on 1e6 rows, and three
                classes with 0 memory usage. It currently runs around 280ms with 2-3kb of memory usage.
                However, before predefining n and passing actual as pointers
                in the helpers, the runtime was around 250ms with 0 memory usage.

                So therefore it should be possible to optimize it further. The most important part is that it runs
                faster than using vapply with roc.auc.numeric with this current setup.
        */
        
        // 1) extract global variables
        // and pointers

        // 1.1) size of the actual
        // vector
        const std::size_t& n = actual.size();

        // 1.2) class labels and numbers
        Rcpp::CharacterVector levels = actual.attr("levels");
        const int& n_classes = levels.size();

        // 1.3) determine AUC calculation
        // method
        double (*updateArea)(double,double,double,double) 
            = (method == 0) ? trapeziod_area : step_area;
        
        // 1.4) output vector
        Rcpp::NumericVector output(n_classes, 0.0);

        // 1.5) pointer to the actual
        // vector
        const int* ptr_actual = actual.begin();

        // 2) calculate TPR/FPR
        // for each class
        for (int c = 0; c < n_classes; ++c) {

            // 2.1) create a pointer to 
            // the sorted indices
            std::unique_ptr<std::size_t[]> idx_ptr = prepare_index(response, c, n, ordered);

            // 2.2) count number of
            // of positives and derived
            // negatives
            //
            // NOTE: Factors are 1-indexed, 
            // C++ is 0-indexed
            int class_label = c + 1;
            double positives = count_positives(ptr_actual, idx_ptr.get(), n, class_label);
            double negatives = n - positives;

            // 2.2.1) if positives and negatives
            // are 0, the AUC is undefined;
            // return NA and skip iteration
            if (positives == 0.0 || negatives == 0.0) {
                output[c] = NA_REAL;
                continue;
            }

            // 2.3) calculate
            // AUC by streaming.
            //
            // NOTE: This is much more efficient
            // than looping through all values, then looping
            // through again for the AUC. 
            //
            // So we do not re-use the AUC class. We **could** potentially
            // it, but then we would need to constantly check for method.
            // But that is ineffcient, just trust me bro.
            double area = 0.0;
            double tp = 0.0;
            double fp = 0.0;
            double prev_tpr = 0.0;
            double prev_fpr = 0.0;

            for (std::size_t i = 1; i <= n; i++) {
                std::size_t id = idx_ptr[i - 1];

                if (ptr_actual[id] == class_label) {
                    tp += 1.0;
                } else {
                    fp += 1.0;
                }

                double cur_tpr = tp / positives;
                double cur_fpr = fp / negatives;
                area += updateArea(prev_fpr, prev_tpr, cur_fpr, cur_tpr);
                prev_tpr = cur_tpr;
                prev_fpr = cur_fpr;
            }
            
            // 2.4) store AUC in
            // in the output vector
            output[c] = area;
        }

        // 3) add names to the
        // out and return
        output.attr("names") = levels;
        return output;
}


//' @rdname roc.auc
//' @method weighted.roc.auc numeric
//' @export
// [[Rcpp::export(weighted.roc.auc.numeric)]]
Rcpp::NumericVector weighted_roc_auc(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response,
    const Rcpp::NumericVector& w,
    int method = 0,
    bool ordered = false) {
        
        // Basic checks
        std::size_t n = actual.size();
        if (n == 0 || n != (std::size_t)response.size() || n != (std::size_t)w.size()) {
            Rcpp::stop("'actual', 'response', and 'w' must have the same non-zero length.");
        }

        Rcpp::CharacterVector levels = actual.attr("levels");
        int n_classes = levels.size();
        Rcpp::NumericVector output(n_classes, R_NaReal);

        // 1) Prepare idx
        std::vector<std::size_t> idx = prepare_index(response, ordered);

        // 2) Pick area update function pointer once
        double (*updateArea)(double,double,double,double)
            = (method == 0) ? trapeziod_area : step_area;

        // 3) For each class => one-vs.-rest
        const int*    ptr_actual  = actual.begin();
        const double* ptr_w = w.begin();
        double total_weight = std::accumulate(ptr_w, ptr_w + n, 0.0);
        

        for (int c = 0; c < n_classes; ++c) {
            int class_label = c + 1;

            // Weighted count of positives
            double positives = count_positives(actual, w, idx, class_label);
            // Weighted count of negatives = total weight - positives
            double negatives = total_weight - positives;

            if (positives == 0.0 || negatives == 0.0) {
            continue;
            }

            double area     = 0.0;
            double tp       = 0.0;
            double fp       = 0.0;
            double prev_tpr = 0.0;
            double prev_fpr = 0.0;

            for (std::size_t i = 1; i <= n; i++) {
            std::size_t id = idx[i - 1];
            double w = ptr_w[id]; // sample's weight

            if (ptr_actual[id] == class_label) {
                tp += w;
            } else {
                fp += w;
            }

            double cur_tpr = (tp / positives);
            double cur_fpr = (fp / negatives);

            area += updateArea(prev_fpr, prev_tpr, cur_fpr, cur_tpr);

            prev_tpr = cur_tpr;
            prev_fpr = cur_fpr;
            }

            output[c] = area;
        }

        output.attr("names") = levels;
        return output;
}


//' @rdname pr.auc
//' @method pr.auc numeric
//' @export
// [[Rcpp::export(pr.auc.numeric)]]
Rcpp::NumericVector pr_auc(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response,
    int method = 0,
    bool ordered = false) {
        
        // Basic checks
        std::size_t n = actual.size();
        if (n == 0 || n != (std::size_t)response.size()) {
            Rcpp::stop("'actual' and 'response' must have the same non-zero length.");
        }

        Rcpp::CharacterVector levels = actual.attr("levels");
        int n_classes = levels.size();
        Rcpp::NumericVector output(n_classes, R_NaReal);

        // 1) Prepare idx
        std::vector<std::size_t> idx = prepare_index(response, ordered);

        // 2) Pick area update function pointer
        double (*updateArea)(double,double,double,double) 
            = (method == 0) ? trapeziod_area : step_area;

        // 3) For each class => one-vs.-rest
        const int* ptr_actual = actual.begin();
        for (int c = 0; c < n_classes; ++c) {
            int class_label = c + 1;
            // count positives
            double positives = count_positives(actual, idx, class_label);
            if (positives == 0.0) {
            continue; 
            }

            double area = 0.0;
            double tp   = 0.0;
            double fp   = 0.0;

            double prev_recall    = 0.0;
            double prev_precision = 0.0;

            for (std::size_t i = 1; i <= n; i++) {
            std::size_t id = idx[i - 1];
            if (ptr_actual[id] == class_label) {
                tp += 1.0;
            } else {
                fp += 1.0;
            }

            double cur_recall    = (tp / positives);
            double denom         = (tp + fp);
            double cur_precision = (denom > 0.0) ? (tp / denom) : 0.0;

            area += updateArea(prev_recall, prev_precision, 
                                cur_recall,    cur_precision);

            prev_recall    = cur_recall;
            prev_precision = cur_precision;
            }

            output[c] = area;
        }

        // optional: name the output
        output.attr("names") = levels;
        return output;
}

//' @rdname pr.auc
//' @method weighted.pr.auc numeric
//' @export
// [[Rcpp::export(weighted.pr.auc.numeric)]]
Rcpp::NumericVector weighted_pr_auc(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response,
    const Rcpp::NumericVector& w,
    int method = 0,
    bool ordered = false) {
        
        // Basic checks
        std::size_t n = actual.size();
        if (n == 0 || n != (std::size_t)response.size() || n != (std::size_t)w.size()) {
            Rcpp::stop("'actual', 'response', and 'w' must have the same non-zero length.");
        }

        Rcpp::CharacterVector levels = actual.attr("levels");
        int n_classes = levels.size();
        Rcpp::NumericVector output(n_classes, R_NaReal);

        // 1) Prepare idx
        std::vector<std::size_t> idx = prepare_index(response, ordered);

        // 2) Pick area update function pointer once
        double (*updateArea)(double,double,double,double)
            = (method == 0) ? trapeziod_area : step_area;

        // 3) For each class => one-vs.-rest
        const int*    ptr_actual  = actual.begin();
        const double* ptr_w = w.begin();
        //double total_weight = std::accumulate(ptr_w, ptr_w + n, 0.0);

        for (int c = 0; c < n_classes; ++c) {
            int class_label = c + 1;

            // Weighted count of positives
            double positives = count_positives(actual, w, idx, class_label);
            if (positives == 0.0) {
            continue;
            }

            double area = 0.0;
            double tp   = 0.0;
            double fp   = 0.0;

            double prev_recall    = 0.0;
            double prev_precision = 0.0;

            for (std::size_t i = 1; i <= n; i++) {
            std::size_t id = idx[i - 1];
            double w = ptr_w[id];

            if (ptr_actual[id] == class_label) {
                tp += w;
            } else {
                fp += w;
            }

            double cur_recall    = (tp / positives);
            double denom         = (tp + fp);
            double cur_precision = (denom > 0.0) ? (tp / denom) : 0.0;

            area += updateArea(prev_recall, prev_precision, 
                                cur_recall,    cur_precision);

            prev_recall    = cur_recall;
            prev_precision = cur_precision;
            }

            output[c] = area;
        }

        output.attr("names") = levels;
        return output;
}
