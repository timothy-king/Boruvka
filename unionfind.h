#include <stdint.h>
#include <stdbool.h>
#include "node.h"

#ifndef UNIONFIND_H
#define UNIONFIND_H

struct Forest {
  NodeId size;
  uint32_t numRoots;

  NodeId* parent;
  uint32_t* treeSize;
  uint32_t* posInRoots;
  NodeId* roots; /* List of the roots in the Forest */
};

typedef struct Forest* ForestP;

void ForestInit(ForestP f, uint32_t size);
void ForestUninit(ForestP f);

ForestP ForestNew(uint32_t size);
void ForestDelete(ForestP f);

NodeId find(ForestP f, NodeId id);

void merge(ForestP f, NodeId x, NodeId y);

bool isRoot(ForestP f, NodeId id);

bool sameForest(ForestP f, NodeId x, NodeId y);

#endif /* UNIONFIND_H */
