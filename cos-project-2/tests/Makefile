SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: test_client test_process test_client_answer test_process_answer

test_client: test_client.o
	g++ -o $@ $<

test_client_answer: test_client_answer.o
	g++ -o $@ $<

test_process: test_process.o
	g++ -o $@ $< -L../edge -ledge

test_process_answer: test_process_answer.o
	g++ -o $@ $< -L../edge -ledge

%.o: %.c
	$(CC) -c $< $(COMMON_CFLAGS)
	@echo "CC <= $<"

clean:
	$(RM) test_client test_process test_client_answer test_process_answer $(OBJS) 
