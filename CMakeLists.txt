cmake_minimum_required(VERSION 3.80)

project(mentat VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4 gmodule-export-2.0>=2.82.2)

add_executable(mentat
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mentat_app.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/state.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/buttons.c
)
target_include_directories(mentat
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_options(mentat
    PRIVATE -Wl,--export-dynamic
)
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/mentat.ui MENTAT_UI_CONTENTS)
string(REPLACE "\n" "" MENTAT_UI ${MENTAT_UI_CONTENTS})

set_property(
    DIRECTORY
    APPEND
    PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mentat.ui
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mentatui.h.in ${CMAKE_BINARY_DIR}/mentatui.h ESCAPE_QUOTES @ONLY)

target_link_libraries(mentat PRIVATE PkgConfig::GTK4)

target_include_directories(mentat PRIVATE ${CMAKE_BINARY_DIR})

include(GNUInstallDirs)

install(TARGETS mentat
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
