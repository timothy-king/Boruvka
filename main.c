#include "node.h"
#include "unionfind.h"
#include "edge.h"
#include "shrinkingset.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct Graph{
  uint32_t nodes;
  EdgeListP edges; //The edges->list[0] is an invalid edge of infinite weight
};

struct MSTState {
  ForestP forest;
  ShrinkingSetP activeEdges;

  uint32_t* bestEdgeId;
};

inline void UpdateBestEdge(struct Graph* g, struct MSTState* state, NodeId root, uint32_t id, double weight){
  uint32_t bestEdgePos = state->forest->posInRoots[root];
  uint32_t currBestId = state->bestEdgeId[bestEdgePos];
  double currBestWeight = g->edges->list[currBestId].weight;
  if(weight < currBestWeight || (weight == currBestWeight && id < currBestId)){
    state->bestEdgeId[bestEdgePos] = id;
  }
}

double sum;

void BoruvkaRound(struct Graph* g, struct MSTState* state, EdgeListP selected){
  //Set all of edges for each connected component to INF
  uint32_t numActiveEdges = state->activeEdges->size;
  uint32_t numRoots = state->forest->size;
  uint32_t i;
  for(i = 0; i < numRoots; ++i){
    state->bestEdgeId[i] = 0;
  }

  uint32_t activeEdgeIdx = 0;
  while(activeEdgeIdx < numActiveEdges){
    uint32_t edgeId = state->activeEdges->set[activeEdgeIdx];
    EdgeP edge = &(g->edges->list[edgeId]);
    NodeId rootA = find(state->forest, edge->a), rootB = find(state->forest, edge->b);
    if(rootA == rootB){
      ShrinkingSetRemove(state->activeEdges, activeEdgeIdx);
      --numActiveEdges;
    }else{
      double weight = edge->weight;
      UpdateBestEdge(g, state, rootA, edgeId, weight);
      UpdateBestEdge(g, state, rootB, edgeId, weight);
      ++activeEdgeIdx;
    }
  }

  for(i = 0; i < numRoots; ++i){
    uint32_t edgeId = state->bestEdgeId[i];
    if(edgeId != 0){
      NodeId a = g->edges->list[edgeId].a;
      NodeId b = g->edges->list[edgeId].b;
      double weight = (g->edges->list[edgeId]).weight;

      if(!sameForest(state->forest, a,b)){ // Only merge an edge once
	merge(state->forest, a, b);
	sum += weight;
	EdgeListAppend(selected, a, b, weight);
      }
    }
  }
}

void Boruvka(struct Graph* g, EdgeListP selected){
  struct MSTState state;

  state.forest = ForestNew(g->nodes);
  state.activeEdges = ShrinkingSetNew(g->edges->size);
  state.bestEdgeId = malloc(sizeof(uint32_t) * (g->nodes));

  ShrinkingSetRemove(state.activeEdges, 0);
  while(state.activeEdges->size > 0 && state.forest->numRoots > 1){
    BoruvkaRound(g, &state, selected);
  }
}

void readGraph(struct Graph* g){
  long unsigned int numNodes, numEdges;
  scanf("%lu %lu", &numNodes, &numEdges);

  if(numNodes >= UINT32_MAX){
    printf("Error: too many nodes");
    exit(-1);
  }
  if(numEdges >= UINT32_MAX - 1){
    printf("Error: too many edges");
  }

  g->nodes = numNodes;
  g->edges = EdgeListNew(numEdges+1);

  EdgeListAppend(g->edges, UINT32_MAX, UINT32_MAX, INFINITY);

  uint32_t i;
  for(i = 0; i < numEdges; ++i){
    long unsigned int a, b;
    double w;
    scanf("%lu %lu %lf", &a, &b, &w);
    if(a >= g->nodes || b >= g->nodes){
      printf("Node exceeds numNodes");
      exit(-1);
    }
    EdgeListAppend(g->edges, a, b, w);
  }
}

int main() {
  struct Graph g;
  readGraph(&g);

  EdgeListP selected;
  selected = EdgeListNew(g.edges->size);

  sum = 0.0;

  clock_t start, end;
  float ratio;
  ratio = 1./CLOCKS_PER_SEC;

  start = clock();
  Boruvka(&g, selected);
  end = clock();

  double diff = ratio * (end - start);
  printf("MST weight: %lf time: %lf\n", sum, diff);

  return 0;
}
