#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/edgelist.h"


typedef struct {
  unsigned long id;
  char* name;
  double pagerank;
} Page;

Page* readPages(char* input, unsigned long* nbPages);

void sortPages(Page* pages, unsigned long nbPages);

void free_pages(Page* pages, unsigned long nbPages);
