# This variable is set by project() in CMake 3.20+
string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}"
    PROJECT_IS_TOP_LEVEL
)
