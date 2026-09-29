CXX = g++
CXXFLAGS = -std=c++23 -fdiagnostics-color=always -g -Iinclude
LDLIBS = -lsqlite3
TARGET = out/main
DB = db/*.db

SRC = src/*.cpp


build:
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) $(DB)
