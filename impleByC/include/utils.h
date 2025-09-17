#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include "linearlist.h"

void printList(const LinearList *list);
void initializeList(LinearList *list, int capacity);
int getMax(const LinearList *list);

#endif // UTILS_H