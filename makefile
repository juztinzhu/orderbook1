FLAGS = -m64 --std=c++11
HEADERS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	g++ $(FLAGS) -o test $(OBJS)


$(OBJS): %.o: %.cpp $(HEADERS)
	g++ -c $(FLAGS) -o $@ $<


t: $(OBJS)
	echo $(OBJS)

clean:
	rm test
	rm *.o
