CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = main.cc server.cc client.cc
OBJS = $(SRCS:.cc=.o)

TARGET = simpleTcpUdpServerClient

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) && rm *.o

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)