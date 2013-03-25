
# ----------------------------------------------------------------------------
#  Get actual pat version number from sources
# ----------------------------------------------------------------------------
set(pat_version_file "${CMAKE_CURRENT_SOURCE_DIR}/lib/include/pat/version.hpp")
file(STRINGS "${pat_version_file}" pat_version_parts REGEX "#define PAT_VERSION_.+[ ]+[0-9]+" )
string(REGEX REPLACE ".+PAT_VERSION_MAJOR[ ]+([0-9]+).*" "\\1"  PAT_VERSION_MAJOR  "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_VERSION_MINOR[ ]+([0-9]+).*" "\\1"  PAT_VERSION_MINOR  "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_VERSION_PATCH[ ]+([0-9]+).*" "\\1"  PAT_VERSION_PATCH  "${pat_version_parts}")
set(pat_version "${PAT_VERSION_MAJOR}.${PAT_VERSION_MINOR}.${PAT_VERSION_PATCH}")
# ----------------------------------------------------------------------------
