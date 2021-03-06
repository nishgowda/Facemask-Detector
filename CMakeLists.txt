# CMakeLists.txt

# Older versions of CMake are likely to work just fine but, since
# I don't know where to cut off I just use the version I'm using
cmake_minimum_required(VERSION "3.17")

# name of this example project
project(facemask)

# set OpenCV_DIR variable equal to the path to the cmake
# files within the previously installed opencv program
set(OpenCV_DIR /Users/nishgowda/opencv/install/lib/cmake/opencv4)

# Tell compiler to use C++ 14 features which is needed because
# Clang version is often behind in the XCode installation
set(CMAKE_CXX_STANDARD 14)

# configure the necessary common CMake environment variables
# needed to include and link the OpenCV program into this
# demo project, namely OpenCV_INCLUDE_DIRS and OpenCV_LIBS
find_package( OpenCV REQUIRED )

# tell the build to include the headers from OpenCV
include_directories( ${OpenCV_INCLUDE_DIRS} )
file(GLOB source_files
        "*.h"
        "*.cpp"
        "include/*.h"
        "src/main.cpp")
file(GLOB test_files
        "*.h"
        "*.cpp"
        "include/*.h"
        "src/tests.cpp")
# specify the executable target to be built
add_executable(facemask  ${source_files} )
add_executable(facemask_test ${test_files})

# tell it to link the executable target against OpenCV
target_link_libraries(facemask ${OpenCV_LIBS} )
target_link_libraries(facemask_test ${OpenCV_LIBS} )