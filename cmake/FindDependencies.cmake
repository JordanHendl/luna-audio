option(UseConan "Whether or not to use Conan for packages" ON)

macro(FindRequiredPackages)
set(conan_include_path ${CMAKE_BINARY_DIR}/conan_paths.cmake)
if(EXISTS ${conan_include_path})
  include(${conan_include_path})
endif()
find_package(OpenAL REQUIRED)
find_package(GTest)
endmacro()