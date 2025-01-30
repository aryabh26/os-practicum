test_queue: test_queue.o queue.o
	$(CC) -Wall -o test_queue queue.o test_queue.o

queue.o: queue.h queue.c
test_queue.o: queue.h test_queue.c

clean:
	rm -f *.o *.gch a.out test_queue
