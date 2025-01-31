#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    void* data;
    struct node* next;
} node_t;

typedef struct queue {
	node_t* head;
    node_t* tail;
    int size;
} *queue_t;

queue_t queue_new() {
    queue_t queue = (queue_t)malloc(sizeof(struct queue));

    if (!queue){
        return NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

int queue_enqueue(queue_t queue, void* item) {
    if (!queue){
        return -1;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node){
        return -1;
    }
    new_node->data = item;
    new_node->next= NULL;

    if (queue->head==NULL){
        queue->head = new_node;
    } else {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    queue->size++;
    return 0;
}

int queue_insert(queue_t queue, void* item) {
    if (!queue){
        return -1;
    }
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node){
        return -1;
    }
    new_node->data = item;
    new_node->next= NULL;

    if (queue->head==NULL){
        queue->tail = new_node;
    } else {
        new_node->next = queue->head;
    }
    queue->head = new_node;
    queue->size++;
    return 0;
}

int queue_dequeue(queue_t queue, void** pitem) {
    
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
