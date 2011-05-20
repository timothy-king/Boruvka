#include <stdint.h>

#ifndef SHRINKINGSET_H
#define SHRINKINGSET_H

struct ShrinkingSet {
  uint32_t size;
  uint32_t max;

  uint32_t* set;
};

typedef struct ShrinkingSet* ShrinkingSetP;

ShrinkingSetP ShrinkingSetNew(uint32_t max);
void ShrinkingSetDelete(ShrinkingSetP ss);

void ShrinkingSetRemove(ShrinkingSetP ss, uint32_t idx);

#endif /* SHRINKINGSET_H */
