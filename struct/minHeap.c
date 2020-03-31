#include "minHeap.h"



MinHeap* createMinHeap(unsigned long capacity) {
  MinHeap* h = malloc(sizeof(MinHeap));
  if (!h) {
    printf("Memory Error !\n");
    return NULL;
  }

  h->capacity = capacity;
  h->count = 0;
  h->array = malloc(capacity*sizeof(Vertex*));

  if (!h->array) {
    printf("Memory Error !\n");
    return NULL;
  }

  return h;
}

void free_MinHeap(MinHeap* h) {
  free(h->array);
  free(h);
}

void free_vertices(Vertex** vertices, unsigned long nbVertices) {
  for (unsigned long i=0; i<nbVertices; i++) {
    free(vertices[i]);
  }
  free(vertices);
}

void heapify_up(MinHeap* h, unsigned long index) {
  if (index == 0) {
    return;
  }

  unsigned long parent_node = (index-1)/2;
  if (h->array[parent_node]->degree > h->array[index]->degree) {
    // swap and recursive call
    Vertex* temp = h->array[parent_node];
    h->array[parent_node] = h->array[index];
    h->array[index] = temp;
    h->array[index]->pos = index;
    h->array[parent_node]->pos = parent_node;
    heapify_up(h, parent_node);
  }
}

void heapify_down(MinHeap* h, unsigned long parent_node) {
  unsigned long left = parent_node*2 + 1;
  unsigned long right = right = parent_node*2 + 2;
  unsigned long minNode;

  _Bool validLeft = ((left < h->count) && (left >= 0));
  _Bool validRigth = ((right < h->count) && (right >= 0));

  if (validLeft && (h->array[left]->degree < h->array[parent_node]->degree)) {
    minNode = left;
  } else {
    minNode = parent_node;
  }
  if (validRigth && (h->array[right]->degree < h->array[minNode]->degree)) {
    minNode = right;
  }

  if (minNode != parent_node) {
    Vertex* temp = h->array[parent_node];
    h->array[parent_node] = h->array[minNode];
    h->array[minNode] = temp;
    h->array[parent_node]->pos = parent_node;
    h->array[minNode]->pos = minNode;
    heapify_down(h, minNode);
  }
}

void insert(MinHeap* h, Vertex* v) {
  if (h->count >= h->capacity) {
    printf("Error : MinHeap reached maximum capacity");
    return;
  }
  h->array[h->count] = v;
  v->pos = h->count;
  v->inserted = 1;
  heapify_up(h, h->count);
  h->count++;
}

void displayMinHeap(MinHeap* h) {
  printf("Display heap\n");
  Vertex* v;
  for (unsigned long i=0; i<h->count; i++) {
    v = h->array[i];
    printf("-> (i:%lu; d:%lu, pos:%lu) ", v->index, v->degree, v->pos);
  }
  printf("\n");
}

Vertex* popMin(MinHeap* h) {
  if (h->count <= 0) {
    return NULL;
  }
  // replace first node by last and delete last
  Vertex* pop = h->array[0];
  h->array[0] = h->array[h->count-1];
  h->array[0]->pos = 0;
  h->count--;
  heapify_down(h, 0);
  pop->inserted = 0;
  return pop;
}

void decrementAndUpdate(MinHeap* h, Vertex* v) {
  if (v->degree <= 0) {
    printf("Error : attempt to decrement a degree already equal to 0 !\n");
    return;
  }
  v->degree--;
  heapify_up(h, v->pos);
}

void testHeap() {
  printf(" --- Test MinHeap ---\n\n");

  printf("Creating MinHeap\n");
  unsigned long capacity = 100;
  MinHeap* h = createMinHeap(capacity);
  if (!h) {
    return;
  }

  printf("\nCreating vertices\n");
  unsigned long nbVertices = 10;
  Vertex** vertices = malloc(10*sizeof(Vertex*));
  for (unsigned long i=0; i<nbVertices; i++) {
    vertices[i] = malloc(sizeof(Vertex));
    vertices[i]->index = i;
    vertices[i]->degree = (11*i + 8)%7;
    vertices[i]->inserted = 0;
    printf("i : %lu -> d = %lu\n", vertices[i]->index, vertices[i]->degree);
  }

  printf("\nInserting vertices in the MinHeap\n");
  for (unsigned long i=0; i<nbVertices; i++) {
    insert(h, vertices[i]);
    displayMinHeap(h);
  }

  printf("\nPoping elements\n");
  Vertex* v;
  while (h->count > 0) {
    displayMinHeap(h);
    v = popMin(h);
  }

  printf("\nFreeing MinHeap\n");
  free_MinHeap(h);

  printf("\nFreeing vertices\n");
  free_vertices(vertices, nbVertices);
}
