cmake_minimum_required(VERSION 3.0.0)
include(FetchContent)

FetchContent_Declare(
	json
	URL https://github.com/nlohmann/json/releases/download/v3.11.3/include.zip 
	URL_HASH SHA256=a22461d13119ac5c78f205d3df1db13403e58ce1bb1794edc9313677313f4a9d
)

FetchContent_MakeAvailable(json)

project(Manager VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_DIR /src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /bin)

set(SOURCES 
	${SOURCE_DIR}/cryptography.cpp
	${SOURCE_DIR}/cryptography.h
	${SOURCE_DIR}/globals.cpp
	${SOURCE_DIR}/globals.h
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/options.cpp
	${SOURCE_DIR}/options.h)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenSSL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${json_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)