import torch
import torch.nn as nn
from torchmetrics import ConcordanceCorrCoef
from torchmetrics.functional import symmetric_mean_absolute_percentage_error

# Classification metrics
def py_huber(actual, predicted, delta=1.0, w=None):
  
    actual = torch.tensor(actual, dtype=torch.float64)
    predicted = torch.tensor(predicted, dtype=torch.float64)
    huber_loss_fn = nn.HuberLoss(delta=delta, reduction='none')
    loss = huber_loss_fn(predicted, actual)

    if w is not None:
        w = torch.tensor(w, dtype=torch.float64)

        weighted_loss_sum = (loss * w).sum()
        w_sum = w.sum()

        return (weighted_loss_sum / w_sum).item()
    else:
        return loss.mean().item()

def py_ccc(actual, predicted, w=None):

    actual = torch.tensor(actual, dtype=torch.float64)
    predicted = torch.tensor(predicted, dtype=torch.float64)

    ccc_metric = ConcordanceCorrCoef()

    if w is None:
        result = ccc_metric(predicted, actual)
        return result.item()

    else:
        w = torch.tensor(w, dtype=torch.float64)

        mean_actual = (actual * w).sum() / w.sum()
        mean_predicted = (predicted * w).sum() / w.sum()

        centered_actual = actual - mean_actual
        centered_predicted = predicted - mean_predicted

        var_actual = ((centered_actual)**2 * w).sum() / w.sum()
        var_predicted = ((centered_predicted)**2 * w).sum() / w.sum()

        covariance = (centered_actual * centered_predicted * w).sum() / w.sum()

        ccc = (2 * covariance) / (var_actual + var_predicted + (mean_actual - mean_predicted)**2)
        return ccc.item()

def py_smape(actual, predicted, w=None):
    actual = torch.tensor(actual, dtype=torch.float64)
    predicted = torch.tensor(predicted, dtype=torch.float64)

    smape_values = []
    
    for a, p in zip(actual, predicted):
        smape = symmetric_mean_absolute_percentage_error(p.unsqueeze(0), a.unsqueeze(0))
        smape_values.append(smape.item())

    smape_values = torch.tensor(smape_values, dtype=torch.float64)

    if w is None:
        return smape_values.mean().item()
    
    # If weights are provided, calculate the weighted SMAPE
    else:
        w = torch.tensor(w, dtype=torch.float64)
        weighted_smape = (smape_values * w).sum() / w.sum()
        return weighted_smape.item()
