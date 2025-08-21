#ifndef UTILS_H
#define UTILS_H
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "linearlist.h"
#include "linklist.h"

void printList(const LinearList *list);
void initializeList(LinearList *list, int capacity);
int getMax(const LinearList *list);

#endif // UTILS_H