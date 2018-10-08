#Main sources
SOURCES=main.cpp PSoCUART.cpp PSoCComm.cpp

#Two arch targets. Host and Target. Remember to make filefolder for directory.
ifeq ($(ARCH),host)
CXX=g++
BUILD_DIR=build/host
EXE_DIR=bin/host
endif

ifeq ($(ARCH),target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
EXE_DIR=bin/target
endif


#Set flags here.
EXE=PSoCComm
CXXFLAGS=-I.

#For no normal reason change below this reason
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))

.PHONY: clean all

# Default target
all: $(EXE)

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXE_DIR)/$@ $(OBJECTS) -lpthread


$(BUILD_DIR)/%.d: %.cpp
	$(CXX) -MT $(addprefix $(BUILD_DIR)/,$(@:.d=.o)) -MM $(CXXFLAGS) $^ > $@

$(BUILD_DIR)/%.o:%.cpp
	$(CXX) -c -o $@ $^



clean:
	rm -f bin/*/$(EXE) build/*/*.o build/*/*.d


help:
	@echo "Target"
	@echo "all"
	@echo "clean"
	@echo "help"

# Don't include (build) dependency-files when running clean
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
