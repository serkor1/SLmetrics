## 0) Initialize the Autoconf
##    and broadcast the awesomeness of 
##    this tool.
##
##    NOTE: If you are reading this, and you are not me, then
##    see: https://unconj.ca/blog/an-autoconf-primer-for-r-package-authors.html
##    this is a good place to get started, alongside the official documentation
##    found here: https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.72/autoconf.pdf
AC_INIT([{SLmetrics}], [v0.3-3])
AC_MSG_NOTICE([Configuring {SLmetrics} ${PACKAGE_VERSION}])

## 1) Locate R Home
##    this is where R is stored
##    often a standard location.
##
##    NOTE: It may, or may not, be a a good idea
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
m4_include([m4/ax_cxx_compile_stdcxx.m4])
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
##    which us appended at step 6.
##
##    NOTE: As per March 22, 2025 this have not been
##    tested on clang, and according to the macro
##    it doesnt test on clang or llvm. So it is not clear
##    what will happen when it fails.
m4_include([m4/ax_openmp.m4])
AX_OPENMP([
  AC_MSG_NOTICE([OpenMP available])
],[
  AC_MSG_NOTICE([OpenMP NOT available])
])

## 5) Check for zlib
##    availability. 
## 
##    At this stage it is unkown why I need
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
PKG_CPPFLAGS="${CPPFLAGS_R}"
if test -n "$OPENMP_CFLAGS"; then
  PKG_CPPFLAGS="$PKG_CPPFLAGS $OPENMP_CFLAGS"
fi
AC_SUBST([PKG_CPPFLAGS])

## 6.2) PKG_CXXFLAGS
##      conditional on OPENMP
##      availability
PKG_CXXFLAGS="${CXXSTD} ${CXXFLAGS_R}"
if test -n "$OPENMP_CXXFLAGS"; then
  PKG_CXXFLAGS="$PKG_CXXFLAGS $OPENMP_CXXFLAGS"
fi
AC_SUBST([PKG_CXXFLAGS])

## 6.3) PKG_LIBS
##      This is wher all the 
##      relevant extra libraries are added
PKG_LIBS="${BLAS_LIBS} ${LAPACK_LIBS} ${FLIBS}"
AC_SUBST([PKG_LIBS])

## 7) Construct the Makevars
##    file and celebrate
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

## 8) End of program
##    (For the LF/CRF warnings)