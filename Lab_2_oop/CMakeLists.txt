add_executable (Lab_2_oop "dist_class.cpp" "dist_class.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab_2_oop PROPERTY CXX_STANDARD 20)
endif()