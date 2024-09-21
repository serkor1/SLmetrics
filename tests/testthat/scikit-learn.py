# import metrics from
# sklearn and define functions
# that corresponds to SLmetrics
from sklearn import metrics

# classification 
# functions
def py_jaccard(actual, predicted, average = None):
    return metrics.jaccard_score(
      y_true = actual, 
      y_pred = predicted, 
      average = average
    )

def py_fmi(actual, predicted):
    return metrics.fowlkes_mallows_score(
      labels_true = actual,
      labels_pred = predicted
    )

def py_kappa(actual, predicted, penalty):
    return metrics.cohen_kappa_score(
      y1 = actual,
      y2 = predicted,
      weights = penalty,
      sample_weight = None
    )

def py_mcc(actual, predicted):
    return metrics.matthews_corrcoef(
      y_true = actual,
      y_pred = predicted
    )

def py_fbeta(actual, predicted, beta, average = None):
    return metrics.fbeta_score(
      y_true  = actual,
      y_pred  = predicted,
      beta    = beta,
      average = average 
    )

def py_likelihood(actual, predicted):
    return metrics.class_likelihood_ratios(
      y_true = actual,
      y_pred = predicted
    )
    
def py_recall(actual, predicted, average = None):
    return metrics.recall_score(
      y_true  = actual,
      y_pred  = predicted,
      average = average
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
      average = average
    )
