#
# Set compiler flags before running conan
#

# Link this 'library' to use the standard warnings
add_library(compiler_warnings INTERFACE)
add_library(tobanteGaming::CompilerWarnings ALIAS compiler_warnings)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(compiler_options INTERFACE)
add_library(tobanteGaming::CompilerOptions ALIAS compiler_options)

target_compile_features(compiler_options INTERFACE cxx_std_17)
if(MSVC)
  target_compile_options(compiler_warnings INTERFACE /W4 "/permissive-")
else()
  option(ONLY_COVERAGE "Build only tests necessary for coverage" FALSE)
  option(LIBCPP "Build with libc++" FALSE)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
  option(ENABLE_FUZZERS "Enable fuzz testing tools" FALSE)

  if(ONLY_COVERAGE OR ENABLE_COVERAGE)
    target_compile_options(compiler_options INTERFACE --coverage -O0 -g)
    target_link_libraries(compiler_options INTERFACE --coverage)
  endif()

  option(ENABLE_ASAN "Enable address sanitizer" FALSE)

  if(ENABLE_ASAN)
    target_compile_options(compiler_options INTERFACE -fsanitize=address)
    target_link_libraries(compiler_options INTERFACE -fsanitize=address)
  endif()

  target_compile_options(compiler_warnings
                         INTERFACE -Wall
                                   -Wextra # reasonable and standard
                                   -Wshadow # warn the user if a variable
                                            # declaration shadows one from a
                                            # parent context
                                   -Wnon-virtual-dtor # warn the user if a class
                                                      # with virtual functions
                                                      # has a non-virtual
                                                      # destructor. This helps
                                                      # catch hard to track down
                                                      # memory errors
                                   -Wold-style-cast # warn for c-style casts
                                   -Wcast-align # warn for potential performance
                                                # problem casts
                                   -Wunused # warn on anything being unused
                                   -Woverloaded-virtual # warn if you overload
                                                        # (not override) a
                                                        # virtual function
                                   -Wpedantic # warn if non-standard C++ is used
                                   -Wconversion # warn on type conversions that
                                                # may lose data
                                   -Wsign-conversion # warn on sign conversions
                                   -Wnull-dereference # warn if a null
                                                      # dereference is detected
                                   -Wdouble-promotion # warn if float is
                                                      # implicit promoted to
                                                      # double
                                   -Wformat=2 # warn on security issues around
                                              # functions that format output (ie
                                              # printf)
                         )

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(compiler_warnings
                           INTERFACE -Wmisleading-indentation # warn if
                                                              # identation
                                                              # implies blocks
                                                              # where blocks do
                                                              # not exist
                                     -Wduplicated-cond # warn if if / else chain
                                                       # has duplicated
                                                       # conditions
                                     -Wduplicated-branches # warn if if / else
                                                           # branches have
                                                           # duplicated code
                                     -Wlogical-op # warn about logical
                                                  # operations being used where
                                                  # bitwise were probably wanted
                                     -Wuseless-cast # warn if you perform a cast
                                                    # to the same type
                           )
    target_link_libraries(compiler_options INTERFACE stdc++fs)
  else()
    if(LIBCPP)
      target_compile_options(compiler_options INTERFACE -stdlib=libc++)
    else()
      target_link_libraries(compiler_options INTERFACE stdc++fs)
    endif()

  endif()
endif()