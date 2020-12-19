find_path(NONIUS_LIB_DIR 
    NAMES "nonius/nonius.h++"
    PATHS "nonius/include"
    )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(NONIUS NONIUS_LIB_DIR)

if(NONIUS_FOUND AND NOT TARGET Nonius::Nonius)
    add_library(Nonius::Nonius INTERFACE IMPORTED)
    target_include_directories(Nonius::Nonius INTERFACE "${NONIUS_LIB_DIR}")
endif()

mark_as_advanced(NONIUS_LIB_DIR) 
