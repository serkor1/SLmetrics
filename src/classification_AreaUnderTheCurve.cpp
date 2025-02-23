#include "classification_AreaUnderTheCurve.h"
#include <Rcpp.h>

using namespace Rcpp;

//' @rdname ROC
//' @export
// [[Rcpp::export(roc.auc)]]
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

//' @rdname ROC
//' @export
// [[Rcpp::export(weighted.roc.auc)]]
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


//' @rdname prROC
//' @export
// [[Rcpp::export(pr.auc)]]
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

//' @rdname prROC
//' @export
// [[Rcpp::export(weighted.pr.auc)]]
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
