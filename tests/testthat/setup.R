# script: Test-setup
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: General test setup (Not entirely sure how this works tbh)
# script start;

# 1) set seed for all
# samples
set.seed(1903)

# # 2) install
# reticulate::conda_install(
#   envname = "base",
#   packages = c(
#     "numpy",
#     "scipy",
#     "mkl",
#     "mkl-service",
#     "mkl_fft",
#     "mkl_random",
#     "pytorch",
#     "torchmetrics",
#     "scikit-learn"
#   )
#   # python_version = "3.12.2"
# )
#
# # 3) set the condaenvironment
# # for the tests


# 3) force reticulate to
# use virtual environment
#
# NOTE: Has to be set between sessions
# otherwise it won't compile
reticulate::use_virtualenv()


# script end;
