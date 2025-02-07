#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    void *data;
    struct node *next;
} node_t;

typedef struct queue {
	node_t *head;
    node_t *tail;
    int size;
} *queue_t;

queue_t queue_new() {
    queue_t queue = malloc(sizeof(*queue));

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
    node_t *new_node = malloc(sizeof(*new_node));
    if (!new_node){
        return -1;
    }
    new_node->data = item;
    new_node->next= NULL;

    if (queue->size==0){
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
    node_t *new_node = malloc(sizeof(*new_node));
    if (!new_node){
        return -1;
    }
    new_node->data = item;
    new_node->next= NULL;

    if (queue->size==0){
        queue->tail = new_node;
    } else {
        new_node->next = queue->head;
    }
    queue->head = new_node;
    queue->size++;
    return 0;
}

int queue_dequeue(queue_t queue, void** pitem) {
    if (!queue || queue->size==0){
        return -1;
    }
    node_t *node = queue->head;
    queue->head = node->next;
    if (!queue->head){
        queue->tail=NULL;
    }
    queue->size--;
    if (pitem){
        *pitem = node->data;
    }
    free(node);
    return 0;
}

void queue_iterate(const queue_t queue, queue_func_t f, void* context) {
    if (!queue || !f){
        return; //no -1 since return type is void
    }
    node_t *cur = queue->head;
    while (cur){
        f(cur->data,context);
        cur = cur->next;
    }
}

int queue_free(queue_t queue) {
    if (!queue || queue->size!=0){
        return -1;
    }
    free(queue);
    return 0;
}

int queue_length(const queue_t queue) {
    if (!queue){
        return -1;
    }
    return queue->size;
}

int queue_delete(queue_t queue, void* item) {
    if (!queue || !item || queue->size==0){
        return -1;
    }
    node_t *cur = queue->head;
    if (cur->data==item){
        queue->head = cur->next;
        free(cur);
        queue->size--;
        return 0;
    }
    while (cur->next){
        if (cur->next->data==item){
            node_t *temp = cur->next;
            cur->next = temp->next;
            if (temp==queue->tail){
                queue->tail=cur;
            }
            free(temp);
            queue->size--;
            return 0;
        }
        cur = cur->next;
    }
    return -1;
}
