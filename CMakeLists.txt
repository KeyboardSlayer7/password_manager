cmake_minimum_required(VERSION 3.0.0)
include(FetchContent)

FetchContent_Declare(
	json
	URL https://github.com/nlohmann/json/releases/download/v3.11.3/include.zip 
	URL_HASH SHA256=a22461d13119ac5c78f205d3df1db13403e58ce1bb1794edc9313677313f4a9d
)

FetchContent_MakeAvailable(json)

project(Manager VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES 
	${SOURCE_DIR}/cryptography.cpp
	${SOURCE_DIR}/cryptography.h
	${SOURCE_DIR}/globals.cpp
	${SOURCE_DIR}/globals.h
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/options.cpp
	${SOURCE_DIR}/options.h
	${SOURCE_DIR}/app.h
	${SOURCE_DIR}/app.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenSSL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${json_SOURCE_DIR}/single_include)

target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)

set(DLL_FILES 
    ${OPENSSL_ROOT_DIR}/libcrypto-3.dll
    ${OPENSSL_ROOT_DIR}/libssl-3.dll
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${DLL_FILES}
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}
)