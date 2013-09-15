SRC_DIR=$(PWD)

CXX=g++
CXXFLAGS=-c -g -W -I$(SRC_DIR)

TESTER=Main
OBJS=$(SRC_DIR)/Point.o	\
	$(SRC_DIR)/KMinHeap.o	\
	$(SRC_DIR)/Finder.o	\
	$(SRC_DIR)/Main.o

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
