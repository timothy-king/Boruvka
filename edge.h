#include "node.h"
#include <stdint.h>

#ifndef EDGE_H
#define EDGE_H

struct Edge {
  NodeId a, b; //Nodes on the graph
  double weight;
};

typedef struct Edge* EdgeP;

struct EdgeList {
  uint32_t size;
  uint32_t allocated;

  EdgeP list;
};

typedef struct EdgeList* EdgeListP;

EdgeListP EdgeListNew(uint32_t alloc);

void EdgeListDelete(EdgeListP el);

void EdgeListAppend(EdgeListP el, NodeId a, NodeId b, double w);

#endif /* EDGE_H */
