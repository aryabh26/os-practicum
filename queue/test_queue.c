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

int main(void) {
    test1();
	// test2();
	// ...
	return 0;
}
