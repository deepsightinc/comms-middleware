enable_testing()

add_subdirectory(fakes)

find_package(GTest REQUIRED)

add_executable(unit_tests)

set(PROTO_SOURCES testPayload.proto)
protobuf_generate_cpp(LIB_SOURCES LIB_HEADERS ${PROTO_SOURCES})
target_sources(unit_tests PRIVATE
        ${LIB_HEADERS}
        ${LIB_SOURCES}
        test_middleware.cpp)

target_include_directories(unit_tests PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${Protobuf_INCLUDE_DIRS})

target_link_libraries(unit_tests PRIVATE Comms Comms_testing)
target_link_libraries(unit_tests PRIVATE GTest::gtest)
target_link_libraries(unit_tests PRIVATE ${Protobuf_LIBRARIES})
