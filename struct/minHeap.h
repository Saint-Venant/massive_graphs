#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>


typedef struct {
  unsigned long index;
  unsigned long degree;
  unsigned long pos; // position in the MinHeap
  _Bool inserted;
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
void decrementAndUpdate(MinHeap* h, Vertex* v);

void free_MinHeap(MinHeap* h);
void free_vertices(Vertex** vertices, unsigned long nbVertices);

void testHeap();
