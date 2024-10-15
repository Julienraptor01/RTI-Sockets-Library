### paths
# sources
SRC=./src
# sources sub directories
MAIN=/main
# sources -> main
MAIN_SRC=$(SRC)$(MAIN)
# build
BUILD=./build
# build sub directories
OBJS=/obj
BINS=/bin
# build -> objs -> (*)
OBJ=$(BUILD)$(OBJS)
MAIN_OBJ=$(OBJ)$(MAIN)
# build -> bins -> (*)
BIN=$(BUILD)$(BINS)
MAIN_BIN=$(BIN)$(MAIN)
# logs
LOGS=./logs

### lists
# use a generic rule to list all the headers
MAIN_HEADERS=$(wildcard $(MAIN_SRC)/*.h)
# use a generic rule to list all the objects
MAIN_OBJECTS=$(patsubst $(MAIN_SRC)/%.cpp,$(MAIN_OBJ)/%.o,$(wildcard $(MAIN_SRC)/*.cpp))

### commands
# compiler
CXX=g++
# compiler flags
ifdef DEBUG
CXXFLAGS=-std=gnu++23 -Wall -Wextra -g -Og
else
CXXFLAGS=-std=gnu++23 -Wall -Wextra -O3
endif
CPPFLAGS=
MAIN_CPPFLAGS=$(CPPFLAGS) -I$(MAIN_SRC)
# linker flags
LDFLAGS=
# compilation
MAIN_COMPILE=$(CXX) $(CXXFLAGS) $(MAIN_CPPFLAGS) -c $< -o $@
# linking
MAIN_LINK=$(CXX) $^ -o $@ $(LDFLAGS)
# deletion
RM=rm -rf
# silent log
LOG=@printf

.PHONY: all build setup clean full-clean
.SECONDARY: $(OBJECTS)

all: setup build

$(MAIN_OBJ)/%.o: $(MAIN_SRC)/%.cpp $(MAIN_HEADERS)
	$(LOG) '\n\033[42mcreation of the $* object file\033[49m\n'
	$(MAIN_COMPILE)

$(MAIN_BIN)/%: $(MAIN_OBJ)/%.o $(MAIN_OBJECTS)
	$(LOG) '\n\033[42mcreation of the $* executable\033[49m\n'
	$(MAIN_LINK)

build:
	$(LOG) '\n\033[42mbuilding the main executable\033[49m\n'
	make $(MAIN_BIN)/main
	$(LOG) '\n\033[44mmake build finished\033[49m\n\n'

setup:
	$(LOG) '\n\033[42msetup of the directories\033[49m\n'
	mkdir \
	-p \
	$(MAIN_OBJ) \
	$(MAIN_BIN) \
	$(LOGS)
	$(LOG) '\n\033[44mmake setup finished\033[49m\n\n'

clean:
	$(LOG) '\n\033[41mdeletion of the object directory\033[49m\n'
	$(RM) $(OBJ)/*
	make setup
	$(LOG) '\n\033[44mmake clean finished\033[49m\n\n'

full-clean:
	$(LOG) '\n\033[41mdeletion of ALL the build directories\033[49m\n'
	$(RM) $(BUILD)/*
	make setup
	$(LOG) '\n\033[44mmake full-clean finished\033[49m\n\n'
