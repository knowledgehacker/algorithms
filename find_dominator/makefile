SRC_DIR=$(PWD)

CXX=g++
CXXFLAGS=-c -g -W -I$(SRC_DIR)

TESTER=BTreeTester
OBJS=$(SRC_DIR)/BTree.o	\
	$(SRC_DIR)/BTreeTester.o

.PHONY: test
test: ${TESTER}
	./${TESTER}

.PHONY: comp
comp: ${TESTER}

$(TESTER): $(OBJS)
	$(CXX) $^ -o $@

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TESTER)
