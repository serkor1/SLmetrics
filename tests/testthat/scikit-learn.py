# import metrics from
# sklearn and define functions
# that corresponds to SLmetrics
from sklearn import metrics
import string
from imblearn.metrics import sensitivity_score
from imblearn.metrics import specificity_score
from sklearn.metrics import confusion_matrix
import numpy as np

# classification 
# functions
def py_jaccard(actual, predicted, average = None, w = None):
    return metrics.jaccard_score(
      y_true = actual, 
      y_pred = predicted, 
      average = average,
      zero_division = 0.0,
      sample_weight = w
    )

def py_fmi(actual, predicted, average = None):
    return metrics.fowlkes_mallows_score(
      labels_true = actual,
      labels_pred = predicted
    )

def py_ckappa(actual, predicted, penalty = None, average = None, w = None):
    return metrics.cohen_kappa_score(
      y1 = actual,
      y2 = predicted,
      weights = penalty,
      sample_weight = w
    )

def py_mcc(actual, predicted, average = None, w = None):
    return metrics.matthews_corrcoef(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )

def py_fbeta(actual, predicted, beta = 1, average = None, w = None):
    return metrics.fbeta_score(
      y_true  = actual,
      y_pred  = predicted,
      beta    = beta,
      average = average,
      zero_division = np.nan,
      sample_weight = w
    )

def py_likelihood(actual, predicted, w = None, labels = None):
    return metrics.class_likelihood_ratios(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w,
      labels = labels
    )
    
def py_zerooneloss(actual, predicted, average = None, w = None):
    return metrics.zero_one_loss(
      y_true  = actual,
      y_pred  = predicted,
      sample_weight = w
    )

def py_precision(actual, predicted, average = None, w = None):
    return metrics.precision_score(
      y_true  = actual,
      y_pred  = predicted,
      average = average,
      zero_division = np.nan,
      sample_weight = w
    )

def py_accuracy(actual, predicted, average = None, w = None):
    return metrics.accuracy_score(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )

def py_hammingloss(actual, predicted, w = None):
    return metrics.hamming_loss(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )
    
def py_baccuracy(actual, predicted, adjust = False, average = None, w = None):
    return metrics.balanced_accuracy_score(
      y_true   = actual,
      y_pred   = predicted,
      adjusted = adjust,
      sample_weight = w
    )
    
def py_entropy(actual, qk, normalize = True, w = None, labels = None):
    return metrics.log_loss(
      y_true    = actual,
      y_pred    = qk,
      normalize = normalize,
      sample_weight = w,
      labels = labels
    )

def py_roc(actual, response, pos_label = 1, w = None):
    return metrics.roc_curve(
      actual,
      response,
      drop_intermediate = False,
      pos_label = pos_label,
      sample_weight = w
      
    )
def py_prROC(actual, response, pos_label = 1, w = None):
  return metrics.precision_recall_curve(
    y_true    = actual,
    y_score   = response,
    drop_intermediate = False,
    pos_label = pos_label,
    sample_weight = w
  )

def py_brier(actual, predicted, w = None):
    return metrics.brier_score_loss(
      y_true  = actual,
      y_prob  = predicted,
      sample_weight = w,
      pos_label = 1
    )

# regression metrics

def py_rmse(actual, predicted, w = None):
    return metrics.root_mean_squared_error(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )
    
def py_rmsle(actual, predicted, w = None):
    return metrics.root_mean_squared_log_error(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )
    
def py_mse(actual, predicted, w = None):
    return metrics.mean_squared_error(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )
    
def py_mae(actual, predicted, w = None):
    return metrics.mean_absolute_error(
      y_true        = actual,
      y_pred        = predicted,
      sample_weight = w
    )

def py_mape(actual, predicted, w = None):
    return metrics.mean_absolute_percentage_error(
      y_true        = actual,
      y_pred        = predicted,
      sample_weight = w
    )
    
def py_msle(actual, predicted, w = None):
    return metrics.mean_squared_log_error(
      y_true        = actual,
      y_pred        = predicted,
      sample_weight = w
    )
    
def py_pinball(actual, predicted, w = None, alpha = 0.5):
    return metrics.mean_pinball_loss(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w,
      alpha = alpha,
      multioutput = "raw_values"
    )

def py_tweedie(actual, predicted, w = None, power = 2):
    return metrics.mean_tweedie_deviance(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w,
      power = power
    )

def py_gamma(actual, predicted, w = None):
    return metrics.mean_gamma_deviance(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )

def py_poisson(actual, predicted, w = None):
    return metrics.mean_poisson_deviance(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w
    )


def py_d2pinball(actual, predicted, w = None, alpha = 0.5):
    return metrics.d2_pinball_score(
      y_true = actual,
      y_pred = predicted,
      sample_weight = w,
      alpha = alpha,
      multioutput = "raw_values"
    )

def py_ROC(actual, response, w=None):

    actual = np.asarray(actual)
    response = np.asarray(response)
    unique_labels = np.unique(actual)
    results = {}

    for i, label in enumerate(unique_labels):
        letter = string.ascii_lowercase[i]
        binary_target = (actual == label).astype(int)
        scores = response[:, i]

        fpr, tpr, thresholds = metrics.roc_curve(
            binary_target,
            scores,
            sample_weight=w,
            drop_intermediate=False
        )

        results[letter] = {
            'threshold': thresholds.tolist(),
            'level': i + 1,
            'label': letter,
            'fpr': fpr.tolist(),
            'tpr': tpr.tolist()
        }

    return results


def py_prROC(actual, response, w=None):
    actual = np.asarray(actual)
    response = np.asarray(response)
    
    unique_labels = np.unique(actual)
   
    
    results = {}
    
    for i, label in enumerate(unique_labels):
        letter = string.ascii_lowercase[i]
        
        # Create a binary target: 1 if the sample's label matches, else 0.
        binary_target = (actual == label).astype(int)
        # Get the prediction scores from the corresponding column.
        scores = response[:, i]
        
        precision, recall, thresholds = metrics.precision_recall_curve(
            binary_target,
            scores,
            sample_weight=w,
            drop_intermediate=False
        )
        
        # The thresholds from precision_recall_curve are returned in ascending order.
        # Reverse them to mimic the ROC curve style (descending order).
        sorted_indices = np.argsort(-thresholds)
        thresholds = thresholds[sorted_indices]
        precision = precision[sorted_indices]
        recall = recall[sorted_indices]
        
        results[letter] = {
            'threshold': thresholds.tolist(),
            'level': i + 1,
            'label': letter,
            'recall': recall.tolist(),
            'precision': precision.tolist()
        }
    
    return results


def py_rocAUC(actual, response, w = None, micro = None):
  return metrics.roc_auc_score(
    y_true  = actual,
    y_score = response,
    average = micro,
    multi_class = "ovr",
    sample_weight = w
  )

def py_prAUC(actual, response, w = None, micro = None):
  return metrics.average_precision_score(
    y_true  = actual,
    y_score = response,
    average = micro,
    sample_weight = w
  )