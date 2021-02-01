aux_source_directory(. WINDOW_LIB_SRCS)
include_directories(../base)
add_library(windowlib ${WINDOW_LIB_SRCS})
target_link_libraries(windowlib mathlib gdi32 user32)