add_library(itemProcessor
    include/itemProcessor/processor.h
    src/processor.cpp
)

generate_export_header(itemProcessor
    EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/itemProcessor_export.h
)

target_include_directories(itemProcessor PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/itemProcessor/include>
    $<INSTALL_INTERFACE:include>
)

if (Catch2_FOUND)
    add_subdirectory(tests)
endif()
