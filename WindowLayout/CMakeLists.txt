cmake_minimum_required(VERSION 3.6)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED allegro-5)

message(STATUS "ALLEGRO_INCLUDE_DIRS: ${ALLEGRO_INCLUDE_DIRS}")
message(STATUS "ALLEGRO_LIBRARIES: ${ALLEGRO_LIBRARIES}")

# include_directories(${ALLEGRO_INCLUDE_DIRS} /usr/include)

add_executable(WindowLayout main.cpp)

target_include_directories(WindowLayout PRIVATE ${ALLEGRO_INCLUDE_DIRS} /usr/include/allegro5)

target_link_libraries(WindowLayout ${ALLEGRO_LIBRARIES}
        allegro_main
        allegro_font
        allegro_ttf
        allegro_image
        allegro_primitives
#        allegro_audio
#        allegro_acodec
#        allegro_physfs
)
