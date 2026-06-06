CC=g++
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: edge

edge: $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< -fno-stack-protector
	@echo "CC <= $<"

clean:
	$(RM) edge $(OBJS) 
