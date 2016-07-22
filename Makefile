PROJECT=rtt_tracer

CFLAGS = -std=c++0x # -static cause runtime problem somehow
#CFLAGS += -DLOG2CONSOLE
CFLAGS += -DRTT_TRACER_VERSION=\"0.2\"
LDFLAGS = -pthread


SRC = src/main.cpp \
    src/rtt/RttTcpServer.cpp \
    src/rtt/RttTcpServer.h \
    src/rtt/RttUDP.cpp \
    src/rtt/RttUDP.h \
    src/utils/Logger.cpp \
    src/utils/Logger.h \
    src/utils/LogManager.cpp \
    src/utils/LogManager.h \
    src/utils/easylogging++.h \
    src/rtt/RttPayload.cpp \
    src/rtt/RttPayload.h \
    src/utils/TimeUtils.cpp \
    src/utils/TimeUtils.h \
    src/utils/Utils.h \
    src/utils/Utils.cpp \
    src/rtt/RttTcpClient.cpp \
    src/rtt/RttTcpClient.h

INCLUDES = -I src/rtt/ -I src/utils/

all:
	g++ $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(SRC) -o $(PROJECT)


clean:
	find -iname "*.o" | xargs rm -f
	rm -f $(PROJECT)
