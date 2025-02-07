#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* 
    This is your test file.
*/

// Test 1 is given to you
void test1() {
    queue_t new = queue_new();
    if (new == NULL) {
        fprintf(stderr, "test1: queue_new failed\n");
        exit(1);
    }
	int r = queue_free(new);
    if (r != 0) {
        fprintf(stderr, "test1: queue_free() returned %d instead of 0\n", r);
        exit(1);
    }
}

/*Tests enqueue, dequeue, and length operations*/
void test2() {
    queue_t queue = queue_new();
    int a = 10, b = 20, c = 30;

    if (queue_length(queue) != 0) {
        fprintf(stderr, "test2: queue_length incorrect after construction\n");
        exit(1);
    }
    if (queue_enqueue(queue, &a) != 0) {
        fprintf(stderr, "test2: queue_enqueue a failed\n");
        exit(1);
    }
    if (queue_length(queue) != 1) {
        fprintf(stderr, "test2: queue_length incorrect after enqueue\n");
        exit(1);
    }
    if (queue_enqueue(queue, &b) != 0) {
        fprintf(stderr, "test2: queue_enqueue b failed\n");
        exit(1);
    }
    if (queue_length(queue) != 2) {
        fprintf(stderr, "test2: queue_length incorrect after enqueue\n");
        exit(1);
    }
    if (queue_enqueue(queue, &c) != 0) {
        fprintf(stderr, "test2: queue_enqueue c failed\n");
        exit(1);
    }
    if (queue_length(queue) != 3) {
        fprintf(stderr, "test2: queue_length incorrect after enqueue\n");
        exit(1);
    }

    int* item;
    if (queue_dequeue(queue, (void**)&item) != 0 || *item != 10) {
        fprintf(stderr, "test2: queue_dequeue did not return 10\n");
        exit(1);
    }
    if (queue_length(queue) != 2) {
        fprintf(stderr, "test2: queue_length incorrect after dequeue\n");
        exit(1);
    }
    if (queue_dequeue(queue, (void**)&item) != 0 || *item != 20) {
        fprintf(stderr, "test2: queue_dequeue did not return 20\n");
        exit(1);
    }
    if (queue_length(queue) != 1) {
        fprintf(stderr, "test2: queue_length incorrect after dequeue\n");
        exit(1);
    }
    if (queue_dequeue(queue, (void**)&item) != 0 || *item != 30) {
        fprintf(stderr, "test2: queue_dequeue did not return 30\n");
        exit(1);
    }
    if (queue_length(queue) != 0) {
        fprintf(stderr, "test2: queue_length incorrect after dequeue\n");
        exit(1);
    }

    if (queue_free(queue) != 0) {
        fprintf(stderr, "test2: queue_free failed\n");
        exit(1);
    }
}

/* Tests delete and insert methods */
void test3() {
    queue_t queue = queue_new();
    int a = 1, b = 2, c = 3, d=4;

    queue_enqueue(queue, &a);
    queue_enqueue(queue, &b);
    queue_enqueue(queue, &c);

    // Delete head
    if (queue_delete(queue, &a) != 0) {
        fprintf(stderr, "test3: queue_delete head failed\n");
        exit(1);
    }
    if (queue_insert(queue,&d)!=0){
        fprintf(stderr, "test3: queue_insert failed\n");
        exit(1);
    }

    int* item;
    queue_dequeue(queue, (void**)&item);
    if (*item != 4) {
        fprintf(stderr, "test3: after inserting 4, incorrect dequeue value\n");
        exit(1);
    }
    
    if (queue_delete(queue, &c) != 0) {
        fprintf(stderr, "test3: queue_delete tail failed\n");
        exit(1);
    }
    if (queue_dequeue(queue,NULL)!=0){
        fprintf(stderr, "test3: final item not dequeued\n");
        exit(1);
    }

    if (queue_length(queue) != 0) {
        fprintf(stderr, "test3: queue_length incorrect after deletions\n");
        exit(1);
    }

    if (queue_free(queue) != 0) {
        fprintf(stderr, "test3: queue_free failed\n");
        exit(1);
    }
}

/* Tests various methods on an empty queue */
void test4() {
    queue_t queue = queue_new();

    int* item;
    if (queue_dequeue(queue, (void**)&item) == 0) {
        fprintf(stderr, "test4: dequeue from empty queue did not fail\n");
        exit(1);
    }
    int data = 5;
    if (queue_delete(queue, &data) == 0) {
        fprintf(stderr, "test4: delete from empty queue did not fail\n");
        exit(1);
    }

    if (queue_free(queue) != 0) {
        fprintf(stderr, "test4: queue_free failed\n");
        exit(1);
    }
}


int main(void) {
    test1();
	test2();
    test3();
    test4();
	// ...
	return 0;
}
