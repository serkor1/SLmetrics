import numpy as np
from scipy import stats

def py_shannon_entropy(pk, dim, base = None):

    ## recode dim
    ## to scipy compatible
    ## output
    match dim:
        case 0: dim = None
        case 1: dim = 0
        case 2: dim = 1
        
    ## calculate entropy
    entropy = stats.entropy(
        pk   = pk,
        base = base,
        axis = dim
    )
    
    return entropy

def py_relative_entropy(pk, qk, dim, base = None):

    ## recode dim
    ## to scipy compatible
    ## output
    match dim:
        case 0: dim = None
        case 1: dim = 0
        case 2: dim = 1
        

    ## calculate entropy
    entropy = stats.entropy(
        pk   = pk,
        qk   = qk,
        axis = dim,
        base = base
    )

    return entropy

def py_cross_entropy(pk, qk, dim, base = None):

    ## calculate shannon
    ## entropy
    shannon_entropy = py_shannon_entropy(
        pk   = pk,
        dim  = dim, 
        base = base
    )

    ## calculate relative
    ## entropy
    relative_entropy = py_relative_entropy(
        pk = pk,
        qk = qk,
        dim = dim,
        base = base
    )

    ## entropy
    return shannon_entropy + relative_entropy