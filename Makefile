CC = gcc
CXX = g++
CFLAGS += -lncurses
SRC_DIR = ./
CPP_FILES = $(shell find $(SRC_DIR) -name "*.cpp")
HPP_FILES = $(shell find $(SRC_DIR) -name "*.hpp")
PVZ = PVZ

$(PVZ): $(CPP_FILES) $(HPP_FILES)
	$(CXX) $(CPP_FILES) -o $@ $(CFLAGS)

run: $(PVZ)
	./$< 

debug: $(CPP_FILES) $(HPP_FILES)
	$(CXX) $(CPP_FILES) -o $@ $(CFLAGS) -g

clean:
	rm $(PVZ) debug
