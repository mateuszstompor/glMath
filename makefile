CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++14
BUILD_FOLDER = build
MEMORY_DEBUG_FLAGS = -m32 -g -fno-inline -fno-omit-frame-pointer

MATRIX_TESTS = matrix_tests.x
VECTOR_TESTS = vector_tests.x
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all

all: link
	make test_matrix
	make test_vector
	make mem_check_matrix
	make mem_check_vector

link: compile
	$(CXX) $(CXX_FLAGS) -o $(VECTOR_TESTS) ./$(BUILD_FOLDER)/vector_tests.o ./$(BUILD_FOLDER)/vector_testing_program.o -lcppunit
	$(CXX) $(CXX_FLAGS) -o $(MATRIX_TESTS) ./$(BUILD_FOLDER)/matrix_tests.o ./$(BUILD_FOLDER)/matrix_testing_program.o -lcppunit
	rm -rf ./$(BUILD_FOLDER)

compile:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/matrix/*.cpp
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/vector/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

test_matrix: compile
	./$(MATRIX_TESTS)

test_vector: compile
	./$(VECTOR_TESTS)

mem_check_matrix:
	valgrind $(VALGRIND_FLAGS) ./$(MATRIX_TESTS)

mem_check_vector:
	valgrind $(VALGRIND_FLAGS) ./$(VECTOR_TESTS)

clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
