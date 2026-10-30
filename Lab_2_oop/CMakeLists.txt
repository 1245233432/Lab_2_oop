add_executable (Lab_2_oop "dist_class.cpp" "testing.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab_2_oop PROPERTY CXX_STANDARD 20)
endif()