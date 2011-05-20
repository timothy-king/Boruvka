#include "unionfind.h"
#include <stdlib.h>

void ForestInit(ForestP f, uint32_t size){
  f->parent = malloc(sizeof(NodeId)*size);
  f->treeSize = malloc(sizeof(uint32_t)*size);
  f->posInRoots = malloc(sizeof(uint32_t)*size);
  f->roots = malloc(sizeof(NodeId)*size);

  NodeId i;
  for(i = 0; i < size; ++i){
    f->parent[i] = i;
    f->treeSize[i] = 1;
    f->posInRoots[i] = i;
    f->roots[i] = i;
  }

  f->numRoots = size;
  f->size = size;
}

ForestP ForestNew(uint32_t size){
  ForestP f = malloc(sizeof(struct Forest));
  ForestInit(f, size);
  return f;
}



NodeId find(ForestP f, NodeId id){
  if(isRoot(f,id)){
    return id;
  }else{
    NodeId root = find(f, f->parent[id]);
    f->parent[id] = root;
    return root;
  }
}

void ForestUninit(ForestP f){
  free(f->parent);
  free(f->treeSize);
  free(f->posInRoots);
  free(f->roots);
}

void ForestDelete(ForestP f){
  ForestUninit(f);
  free(f);
}

void merge(ForestP f, NodeId x, NodeId y){
  NodeId rootA = find(f, x);
  NodeId rootB = find(f, y);

  //Swap so that rootA is larger
  if(f->treeSize[rootA] < f->treeSize[rootB]){
    NodeId tmp = rootA;
    rootA = rootB;
    rootB = tmp;
  }

  //Remove rootB from the roots list
  NodeId atBack = f->roots[f->numRoots - 1];
  uint32_t posB = f->posInRoots[rootB];
  f->roots[posB] = atBack;
  --(f->numRoots);

  //Merge rootB into rootA
  f->parent[rootB] = rootA;
  f->treeSize[rootA] += f->treeSize[rootB];
}


bool isRoot(ForestP f, NodeId id){
  return f->parent[id] == id;
}

bool sameForest(ForestP f, NodeId x, NodeId y){
  return find(f, x) == find(f, y);
}
