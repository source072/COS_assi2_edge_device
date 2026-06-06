CC=g++
SRCS=$(wildcard *.cpp data/*.cpp)
OBJS=$(SRCS:.cpp=.o)

all: edge lib

edge: $(OBJS)
	$(CC) -o $@ $^

lib: $(OBJS)
	$(AR) rcv libedge.a $(OBJS)

%.o: %.c
	$(CC) -c $< -fno-stack-protector
	@echo "CC <= $<"

clean:
	$(RM) edge libedge.a $(OBJS) 
