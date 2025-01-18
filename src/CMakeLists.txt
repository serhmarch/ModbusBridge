cmake_minimum_required(VERSION 3.5) # 2.2 - case insensitive syntax

project(mbridge VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(MBRIDGE_SERVER_APP_NAME ${PROJECT_NAME})

message("MBRIDGE: Start configure '${MBRIDGE_SERVER_APP_NAME}'")

set(HEADERS
    modbus/mtcpclient.h
    modbus/mtcpbridge.h
)

set(SOURCES
    modbus/mtcpclient.cpp
    modbus/mtcpbridge.cpp
    mbridge.cpp
)     

set(RESOURCES 
)     

add_executable(${MBRIDGE_SERVER_APP_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})

include_directories(.
                    ..
                    ../modbus/src
)

set_target_properties(
    ${MBRIDGE_SERVER_APP_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    #WIN32_EXECUTABLE true
)

target_link_libraries(${MBRIDGE_SERVER_APP_NAME} PRIVATE 
                      modbus
)

