include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(
	MagicLantern_INCLUDE_DIR
	NAMES mle.h
	PATHS /opt/MagicLantern/include
	PATH_SUFFIXES mle
)
find_library(
	MagicLantern_LIBRARY_DEBUG
	NAMES mlertd
	PATHS /opt/MagicLantern/lib
	PATH_SUFFIXES mle
)
find_library(
	MagicLantern_LIBRARY_RELEASE
	NAMES mlert
	PATHS /opt/MagicLantern/lib
	PATH_SUFFIXES mle mle/rehearsal mle/runtime
)
select_library_configurations(MagicLantern)

if(MagicLantern_INCLUDE_DIR AND EXISTS "${MagicLantern_INCLUDE_DIR}/mle/mlBasic.h")
	file(STRINGS "${MagicLantern_INCLUDE_DIR}/mle/mlBasic.h" _MagicLantern_VERSION_DEFINE REGEX "[\t ]*#define[\t ]+MLE_VERSION[\t ]+\"[^\"]*\".*")
	string(REGEX REPLACE "[\t ]*#define[\t ]+MLE_VERSION[\t ]+\"([^\"]*)\".*" "\\1" MagicLantern_VERSION "${_MagicLantern_VERSION_DEFINE}")
	unset(_MagicLantern_VERSION_DEFINE)
endif()

set(MagicLantern_DEFINITIONS -DCOIN_DLL)
set(MagicLantern_INCLUDE_DIRS ${MagicLantern_INCLUDE_DIR})
set(MagicLantern_LIBRARIES ${MagicLantern_LIBRARY})

find_package_handle_standard_args(
	MagicLantern
	FOUND_VAR MagicLantern_FOUND
	REQUIRED_VARS MagicLantern_INCLUDE_DIR MagicLantern_LIBRARY
	VERSION_VAR MagicLantern_VERSION
)

if(MagicLantern_FOUND AND NOT TARGET MagicLantern::MagicLantern)
	add_library(MagicLantern::MagicLantern UNKNOWN IMPORTED)
	if(MagicLantern_LIBRARY_RELEASE)
		set_property(TARGET MagicLantern::MagicLantern APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
		set_target_properties(MagicLantern::MagicLantern PROPERTIES IMPORTED_LOCATION_RELEASE "${MagicLantern_LIBRARY_RELEASE}")
	endif()
	if(MagicLantern_LIBRARY_DEBUG)
		set_property(TARGET MagicLantern::MagicLantern APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
		set_target_properties(MagicLantern::MagicLantern PROPERTIES IMPORTED_LOCATION_DEBUG "${MagicLantern_LIBRARY_DEBUG}")
	endif()
	set_target_properties(MagicLantern::MagicLantern PROPERTIES INTERFACE_COMPILE_DEFINITIONS "COIN_DLL")
	set_target_properties(MagicLantern::MagicLantern PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${MagicLantern_INCLUDE_DIRS}")
endif()

mark_as_advanced(MagicLantern_DEFINITIONS)
mark_as_advanced(MagicLantern_INCLUDE_DIR)
mark_as_advanced(MagicLantern_FOREIGN_FILES_INCLUDE_DIR)
