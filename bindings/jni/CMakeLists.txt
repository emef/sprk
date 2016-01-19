cmake_minimum_required (VERSION 2.8)

project (sprkjni CXX)
enable_language (C)

find_package (JNI REQUIRED)
find_library (ZMQ_LIBRARY NAMES zmq libzmq REQUIRED)
find_library (SPRK_LIBRARY NAMES sprk REQUIRED)

include_directories (${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} src/native/include)

set (sprkjni_sources
    src/main/c/org_zeromq_sprk_SprkCtx.c
    src/main/c/org_zeromq_sprk_SprkDataset.c
    src/main/c/org_zeromq_sprk_Descriptor.c
    src/main/c/org_zeromq_sprk_Transformation.c
)

add_library (sprkjni SHARED ${sprkjni_sources})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O2")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

target_link_libraries (sprkjni ${ZMQ_LIBRARY} ${SPRK_LIBRARY})
