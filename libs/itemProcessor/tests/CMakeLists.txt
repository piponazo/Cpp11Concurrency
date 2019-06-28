add_executable(testsItemProcessor
    testMain.cpp
    testItemProcessor.cpp
)

target_link_libraries(testsItemProcessor
    PRIVATE
        itemProcessor
        Catch2::Catch2
)
