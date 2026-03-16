#include "forward_list.h"
#include <stdlib.h>

Node* createNode(ht_entry* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void pushFront(Node** head, ht_entry* data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    newNode->next = *head;
    *head = newNode;
}

// Освобождение памяти (исправлено: освобождаем data внутри узла)
void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (tmp->data) {
            free(tmp->data); // Освобождаем ht_entry
        }
        free(tmp);
    }
}