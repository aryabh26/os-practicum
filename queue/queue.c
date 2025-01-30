#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct queue {
	// your code here
} *queue_t;

queue_t queue_new() {
    // your code here
}

int queue_enqueue(queue_t queue, void* item) {
    // your code here
    // Must be O(1) (performance does not depend on length of queue)
}

int queue_insert(queue_t queue, void* item) {
    // your code here
    // Must be O(1) (performance does not depend on length of queue)
}

int queue_dequeue(queue_t queue, void** pitem) {
    // your code here
    // Must be O(1) (performance does not depend on length of queue)
}

void queue_iterate(const queue_t queue, queue_func_t f, void* context) {
    // your code here
}

int queue_free(queue_t queue) {
    // your code here
    // Must be O(1) (performance does not depend on length of queue)
}

int queue_length(const queue_t queue) {
    // your code here
    // Must be O(1) (performance does not depend on length of queue)
}

int queue_delete(queue_t queue, void* item) {
    // your code here
}
