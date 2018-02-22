CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++14
BUILD_FOLDER = build
PROGRAM_NAME = BTree
MEMORY_DEBUG_FLAGS = -m32 -g -fno-inline -fno-omit-frame-pointer
TEST_PROGRAM_NAME = BTree_tests
MEASUREMENTS_PROGRAM_NAME = measurements
PROGRAM_EXTENSION = x

all: tests
	make run
tests: compile
	$(CXX) $(CXX_FLAGS) -o $(TEST_PROGRAM_NAME).$(PROGRAM_EXTENSION) ./$(BUILD_FOLDER)/vector_tests.o ./$(BUILD_FOLDER)/testing_program.o -lcppunit
	rm -rf ./$(BUILD_FOLDER)
compile:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)
run:
	./$(TEST_PROGRAM_NAME).$(PROGRAM_EXTENSION)
clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
