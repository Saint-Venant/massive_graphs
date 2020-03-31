#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>


typedef struct {
  unsigned long index;
  unsigned long degree;
} Vertex;

typedef struct {
  Vertex** array;
  unsigned long capacity;
  unsigned long count;
} MinHeap;

MinHeap* createMinHeap(unsigned long capacity);
void heapify_up(MinHeap* h, unsigned long index);
void heapify_down(MinHeap* h, unsigned long parent_node);
void insert(MinHeap* h, Vertex* v);
void displayMinHeap(MinHeap* h);
Vertex* popMin(MinHeap* h);
void free_MinHeap(MinHeap* h);

void testHeap();
