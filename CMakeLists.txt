cmake_minimum_required(VERSION 3.5)

project(SpacedInvaders)

# vcpkg toolchain integration
# Recommended configure (explicit):
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake
# Or set the environment variable `VCPKG_ROOT` to the vcpkg folder and CMake will pick it up.

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE OR CMAKE_TOOLCHAIN_FILE STREQUAL "")
	# Prefer an explicit VCPKG_ROOT environment variable if present
	if(DEFINED ENV{VCPKG_ROOT} AND EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
		set(_VCPKG_TOOLCHAIN "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
	elseif(EXISTS "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
		set(_VCPKG_TOOLCHAIN "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
	endif()

	if(DEFINED _VCPKG_TOOLCHAIN)
		# Installers and CI generally pass this on the configure command line; cache it so subprojects see it.
		set(CMAKE_TOOLCHAIN_FILE "${_VCPKG_TOOLCHAIN}" CACHE STRING "Vcpkg toolchain file" FORCE)
		message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
	else()
		message(STATUS "vcpkg toolchain not found. To enable vcpkg, run:")
		message(STATUS "  cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
		message(STATUS "Or set the environment variable VCPKG_ROOT to your vcpkg folder.")
	endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(initialtemplate)
add_subdirectory(WindowLayout)
add_subdirectory(bitmaps)
add_subdirectory(simplesprite01)
add_subdirectory(animation01)
add_subdirectory(AnimatedPixels)
add_subdirectory(gameplay01)
add_subdirectory(gameplay02)