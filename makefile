FLAGS = -m64 --std=c++11 -g
HEADERS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	g++ $(FLAGS) -o order $(OBJS)


$(OBJS): %.o: %.cpp $(HEADERS)
	g++ -c $(FLAGS) -o $@ $<


t: $(OBJS)
	echo $(OBJS)


unit_test: $(SRCS) test/test.cpp $(HEADERS)
	g++ OrderBookManager.cpp  -L./test -I./test -pthread test/test.cpp -lgtest -lgmock -o unit_test ${FLAGS}

clean:
	rm -f order unit_test *.o