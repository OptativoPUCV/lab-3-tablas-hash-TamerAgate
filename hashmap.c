#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap{  
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
    long buscar = hash(key, map->capacity);
    
    while (map->buckets[buscar] != NULL && map->buckets[buscar]->key != NULL)
    {
        if (is_equal(map->buckets[buscar]->key, key))
        {
            return;
        }
        buscar = (buscar + 1) % map->capacity;
        if (buscar == hash(key, map->capacity)) 
        {
            return;
        }
    }
    
    map->buckets[buscar] = createPair(key, value);
    map->size++;
    map->current = buscar;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL) return NULL;

    map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
    if (map->buckets == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key)
{    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
    long buscar = hash(key, map->capacity);

    while (map->buckets[buscar] != NULL)
    {
        if (map->buckets[buscar]->key != NULL && is_equal(map->buckets[buscar]->key, key)) 
        {
            map->current = buscar;
            return map->buckets[buscar];
        }
        buscar = (buscar + 1) % map->capacity;
        {
        
        if (buscar == hash(key, map->capacity)) 
        {
            break;
        }

    
    return NULL;
    }



    return NULL;
}

Pair * firstMap(HashMap * map) 
{
    if (map->size == 0) return NULL;
    
    for (int i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) 
        {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) 
{
    if (map->size == 0) return NULL;

    for (int i = map->current + 1; i < map->capacity; i++)
    {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) 
        {
            map->current = i;
            return map->buckets[i];
        }
    }

    return NULL;
}
