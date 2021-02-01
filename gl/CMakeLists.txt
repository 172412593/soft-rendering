
add_subdirectory(base)
add_subdirectory(window)
add_subdirectory(pro)
aux_source_directory(. GL_LIB_SRCS)
message(STATUS ${GL_LIB_SRCS})
add_library(GL ${GL_LIB_SRCS})
target_link_libraries(GL mathlib windowlib prolib)