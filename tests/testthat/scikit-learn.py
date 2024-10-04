# import metrics from
# sklearn and define functions
# that corresponds to SLmetrics
from sklearn import metrics
from imblearn.metrics import sensitivity_score
from imblearn.metrics import specificity_score
import numpy as np

# classification 
# functions
def py_jaccard(actual, predicted, average = None):
    return metrics.jaccard_score(
      y_true = actual, 
      y_pred = predicted, 
      average = average,
      zero_division = np.nan
    )

def py_fmi(actual, predicted):
    return metrics.fowlkes_mallows_score(
      labels_true = actual,
      labels_pred = predicted,
      zero_division = np.nan
    )

def py_kappa(actual, predicted, penalty):
    return metrics.cohen_kappa_score(
      y1 = actual,
      y2 = predicted,
      weights = penalty,
      sample_weight = None,
      zero_division = np.nan
    )

def py_mcc(actual, predicted):
    return metrics.matthews_corrcoef(
      y_true = actual,
      y_pred = predicted
    )

def py_fbeta(actual, predicted, beta = 1, average = None):
    return metrics.fbeta_score(
      y_true  = actual,
      y_pred  = predicted,
      beta    = beta,
      average = average,
      zero_division = np.nan
    )

def py_likelihood(actual, predicted):
    return metrics.class_likelihood_ratios(
      y_true = actual,
      y_pred = predicted,
      zero_division = np.nan
    )
    
def py_recall(actual, predicted, average = None):
    return metrics.recall_score(
      y_true  = actual,
      y_pred  = predicted,
      average = average,
      zero_division = np.nan
    )
    
def py_zerooneloss(actual, predicted):
    return metrics.zero_one_loss(
      y_true  = actual,
      y_pred  = predicted
    )

def py_precision(actual, predicted, average = None):
    return metrics.precision_score(
      y_true  = actual,
      y_pred  = predicted,
      average = average,
      zero_division = np.nan
    )

def py_accuracy(actual, predicted):
    return metrics.accuracy_score(
      y_true = actual,
      y_pred = predicted
    )
    
def py_baccuracy(actual, predicted, adjust = False):
    return metrics.balanced_accuracy_score(
      y_true   = actual,
      y_pred   = predicted,
      adjusted = adjust 
    )
    
def py_cmatrix(actual, predicted):
    return metrics.confusion_matrix(
      y_true = actual,
      y_pred = predicted
    )
    
def py_entropy(actual, response, normalize = True):
    return metrics.log_loss(
      y_true    = actual,
      y_pred    = response,
      normalize = normalize
    )

def py_specificity(actual, response, average = None):
    return specificity_score(
      y_true    = actual,
      y_pred    = response,
      average   = average
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
