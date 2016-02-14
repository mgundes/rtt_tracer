cmake_minimum_required(VERSION 3.3)
project(network_diagnostics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/rtt/RttTcpServer.cpp src/rtt/RttTcpServer.h src/rtt/RttUDP.cpp src/rtt/RttUDP.h src/utils/Logger.cpp src/utils/Logger.h src/rtt/RttPayload.cpp src/rtt/RttPayload.h src/utils/TimeUtils.cpp src/utils/TimeUtils.h src/rtt/RttTcpClient.cpp src/rtt/RttTcpClient.h)
add_executable(network_diagnostics ${SOURCE_FILES})