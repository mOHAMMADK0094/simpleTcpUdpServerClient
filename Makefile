CXX = g++
CXXFLAGS = -Werror -std=c++11

SRCS = main.cc server.cc client.cc

TARGET = simpleTcpUdpServerClient

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) 
.PHONY: clean
clean:
	rm -f $(TARGET)