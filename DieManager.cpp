//
//  DieManager.cpp
//  Obsession
//
//

#include "DieManager.h"
#include <stdexcept>

namespace cs31
{

DieManager::DieManager()
{
  
}

// randomly roll both Dies
void DieManager::roll()
{
  mDie1.roll();
  mDie2.roll();
}

// for cheating purposes by forcing values into the Dies
void DieManager::roll( Die d1, Die d2 )
{
  mDie1 = d1;
  mDie2 = d2;
}

// accessor method
Die  DieManager::getDie1() const
{
  return( mDie1 );
}

// accessor method
Die  DieManager::getDie2() const
{
  return( mDie2 );
}

}
