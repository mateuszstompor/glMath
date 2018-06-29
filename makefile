CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++14 -I.
BUILD_FOLDER = build
MEMORY_DEBUG_FLAGS = -m32 -g -fno-inline -fno-omit-frame-pointer

MATRIX_TESTS = matrix_tests.x
VECTOR_TESTS = vector_tests.x
PLANE_TESTS = plane.x
BOUNDING_BOX_TESTS = bounding_box.x
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=1 --show-leak-kinds=definite --errors-for-leak-kinds=definite

all:
	make tests
	make mem_check

tests: link
	make test_matrix
	make test_vector
	make test_plane
	make test_bounding_box

link: compile
	$(CXX) $(CXX_FLAGS) -o $(VECTOR_TESTS) ./$(BUILD_FOLDER)/vector_tests.o ./$(BUILD_FOLDER)/vector_testing_program.o -lcppunit
	$(CXX) $(CXX_FLAGS) -o $(MATRIX_TESTS) ./$(BUILD_FOLDER)/matrix_tests.o ./$(BUILD_FOLDER)/matrix_testing_program.o -lcppunit
	$(CXX) $(CXX_FLAGS) -o $(PLANE_TESTS) ./$(BUILD_FOLDER)/plane_tests.o ./$(BUILD_FOLDER)/plane_testing_program.o -lcppunit
	$(CXX) $(CXX_FLAGS) -o $(BOUNDING_BOX_TESTS) ./$(BUILD_FOLDER)/boundingbox_tests.o ./$(BUILD_FOLDER)/boundingbox_testing_program.o -lcppunit
	rm -rf ./$(BUILD_FOLDER)

compile:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/matrix/*.cpp
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/vector/*.cpp
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/bounding_box/*.cpp
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/plane/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

test_matrix: link
	./$(MATRIX_TESTS)

test_vector: link
	./$(VECTOR_TESTS)

test_plane: link
	./$(PLANE_TESTS)

test_bounding_box: link
	./$(BOUNDING_BOX_TESTS)

mem_check_plane: link
	valgrind $(VALGRIND_FLAGS) ./$(PLANE_TESTS)

mem_check_bounding_box: link
	valgrind $(VALGRIND_FLAGS) ./$(BOUNDING_BOX_TESTS)

mem_check_matrix: link
	valgrind $(VALGRIND_FLAGS) ./$(MATRIX_TESTS)

mem_check_vector: link
	valgrind $(VALGRIND_FLAGS) ./$(VECTOR_TESTS)

mem_check: link
	make mem_check_matrix
	make mem_check_vector
	make mem_check_plane
	make mem_check_bounding_box

clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
	rm -f *.o
	rm -rf *.dSYM
