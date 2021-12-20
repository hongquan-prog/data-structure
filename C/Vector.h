#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>
#include "List.h"

typedef void Vector;
typedef void* VectorNode;

typedef struct
{
    list_def base;
    VectorNode* head;
}vector_def;

Vector* vector_create(int length);
bool vector_insert(Vector* list, int i, const VectorNode node);
VectorNode vector_remove(Vector* list, int i);
int vector_find(Vector* list, const VectorNode node);
bool vector_get(Vector* list, int i, VectorNode* node);
bool vector_set(Vector* list, int i, const VectorNode node);
int vector_length(Vector* list);
void vector_clear(Vector* list);

#endif