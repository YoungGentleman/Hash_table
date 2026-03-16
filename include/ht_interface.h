#ifndef _HT_H
#define _HT_H

#define MAX_CAPACITY 1000
#include <stdbool.h>
#include <stddef.h>

// Определяем структуру записи заранее
typedef struct {
    const char* key;
    void* value;
} ht_entry;

// Предварительное объявление структуры узла, чтобы избежать циклического включения
typedef struct Node Node;

typedef struct {
    Node** ptr_bucket;       // Массив указателей на начала списков
    size_t length;            // Количество элементов
} ht;

ht* ht_create(void);
void ht_destroy(ht* table);
void* ht_get(ht* table, const char* key); // Возвращает значение, а не массив
void ht_set(ht* table, ht_entry elem);
size_t ht_length(ht* table);

#endif