aux_source_directory(. MATH_LIB_SRCS)
message(STATUS ${MATH_LIB_SRCS})
add_library(mathlib ${MATH_LIB_SRCS})
