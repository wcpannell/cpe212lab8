#Makefile for graphs assignment 19
CXX=clang++
EXECUTER = "./"

TEST_FILES=$(wildcard test_*.cpp)
CXX_FLAGS=-Wall -Wextra -Wpedantic -std=c++98

graph_driver:  graph_driver.o LList.h NodeType.h Vertex.h
	$(CXX) $(CXX_FLAGS) $^ -o $@

test_%: test_%.cpp
	$(CXX) $(CXX_FLAGS) -g $^ -o $@
	@$(EXECUTER)test_$*

%.o: %.cpp %.h
	$(CXX) $(CXX_FLAGS) -c -g $^

.PHONY: clean
clean:
	rm -f *.o $(TEST_FILES:%.cpp=%)

.PHONY: test
test:
	@make clean
	@$(foreach test, $(TEST_FILES:%.cpp=%), make --no-print-directory $(test);)

.PHONY: test
vtest:
	make test EXECUTER="valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./"
