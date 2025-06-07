## 0) Initialize the Autoconf
##    and broadcast the awesomeness of 
##    this tool.
##
##    NOTE: If you are reading this, and you are not me, then
##    see: https://unconj.ca/blog/an-autoconf-primer-for-r-package-authors.html
##    this is a good place to get started, alongside the official documentation
##    found here: https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.72/autoconf.pdf
AC_INIT([{SLmetrics}], [v0.3-4])
AC_MSG_NOTICE([Configuring {SLmetrics} ${PACKAGE_VERSION}])

## 1) Locate R Home
##    this is where R is stored
##    often a standard location.
##
##    NOTE: It may, or may not, be a good idea
##    to search for it in alternative locations 
##    for users using containers, dockers and other
##    stuff that changes essential stuff 
: ${R_HOME=`R RHOME`}
if test -z "$R_HOME"; then
  AC_MSG_ERROR([could not determine R_HOME])
fi

## 2) Extract compiler flags
##    shipped with R (NOTE: I do not know if this is TRUE, however.)
##    alternatively one can use pkgconf however
##    at this stage R CMD config is sufficient
CPPFLAGS_R=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
CXXFLAGS_R=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
BLAS_LIBS=`"${R_HOME}/bin/R" CMD config BLAS_LIBS`
LAPACK_LIBS=`"${R_HOME}/bin/R" CMD config LAPACK_LIBS`
FLIBS=`"${R_HOME}/bin/R" CMD config FLIBS`

## 3) Check for C++23 
##    if not available try C++20, and 
##    fall back on C++17 (if not available it will abort)
##
##    NOTE: The macro will export the relevant flags
##
## 3.1) Run the conditional tests
##      and ending with [mandatory] to abort
##      installation
AC_LANG([C++])
AC_PROG_CXX
AC_CONFIG_MACRO_DIR([tools/m4])
m4_include([tools/m4/ax_cxx_compile_stdcxx.m4])
AX_CXX_COMPILE_STDCXX([23], [ext], [optional])
if test "$HAVE_CXX23" = "1"; then
  STD_VER=23
else
  AX_CXX_COMPILE_STDCXX([20], [ext], [optional])
  if test "$HAVE_CXX20" = "1"; then
    STD_VER=20
  else
    AX_CXX_COMPILE_STDCXX([17], [ext], [mandatory])
    STD_VER=17
  fi
fi

## 3.2) Notify user which
##      CXXSTD is used and
##      set it accordingly
AC_MSG_NOTICE([Using C++$STD_VER])
CXXSTD=`"${R_HOME}/bin/R" CMD config CXX${STD_VER}STD`

## 4) Check OpenMP support
##    on the compiler.
##
##    This macro returns a $OPENMP_CFLAGS or $OPENMP_CXXFLAGS
##    which is appended at step 6.
##
##    NOTE: As per March 22, 2025 this have not been
##    tested on clang, and according to the macro
##    it doesn't test on clang or LLVM. So it is not clear
##    what will happen when it fails.
##
##    March 27, 2025
##    UPDATE: This does NOT work on clang, or generally
##    on MacOS unless ~/.R/Makevars is correctly specified.
##    This has been tested on locally on Macbook with and without
##    ~/.R/Makevars
##
##    m4_include([m4/ax_openmp.m4])
##    AX_OPENMP([
##     AC_MSG_NOTICE([OpenMP available])
##     ],[
##     AC_MSG_NOTICE([OpenMP NOT available])
##    ])
##
##    This section has been borrowed and adapted from the configure.ac-file
##    at https://github.com/RcppCore/RcppArmadillo - the entire configure.ac there works
##    as it should from my own tests. Check out that file made by  Dirk Eddelbuettel and his team.
openmp_already_works="no"
can_use_openmp="no"

## 4.1) Define a small .cpp-program that
##      checks for OpenMP availability
cat <<EOF > test-omp.cpp
#include <omp.h>
int main() {
  return omp_get_num_threads();
}
EOF

## 4.2) Run OpenMP-program with
##      standard R CMD SHLIB
AC_MSG_CHECKING([whether R CMD SHLIB can already compile programs using OpenMP])
"${R_HOME}/bin/R" CMD SHLIB test-omp.cpp >/dev/null 2>&1
if test x"$?" = x"0"; then
    AC_MSG_RESULT([yes])
    openmp_already_works="yes"
else
    AC_MSG_RESULT([no])
fi

