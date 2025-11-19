cmake_minimum_required(VERSION 3.6)

# If vcpkg is available, add its installed triplets to CMAKE_PREFIX_PATH so
# CMake `find_package(... CONFIG)` can find vcpkg-provided config files.
if(DEFINED ENV{VCPKG_ROOT} AND EXISTS "$ENV{VCPKG_ROOT}/installed")
        set(_VCPKG_ROOT "$ENV{VCPKG_ROOT}")
elseif(EXISTS "D:/vcpkg/installed")
        set(_VCPKG_ROOT "D:/vcpkg")
endif()

if(DEFINED _VCPKG_ROOT)
        file(GLOB _VCPKG_INSTALLED_DIRS LIST_DIRECTORIES true "${_VCPKG_ROOT}/installed/*")
        if(_VCPKG_INSTALLED_DIRS)
                foreach(_dir IN LISTS _VCPKG_INSTALLED_DIRS)
                        list(APPEND CMAKE_PREFIX_PATH "${_dir}")
                endforeach()
                message(STATUS "Appended vcpkg installed dirs to CMAKE_PREFIX_PATH: ${_VCPKG_INSTALLED_DIRS}")
        endif()
endif()

# Try CMake CONFIG package (vcpkg can provide this). If targets are present,
# prefer them. Otherwise fall back to pkg-config (for systems that provide
# allegro.pc).
find_package(allegro CONFIG QUIET)
set(_USE_ALLEGRO_CONFIG FALSE)
if(TARGET allegro::allegro OR TARGET allegro::allegro_main)
        set(_USE_ALLEGRO_CONFIG TRUE)
        message(STATUS "Found Allegro via CMake CONFIG package (likely vcpkg)")
endif()

if(NOT _USE_ALLEGRO_CONFIG)
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
                pkg_check_modules(ALLEGRO QUIET allegro-5)
        endif()
endif()

if(NOT _USE_ALLEGRO_CONFIG AND NOT ALLEGRO_FOUND)
        message(FATAL_ERROR "Allegro not found.\n"
                "Install Allegro via vcpkg and configure CMake with the vcpkg toolchain file. Example:\n"
                "  vcpkg install allegro:x64-windows\n"
                "  cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake\n"
                "Or set the environment variable VCPKG_ROOT to your vcpkg root and re-run CMake.")
endif()

add_executable(gameplay01 main.cpp)
set_target_properties(gameplay01 PROPERTIES FOLDER "Gameplay")

if(_USE_ALLEGRO_CONFIG)
        if(TARGET allegro::allegro)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro)
        endif()
        if(TARGET allegro::allegro_main)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro_main)
        endif()
        if(TARGET allegro::allegro_font)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro_font)
        endif()
        if(TARGET allegro::allegro_ttf)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro_ttf)
        endif()
        if(TARGET allegro::allegro_image)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro_image)
        endif()
        if(TARGET allegro::allegro_primitives)
                target_link_libraries(gameplay01 PRIVATE allegro::allegro_primitives)
        endif()
else()
        message(STATUS "ALLEGRO_INCLUDE_DIRS: ${ALLEGRO_INCLUDE_DIRS}")
        message(STATUS "ALLEGRO_LIBRARIES: ${ALLEGRO_LIBRARIES}")
        target_include_directories(gameplay01 PRIVATE ${ALLEGRO_INCLUDE_DIRS} /usr/include/allegro5)
        target_link_libraries(gameplay01 ${ALLEGRO_LIBRARIES}
                allegro_main
                allegro_font
                allegro_ttf
                allegro_image
                allegro_primitives
        #        allegro_audio
        #        allegro_acodec
        #        allegro_physfs
        )
endif()
