# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LLM VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Manually set MbedTLS variables so CPR can find them
set(MBEDTLS_INCLUDE_DIRS ${mbedtls_SOURCE_DIR}/include)
set(MBEDTLS_LIBRARY ${mbedtls_SOURCE_DIR}/build/library/libmbedtls.a)
set(MBEDX509_LIBRARY ${mbedtls_SOURCE_DIR}/build/library/libmbedx509.a)
set(MBEDCRYPTO_LIBRARY ${mbedtls_SOURCE_DIR}/build/library/libmbedcrypto.a)

set(CPR_FORCE_USE_SYSTEM_SSL OFF)
set(CPR_ENABLE_SSL ON)
set(CMAKE_PREFIX_PATH ${mbedtls_SOURCE_DIR})

#zlib
set(zlib_SOURCE_DIR "../include/zlib")
FetchContent_Declare(
  zlib
  SOURCE_DIR ${zlib_SOURCE_DIR}
)
FetchContent_MakeAvailable(zlib)

#cpr
set(cpr_SOURCE_DIR "../include/cpr")
FetchContent_Declare(
  cpr
  SOURCE_DIR ${cpr_SOURCE_DIR}
)
set(CPR_BUILD_TESTS OFF)
FetchContent_MakeAvailable(cpr)

set(SOURCES src/main.cpp)

set(LINK_LIBRARIES cpr::cpr)

# Add the executable
add_executable(LLM ${SOURCES})

target_link_libraries(LLM ${LINK_LIBRARIES})