## 4.3) If 4.2) fails, ie. R CMD SHLIB can't compile
##      and run the OpenMP program then start looking
##      available compilers on host to look for compatible
##      compilers on MacOS, Windows and Linux systems
if test x"${openmp_already_works}" = x"no"; then

    ## Check the C++ compiler using the CXX value set

    ## If it is g++, we have GXX set so let's examine it
    if test "${GXX}" = yes; then
        AC_MSG_CHECKING([whether g++ version is sufficient])
        gxx_version=$(${CXX} -v 2>&1 | awk '/^.*g.. version/ {print $3}')
        case ${gxx_version} in
            1.*|2.*|3.*|4.0.*|4.1.*|4.2.*|4.3.*|4.4.*|4.5.*|4.6.*|4.7.0|4.7.1)
                 AC_MSG_RESULT([no])
                 AC_MSG_WARN([Only g++ version 4.7.2 or greater can be used with Armadillo.])
                 AC_MSG_ERROR([Please use a different compiler.])
            ;;
            4.7.*|4.8.*|4.9.*|5.0*|5.1*|5.2*|5.3*)
                 AC_MSG_RESULT([yes, but without OpenMP as version ${gxx_version} (Armadillo constraint)])
                 ## we know this one is bad
                 can_use_openmp="no"
            ;;
            5.4*|5.5*|5.6*|5.7*|5.8*|5.9*|6.*|7.*|8.*|9.*|10.*|11.*|12.*)
                 AC_MSG_RESULT([yes, with OpenMP as version ${gxx_version}])
                 ## we know this one is good, yay
                 can_use_openmp="yes"
            ;;
            *)
                 AC_MSG_RESULT([almost])
                 AC_MSG_WARN([Compiler self-identifies as being compliant with GNUC extensions but is not g++.])
                 ## we know nothing, so no
                 can_use_openmp="no"
            ;;
        esac
    fi

    ## Check for Apple LLVM

    AC_MSG_CHECKING([for macOS])
    RSysinfoName=$("${R_HOME}/bin/Rscript" --vanilla -e 'cat(Sys.info()[["sysname"]])')

    if test x"${RSysinfoName}" = x"Darwin"; then
        AC_MSG_RESULT([found])
        AC_MSG_CHECKING([for macOS Apple compiler])

        apple_compiler=$($CXX --version 2>&1 | grep -i -c -e 'apple llvm')

        if test x"${apple_compiler}" = x"1"; then
            AC_MSG_RESULT([found])
            AC_MSG_WARN([OpenMP unavailable and turned off.])
            can_use_openmp="no"
        else
            AC_MSG_RESULT([not found])
            AC_MSG_CHECKING([for clang compiler])
            clang_compiler=$($CXX --version 2>&1 | grep -i -c -e 'clang ')

            if test x"${clang_compiler}" = x"1"; then
                AC_MSG_RESULT([found])
                AC_MSG_CHECKING([for OpenMP compatible version of clang])
                clang_version=$(${CXX} -v 2>&1 | awk '/^.*clang version/ {print $3}')

                case ${clang_version} in
                    4.*|5.*|6.*|7.*|8.*|9.*|10.*|11.*)
                        AC_MSG_RESULT([found and suitable])
                        can_use_openmp="yes"
                    ;;
                    *)
                        AC_MSG_RESULT([not found])
                        AC_MSG_WARN([OpenMP unavailable and turned off.])
                        can_use_openmp="no"
                    ;;
                esac
            else
                AC_MSG_RESULT([not found])
                AC_MSG_WARN([unsupported macOS build detected; if anything breaks, you keep the pieces.])
            fi
        fi
    else
        AC_MSG_RESULT([no])
    fi

fi

## 5) Check for zlib
##    availability. 
## 
##    At this stage it is unknown why I need
##    it. But its basically there in every single
##    tutorial, or documentation. So it must be
##    important.
AC_SEARCH_LIBS([deflate], [z], [], [AC_MSG_ERROR([zlib required])])

## 6) Construct flags and libraries
##    to be appended in Makevars.
##
## 6.1) PKG_CPPFLAGS
##      conditional on OPENMP
##      availability
openmp_flag=""

## Set the fallback, by default it is nope
arma_have_openmp="#define ARMA_DONT_USE_OPENMP 1"

if test x"${openmp_already_works}" = x"yes"; then
    arma_have_openmp="#define ARMA_USE_OPENMP 1"
    openmp_flag='$(SHLIB_OPENMP_CXXFLAGS)'
fi

if test x"${can_use_openmp}" = x"yes"; then
    AC_MSG_CHECKING([for OpenMP])
    ## if R has -fopenmp we should be good
    allldflags=$(${R_HOME}/bin/R CMD config --ldflags)
    hasOpenMP=$(echo ${allldflags} | grep -- -fopenmp)
    if test x"${hasOpenMP}" = x""; then
        AC_MSG_RESULT([missing])
        arma_have_openmp="#define ARMA_DONT_USE_OPENMP 1"
    else
        AC_MSG_RESULT([found and suitable])
        arma_have_openmp="#define ARMA_USE_OPENMP 1"
        openmp_flag='$(SHLIB_OPENMP_CXXFLAGS)'
    fi
fi
AC_SUBST([OPENMP_FLAG], ["${openmp_flag}"])

## 6.3) PKG_LIBS
##      This is where all the
##      relevant extra libraries are added
PKG_LIBS="${BLAS_LIBS} ${LAPACK_LIBS} ${FLIBS}"
AC_SUBST([PKG_LIBS])

## 6.4) CPP AND CXX FLAGS
PKG_CPPFLAGS="${CPPFLAGS_R}"
AC_SUBST([PKG_CPPFLAGS])
PKG_CXXFLAGS="${CXXSTD} ${CXXFLAGS_R}"
AC_SUBST([PKG_CXXFLAGS])

## 7) Construct the Makevars
##    file and celebrate
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
