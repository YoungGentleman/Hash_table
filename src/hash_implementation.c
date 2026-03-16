#include "ht_interface.h"
#include "forward_list.h"
#include "hash_functions.h"
#include <stdlib.h>
#include <string.h>

ht* ht_create(void) {
    ht* h_ptr = (ht*)malloc(sizeof(ht));
    if (h_ptr == NULL) return NULL;
    
    h_ptr->length = 0;
    // Выделяем массив указателей на узлы
    h_ptr->ptr_bucket = calloc(MAX_CAPACITY, sizeof(Node*)); 

    if (h_ptr->ptr_bucket == NULL) {
        free(h_ptr);
        return NULL;
    }
    return h_ptr;
}

void ht_destroy(ht* table) {
    if (!table) return;
    for (int i = 0; i < MAX_CAPACITY; i++) {
        freeList(table->ptr_bucket[i]);
    }
    free(table->ptr_bucket); // Освобождаем массив корзин
    free(table);
}

void ht_set(ht* table, ht_entry elem) {
    if (!table) return;

    unsigned int len = strlen(elem.key);
    unsigned int index = 0;

#ifdef MURMUR2
    index = MurmurHash2(elem.key, len);
#else
    index = simple_sum_hash(elem.key, len);
#endif
    
    // Выделяем память для копии записи, чтобы не хранить адрес локальной переменной
    ht_entry* new_entry = (ht_entry*)malloc(sizeof(ht_entry));
    if (!new_entry) return;
    
    new_entry->key = elem.key;
    new_entry->value = elem.value;

    Node** head = &(table->ptr_bucket[index]);
    pushFront(head, new_entry);
    table->length += 1;
}

void* ht_get(ht* table, const char* key) {
    if (!table) return NULL;

    unsigned int len = strlen(key);
    unsigned int index = 0;

#ifdef MURMUR2
    index = MurmurHash2(key, len);
#else
    index = simple_sum_hash(key, len);
#endif
    index = index % MAX_CAPACITY;

    // Ищем ключ в списке коллизий
    Node* current = table->ptr_bucket[index];
    while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
            return current->data->value;
        }
        current = current->next;
    }
    return NULL;
}

size_t ht_length(ht* table) {
    return table ? table->length : 0;
}