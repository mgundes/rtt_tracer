PROJECT=rtt_tracer

CC = g++
CFLAGS = -std=c++11
CFLAGS += -DLOG2CONSOLE
CFLAGS += -DRTT_TRACER_VERSION=\"0.2\"
LDFLAGS = -pthread


SRC = src/main.cpp \
    src/rtt/RttTcpServer.cpp \
    src/rtt/RttTcpServer.h \
    src/rtt/RttUDP.cpp \
    src/rtt/RttUDP.h \
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
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(SRC) -o $(PROJECT)

analys: clang_analys scan-build_analys cppcheck_analys

clang_analys:
	@echo "=== Run clang analyze"
	@clang++ --analyze $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(SRC)
	@echo "=== clang analyze finished\n"

cppcheck_analys:
	@echo "=== Run cppcheck analyze ==="
	@APP=`which cppcheck`
	@if [ ! -f ${APP} ]; then \
	    echo "=== cppcheck could not found! ==="; \
	else \
	    cppcheck --enable=all src; \
	    echo "=== cppcheck analyze finished\n"; \
	fi

scan-build_analys:
	echo "=== Run scan-build analyze ===";
	@APP=`which scan-build`
	@if [ ! -f ${APP} ]; then \
	    echo "=== scan-build could not found! ==="; \
	else \
	    scan-build -v make; \
	    echo "=== scan-build analyze finished ===\n"; \
	fi

clean:
	find -iname "*.o" | xargs rm -f
	rm -f $(PROJECT)
