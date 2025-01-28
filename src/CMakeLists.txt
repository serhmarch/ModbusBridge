cmake_minimum_required(VERSION 3.5) # 2.2 - case insensitive syntax

project(mbridge VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(MBRIDGE_APP_NAME ${PROJECT_NAME})

message("MBRIDGE: Start configure '${MBRIDGE_APP_NAME}'")

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

if (WIN32)
    set(MBRIDGE_WIN_RESOURCE_FILE win_resource.rc)
        message("${PROJECT_NAME} resource file for Windows: '${MBRIDGE_WIN_RESOURCE_FILE}'")

    set(MBRIDGE_WIN_FILE "${PROJECT_NAME}")
    set(MBRIDGE_WIN_OUTFILE "${MBRIDGE_APP_NAME}.exe")
    configure_file(${CMAKE_CURRENT_LIST_DIR}/${MBRIDGE_WIN_RESOURCE_FILE}.in 
                   ${CMAKE_CURRENT_LIST_DIR}/${MBRIDGE_WIN_RESOURCE_FILE})

    set(RESOURCES ${RESOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/${MBRIDGE_WIN_RESOURCE_FILE}           
    )     
endif()

add_executable(${MBRIDGE_APP_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})

include_directories(.
                    ..
                    ../modbus/src
)

set_target_properties(
    ${MBRIDGE_APP_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    #WIN32_EXECUTABLE true
)

target_link_libraries(${MBRIDGE_APP_NAME} PRIVATE 
                      modbus
)

