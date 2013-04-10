cmake_minimum_required(VERSION 2.8.8)
project(GrandTheftGentoo CXX)

if (NOT CMAKE_BUILD_TYPE)
	# default build type
	set(CMAKE_BUILD_TYPE "Release")
endif()

set($ENV{LANG} en_US.UTF-8) # fuck localized errors
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wpointer-arith -pedantic")

# (un)comment to switch between gcc and clang
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

if (CMAKE_CXX_COMPILER MATCHES ".*clang.*")
	set(CMAKE_CXX_COMPILER_IS_CLANG 1)
	set(CMAKE_CXX_COMPILER_IS_GCC   0)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if (CMAKE_CXX_COMPILER MATCHES ".*/g(cc|\\+\\+).*")
	set(CMAKE_CXX_COMPILER_IS_CLANG 0)
	set(CMAKE_CXX_COMPILER_IS_GCC   1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DQT_NO_DEBUG_OUTPUT")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

file(GLOB sources ${GrandTheftGentoo_SOURCE_DIR}/*.cpp)
file(GLOB sources_tile ${GrandTheftGentoo_SOURCE_DIR}/tile/*.cpp)
file(GLOB sources_helpers ${GrandTheftGentoo_SOURCE_DIR}/helpers/*.cpp)

add_executable(gtg ${sources} ${sources_tile} ${sources_helpers})

qt5_use_modules(gtg Core Gui Qml Quick)

if (CMAKE_CXX_COMPILER_IS_CLANG)
	target_link_libraries(gtg c++abi)
endif()
