#include "pages.h"

#define NLINKS 100000000

void readLine(char** input, char** name, unsigned long* id) {
  char* middle = strchr(*input, 9);

  size_t lenId = middle - (*input);
  char* strId = malloc((lenId + 1)*sizeof(char));
  strncpy(strId, *input, lenId);
  strId[lenId] = '\0';
  *id = atoi(strId);
  free(strId);

  char* second = middle+1;
  char* eol = strchr(*input, '\n');
  size_t lenName = eol - second;
  *name = malloc((lenName + 1)*sizeof(char));
  strncpy(*name, second, lenName);
  (*name)[lenName] = '\0';
}

Page* readPages(char* input, unsigned long* nbPages) {
  FILE* file = readBeginningFile(input);
  unsigned long e1=NLINKS;

  Page* pages = malloc(e1*sizeof(Page));
  *nbPages = 0;

  unsigned int increment = 5;
  unsigned int sizeStr = increment;
  char* str = malloc((sizeStr+1)*sizeof(char));
  char eol[1] = "\n";
  char* output;

  while (true) {
    output = fgets(str, sizeStr+1, file);
    if (output && (str[0] != eol[0])) {
      while (str[strlen(str) - 1] != eol[0]) {
        str = realloc(str, (sizeStr + increment + 1)*sizeof(char));
        output = fgets(&str[sizeStr], increment + 1, file);
        sizeStr += increment;
      }
      readLine(&str, &pages[*nbPages].name, &pages[*nbPages].id);
      *nbPages += 1;
      if (*nbPages == e1) {
        e1 += NLINKS;
        pages = realloc(pages, e1*sizeof(Page));
      }
    } else if (!output) {
      break;
    }
  }
  pages = realloc(pages, *nbPages*sizeof(Page));

  fclose(file);
  free(str);

  return pages;
}

int cmpPage(const void* a, const void* b) {
  Page* x = (Page*)a;
  Page* y = (Page*)b;
  if (x->pagerank < y->pagerank) {
    return 1;
  } else if (x->pagerank > y->pagerank) {
    return -1;
  }
  return 0;
}

void sortPages(Page* pages, unsigned long nbPages) {
  qsort(pages, nbPages, sizeof(Page), cmpPage);
}

void free_pages(Page* pages, unsigned long nbPages) {
  for (unsigned long i=0; i<nbPages; i++) {
    free(pages[i].name);
  }
  free(pages);
}
