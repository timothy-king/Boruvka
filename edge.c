#include "edge.h"
#include <stdlib.h>
#include <stdio.h>


EdgeListP EdgeListNew(uint32_t alloc){
  EdgeListP el = malloc(sizeof(struct EdgeList));
  el->size = 0;
  el->allocated = alloc;
  el->list = malloc(sizeof(struct Edge)*alloc);

  return el;
}

void EdgeListDelete(EdgeListP el){
  free(el->list);
  free(el);
}

void EdgeListAppend(EdgeListP el, NodeId a, NodeId b, double w){
  if(el->size + 1 > el->allocated){
    printf("Error: exceeded list length.\n");
    exit(-1);
  }

  if(a == b){
    printf("Error: adding edge from node %lu to itself with weight %lf.\n", (long unsigned)a, w);
  }

  el->list[el->size].a = a;
  el->list[el->size].b = b;
  el->list[el->size].weight = w;

  ++(el->size);
}

