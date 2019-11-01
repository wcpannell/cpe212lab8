#Makefile for graphs assignment 19

TEST_FILES=$(wildcard test_*.cpp)
CXX_FLAGS=-Wall -Wextra -Wpedantic

graph_driver:  graph_driver.o LList.h NodeType.h Vertex.h
	g++ $(CXX_FLAGS) -o $@ $^

test_%: test_%.cpp %.h
	g++ $(CXX_FLAGS) -g -o $@ $^
	./test_$*

%.o: %.cpp %.h
	g++ $(CXX_FLAGS) -c -g $^

.PHONY: clean
clean:
	rm -f *.o $(TEST_FILES:%.cpp=%)

.PHONY: test
test:
	@make clean
	@$(foreach test, $(TEST_FILES:%.cpp=%), make $(test);)
