project(EnjoyCMake)
cmake_minimum_required(VERSION 3.13)

add_compile_options(-fno-exceptions)

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtk4 REQUIRED IMPORTED_TARGET gtk4)

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(SOURCE_GRESOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/gresources.xml")
set(GENERATED_RESOURCE_FILE "${CMAKE_CURRENT_BINARY_DIR}/resources.c")

set(RESOURCE_FILES bakground.gif style.css)

add_custom_command(
    OUTPUT "${GENERATED_RESOURCE_FILE}"
    COMMAND "${GLIB_COMPILE_RESOURCES}"
    ARGS
        --target "${GENERATED_RESOURCE_FILE}"
        --generate-source
        --internal --c-name=enjoe_cmake
        --sourcedir "${CMAKE_CURRENT_SOURCE_DIR}"
        "${SOURCE_GRESOURCE_FILE}"
    DEPENDS "${SOURCE_GRESOURCE_FILE}" "${RESOURCE_FILES}"
)


add_executable(EnjoyCMake
    main.cpp
    window.cpp
    style_loader.cpp
    "${GENERATED_RESOURCE_FILE}"
)

target_link_libraries(EnjoyCMake PRIVATE PkgConfig::gtk4)

install(TARGETS EnjoyCMake)
