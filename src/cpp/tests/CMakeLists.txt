set(TEST_NAME "test_${PROJECT_NAME}")

add_executable(${TEST_NAME} "${TEST_NAME}.cpp")
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

target_compile_options(${TEST_NAME} PRIVATE)
target_include_directories(${TEST_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${TEST_NAME} PUBLIC ${PROJECT_NAME})

get_target_property(target_sources ${TEST_NAME} SOURCES)
foreach(source ${target_sources})
    set_property(GLOBAL APPEND PROPERTY CLANG_FORMAT_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
endforeach(source)
