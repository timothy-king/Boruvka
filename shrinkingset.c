#include "shrinkingset.h"
#include <stdlib.h>
#include <stdio.h>

ShrinkingSetP ShrinkingSetNew(uint32_t max){
  ShrinkingSetP ss = malloc(sizeof(struct ShrinkingSet));
  ss->set = malloc(sizeof(uint32_t)*max);
  uint32_t i;
  for(i = 0; i < max; ++i){
    ss->set[i] = i;
  }

  ss->size = max;
  ss->max = max;

  return ss;
}

void ShrinkingSetDelete(ShrinkingSetP ss){
  free(ss->set);
  free(ss);
}

void ShrinkingSetRemove(ShrinkingSetP ss, uint32_t idx){
  if(ss->size == 0){
    printf("Error: removing from an empty list");
    exit(-1);
  }

  ss->set[idx] = ss->set[ss->size-1];
  (ss->size)--;
}
