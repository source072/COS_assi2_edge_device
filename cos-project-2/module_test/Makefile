SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: test_process_data

test_process_data: test_process_data.o
	g++ -o $@ $< -L../edge -ledge

%.o: %.c
	$(CC) -c $< $(COMMON_CFLAGS)
	@echo "CC <= $<"

clean:
	$(RM) test_process_data $(OBJS) 
