SRC := $(shell find apryxscript-core/src -name "*.cpp")
OBJ = $(SRC:%.cpp=%.o)

CC_FLAGS := -IDependencies/boost -Iapryxscript-core/src -std=c++11 -Wall

BIN := bin
EXECUTABLE := main

# all is the target (you would run make all from the command line). 'all' is dependent
# on $(BIN)
all: $(BIN)

#$(BIN) is dependent on objects
$(BIN): $(OBJ)
	g++ -o $(EXECUTABLE) $^

#each object file is dependent on its source file, and whenever make needs to create
# an object file, to follow this rule:
%.o: %.cpp
	g++ $(CC_FLAGS) -c $< -o $@

setup:
	mkdir bin
clean:
	find . -name "*.o" -type f -delete
	rm main
	rm bin/*

