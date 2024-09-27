# script: Test-setup
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective:
#
# Setup the test-environment for
# {scikit-learn} and {torch}
#
# script start;

# 1) set seed for all
# samples
set.seed(1903)

# 2) check if the r-reticulate
# virtual enviroment exists. And install
# it otherwise.
if (!reticulate::virtualenv_exists()) {

  # 2.1) install the virtual
  # environment
  reticulate::virtualenv_create()

  # 2.2) install packages
  # for the virtual environment
  reticulate::py_install(
    packages = c(
      "numpy",
      "scipy",
      "mkl",
      "mkl-service",
      "mkl_fft",
      "mkl_random",
      "pytorch",
      "torchmetrics",
      "scikit-learn"
    )
  )

}

# 3) force reticulate to
# use virtual environment
#
# NOTE: Has to be set between sessions
# otherwise it won't compile
reticulate::use_virtualenv()


# script end;
