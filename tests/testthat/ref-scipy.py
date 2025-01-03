import numpy as np
from scipy import stats

def ref_entropy(pk, qk = None, type = 0, relative = True, axis = None, base = None):

    # shannons entropy
    if type == 0:
        output = stats.entropy(
            pk   = pk,
            base = base,
            axis = axis
        )
    
    # relative entropy
    if type == 1:
        output = stats.entropy(
            pk = pk,
            qk = qk,
            base = base,
            axis = axis
        )
    
    # cross-entropy
    if type == 2:
        entropy_ = stats.entropy(
            pk   = pk,
            base = base,
            axis = axis
        )
        output = entropy_ + stats.entropy(
            pk = pk,
            qk = qk,
            base = base,
            axis = axis
        )

    return output
