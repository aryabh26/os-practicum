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

/* A helper function to use with queue_iterate */
void increment_item(void* data, void* context)
{
    *(int*)data += *(int*)context;
}

/* 
 * Test 5: Test queue_iterate()
 */
void test5() {
    queue_t q = queue_new();
    if (!q) {
        fprintf(stderr, "test5: queue_new failed\n");
        exit(1);
    }

    int a = 10, b = 20, c = 30;
    queue_enqueue(q, &a);
    queue_enqueue(q, &b);
    queue_enqueue(q, &c);


    int increment_amt = 5;
    queue_iterate(q, increment_item, &increment_amt);

    int* item;
    if (queue_dequeue(q, (void**)&item) != 0 || *item != 15) {
        fprintf(stderr, "test5: queue_iterate did not increment item from 10 to 15\n");
        exit(1);
    }

    if (queue_dequeue(q, (void**)&item) != 0 || *item != 25) {
        fprintf(stderr, "test5: queue_iterate did not increment item from 20 to 25\n");
        exit(1);
    }

    if (queue_dequeue(q, (void**)&item) != 0 || *item != 35) {
        fprintf(stderr, "test5: queue_iterate did not increment item from 30 to 35\n");
        exit(1);
    }

    if (queue_length(q) != 0) {
        fprintf(stderr, "test5: queue_length is not 0 after dequeues\n");
        exit(1);
    }

    if (queue_free(q) != 0) {
        fprintf(stderr, "test5: queue_free failed\n");
        exit(1);
    }
}

/*
 * Test 6: Dequeue with pitem == NULL (i.e., remove from queue but don't retrieve the item).
 */
void test6() {
    queue_t q = queue_new();
    if (!q) {
        fprintf(stderr, "test6: queue_new failed\n");
        exit(1);
    }

    int a = 100, b = 200;
    queue_enqueue(q, &a);
    queue_enqueue(q, &b);

    if (queue_dequeue(q, NULL) != 0) {
        fprintf(stderr, "test6: queue_dequeue with NULL pitem failed\n");
        exit(1);
    }

    if (queue_length(q) != 1) {
        fprintf(stderr, "test6: queue_length mismatch after dequeue with NULL\n");
        exit(1);
    }

    int* item;
    if (queue_dequeue(q, (void**)&item) != 0 || *item != 200) {
        fprintf(stderr, "test6: queue_dequeue did not return the remaining item (200)\n");
        exit(1);
    }

    if (queue_length(q) != 0) {
        fprintf(stderr, "test6: queue_length not 0 after removing all items\n");
        exit(1);
    }

    if (queue_free(q) != 0) {
        fprintf(stderr, "test6: queue_free failed\n");
        exit(1);
    }
}

/*
 * Test 7: Attempt to free a non-empty queue.
 */
void test7() {
    queue_t q = queue_new();
    if (!q) {
        fprintf(stderr, "test7: queue_new failed\n");
        exit(1);
    }

    int a = 1;
    queue_enqueue(q, &a);

    if (queue_free(q) != -1) {
        fprintf(stderr, "test7: queue_free succeeded on a non-empty queue, should have failed\n");
        exit(1);
    }

    if (queue_dequeue(q, NULL) != 0) {
        fprintf(stderr, "test7: queue_dequeue failed\n");
        exit(1);
    }

    if (queue_free(q) != 0) {
        fprintf(stderr, "test7: queue_free failed after emptying\n");
        exit(1);
    }
}

/*
 * Test 8: Tests delete with multiple identical items in the queue. 
 */
void test8() {
    queue_t q = queue_new();
    if (!q) {
        fprintf(stderr, "test8: queue_new failed\n");
        exit(1);
    }

    int x = 100;
    queue_enqueue(q, &x);
    queue_enqueue(q, &x);
    queue_enqueue(q, &x);

    if (queue_delete(q, &x) != 0) {
        fprintf(stderr, "test8: queue_delete failed to remove the first occurrence\n");
        exit(1);
    }

    if (queue_length(q) != 2) {
        fprintf(stderr, "test8: queue_length should be 2 after deleting first occurrence\n");
        exit(1);
    }

    int* item;
    if (queue_dequeue(q, (void**)&item) != 0 || *item != 100) {
        fprintf(stderr, "test8: dequeue did not return x as expected\n");
        exit(1);
    }

    if (queue_dequeue(q, (void**)&item) != 0 || *item != 100) {
        fprintf(stderr, "test8: second dequeue did not return x as expected\n");
        exit(1);
    }

    if (queue_length(q) != 0) {
        fprintf(stderr, "test8: queue_length not 0 after removing all identical items\n");
        exit(1);
    }

    if (queue_free(q) != 0) {
        fprintf(stderr, "test8: queue_free failed\n");
        exit(1);
    }
}

int main(void) {
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();

    return 0;
}