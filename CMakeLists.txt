cmake_minimum_required(VERSION 3.10)

project(CppPuzzles)

set(CMAKE_BUILD_TYPE Debug)

## dependencies ###############################################################

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
	range-v3/0.5.0@ericniebler/stable
	BASIC_SETUP CMAKE_TARGETS
	BUILD missing
)

## executables ################################################################

foreach(ITEM iterate-multiple-containers-using-range-v3-zip iterate-multiple-containers-using-range-v3-zip_with)
	add_executable(${ITEM}
		src/${ITEM}.cpp
	)
	target_link_libraries(${ITEM} CONAN_PKG::range-v3)
	target_compile_features(${ITEM} PRIVATE cxx_std_17)
endforeach(ITEM)
