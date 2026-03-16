#ifndef _FORWARD_LIST_H
#define _FORWARD_LIST_H

#include "ht_interface.h" // Нужно для ht_entry
#include <stdlib.h>

typedef struct Node {
    ht_entry* data;
    struct Node* next;
} Node;

Node* createNode(ht_entry* data); // Типизировано
void pushFront(Node** head, ht_entry* data);
void freeList(Node* head);

#endif