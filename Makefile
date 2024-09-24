CC := llvm-g++
SRC := ./src
BUILD := ./build

DEPS := main.o input_handler.o
INC_DEPS := $(addprefix $(BUILD)/,$(DEPS))

INC_DIRS := $(shell find $(SRC) -type d) 
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
FLAGS := $(INC_FLAGS) -std=c++23

LD := -lncurses

%.o : $(SRC)/%.cc
	$(CC) -c $(FLAGS) $< -o $(BUILD)/$@

scribble: $(DEPS) 
	$(CC) -o $@ $(INC_DEPS) $(LD) 

.PHONY: clean
clean:
	rm scribble 
	rm $(BUILD)/* 
