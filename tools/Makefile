# @file Makefile
# @date 2019/01/11
# @brief 1ファイル1app用のMakefile. sample.cpp(main関数含む)を./sampleにする. TARGETに列挙すればいい
TARGET = mkanlmodule

SOURCE_DIR := source/
BUILD_DIR := build/
BIN_DIR := bin/

CXX_DEBUG_FLAGS = -pg -O0
CXX_RELEASE_FLAGS = -s -O2

FLAGS = -I${INCLUDEPATH}

ROOTCFLAGS = `root-config --cflags`
ROOTGLIBS  = `root-config --libs`
LIBS = -lm -lfftw3 -O3 -lCOMCLI

CXX = g++
CXXFLAGS = -O2 -W -Wall ${ROOTCFLAGS} ${FLAGS}
CXXLIBS = ${ROOTGLIBS} ${LIBS}

.PHONY : release
release : CXXFLAGS += ${CXX_RELEASE_FLAGS}
release : all
.PHONY : debug
debug : CXXFLAGS += ${CXX_DEBUG_FLAGS}
debug : all

all : $(addprefix $(BUILD_DIR),$(TARGET))

$(BUILD_DIR)%: $(SOURCE_DIR)%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $< -o $@

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : install
install : $(addprefix $(BUILD_DIR),$(TARGET))
	mkdir -p $(BIN_DIR); install $< $(BIN_DIR)/

.PHONY : clean
clean :
	@rm -f $(addprefix $(BUILD_DIR),$(TARGET)) *.o *~ app*

.PHONY : uninstall
uninstall :
	@rm $(addprefix $(BIN_DIR),$(TARGET))

.PHONY : show
show :
	@echo $(addprefix $(BIN_DIR),$(TARGET))

.PHONY : cleanall
cleanall :
	rm -rf $(BIN_DIR) $(BUILD_DIR)
