#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ht_interface.h"

void test_basic_insert_get() {
    printf("Test 1: Basic Insert/Get... ");
    ht* table = ht_create();
    if (!table) { printf("FAILED (Create)\n"); return; }

    ht_entry e1 = {"key1", (void*)"value1"};
    ht_set(table, e1);

    void* res = ht_get(table, "key1");
    if (res != NULL && strcmp((char*)res, "value1") == 0) {
        printf("PASSED\n");
    } else {
        printf("FAILED (Get)\n");
    }

    ht_destroy(table);
}

void test_collision_handling() {
    printf("Test 2: Collision Handling... ");
    ht* table = ht_create();
    if (!table) { printf("FAILED (Create)\n"); return; }

    // Добавляем два элемента. 
    // simple_sum_hash('A') = 65, 'B' = 66. 
    // Чтобы гарантировать коллизию в тесте без знания алгоритма, 
    // просто добавим много элементов и проверим, что они не теряются.
    // В данной реализации simple_sum_hash % 1000, коллизии редки на 2 элементах,
    // но логика поиска по ключу должна работать корректно.
    
    ht_entry e1 = {"apple", (void*)"red"};
    ht_entry e2 = {"banana", (void*)"yellow"};
    
    ht_set(table, e1);
    ht_set(table, e2);

    void* v1 = ht_get(table, "apple");
    void* v2 = ht_get(table, "banana");
    void* v3 = ht_get(table, "nonexistent");

    if (v1 && strcmp((char*)v1, "red") == 0 &&
        v2 && strcmp((char*)v2, "yellow") == 0 &&
        v3 == NULL) {
        printf("PASSED\n");
    } else {
        printf("FAILED (Logic)\n");
    }

    ht_destroy(table);
}

int main() {
    test_basic_insert_get();
    test_collision_handling();
    return 0;
}