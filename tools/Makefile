# @file Makefile
# @date 2019/01/11
# @brief 1ファイル1app用のMakefile. sample.cpp(main関数含む)を./sampleにする. TARGETに列挙すればいい
TARGET = mkanlmodule mkdatabase

SOURCE_DIR := source/
BUILD_DIR := build/
BIN_DIR := bin/

CXX = g++
CXXFLAGS = -std=c++11 -o3 `root-config --cflags`
CXXLIBS = -lCOMCLI `root-config --libs`

all : $(addprefix $(BUILD_DIR),$(TARGET))

$(BUILD_DIR)%: $(SOURCE_DIR)%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $< -o $@

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : install
install : $(shell ls $(BUILD_DIR))
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
