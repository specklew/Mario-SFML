message(STATUS "Fetching sfml...")

FetchContent_GetProperties(sfml)

if(NOT SFML_POPULATED)
    if (LINK_DEPS_STATIC)
        set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static libraries")
    endif()

    set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "Install pkgconfig files")

    if (USE_SYSTEM_DEPS)
        find_package(sfml ${SFML_VERSION} COMPONENTS graphics QUIET)
    else()
        FetchContent_Populate(sfml)

        # No need to build audio and network moduleswa
        set(SFML_BUILD_AUDIO FALSE CACHE BOOL "Build audio")
        set(SFML_BUILD_NETWORK FALSE CACHE BOOL "Build network")
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endif()
message(STATUS "${sfml_SOURCE_DIR}")