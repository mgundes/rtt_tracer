
PROJECT=rtt_tracer

CFLAGS = -static -std=c++0x


SRC = src/main.cpp \
    src/rtt/RttTcpServer.cpp \
    src/rtt/RttTcpServer.h \
    src/rtt/RttUDP.cpp \
    src/rtt/RttUDP.h \
    src/utils/Logger.cpp \
    src/utils/Logger.h \
    src/rtt/RttPayload.cpp \
    src/rtt/RttPayload.h \
    src/utils/TimeUtils.cpp \
    src/utils/TimeUtils.h \
    src/rtt/RttTcpClient.cpp \
    src/rtt/RttTcpClient.h

INCLUDES = -I src/rtt/ -I src/utils/

all:
	g++ $(CFLAGS) $(INCLUDES) $(SRC) -o $(PROJECT)


clean:
	find -iname "*.o" | xargs rm -f
	rm -f $(PROJET)
