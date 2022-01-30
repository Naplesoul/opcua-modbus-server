/*
 * @Description: 
 * @Autor: Weihang Shen
 * @Date: 2022-01-30 21:13:11
 * @LastEditors: Weihang Shen
 * @LastEditTime: 2022-01-30 22:09:25
 */
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

void List_free(LinkedList *list)
{
    while (list) {
        if (list->next) {
            LinkedList *next = list->next;
            free(list);
            list = next;
        } else {
            free(list);
            return;
        }
    }
}

void *List_get(LinkedList *list, u_int32_t key)
{
    while (list) {
        if (list->key == key) {
            return list->value;
        }
        list = list->next;
    }
    return NULL;
}

void List_put(LinkedList *list, u_int32_t key, void *value)
{
    while (1) {
        if (list->key == key) {
            free(list->value);
            list->value = value;
            return;
        }
        
        if (list->next) {
            list = list->next;
        } else {
            list->next = (LinkedList *)malloc(sizeof(LinkedList));
            list = list->next;
            list->key = key;
            list->value = value;
            list->next = NULL;
            return;
        }
    }
}

HashMap *Map_new()
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    memset(map, 0, sizeof(HashMap));
}

void Map_free(HashMap *map)
{
    for (u_int32_t i = 0; i < MAP_SIZE; ++i) {
        List_free(map->array[i]);
    }
    free(map);
}

void *Map_get(HashMap *map, u_int32_t key)
{
    u_int32_t index = key % MAP_SIZE;
    return List_get(map->array[index], key);
}

void Map_put(HashMap *map, u_int32_t key, void *value)
{
    u_int32_t index = key % MAP_SIZE;
    if (map->array[index] == NULL) {
        LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
        map->array[index] = list;
        list->key = key;
        list->value = valloc;
        list->next = NULL;
    } else {
        List_put(map->array[index], key, value);
    }
}