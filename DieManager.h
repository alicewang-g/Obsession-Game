//
//  DieManager.h
//  Obsession
//
//

#ifndef DieManager_h
#define DieManager_h

#include "Die.h"


namespace cs31
{
    // This class is completely finished and has no work for CS 31 students to complete
    // holds two Die for use by an Obsession Player
    class DieManager
    {
    public:
      DieManager();
        
      // randomly roll both Dies
      void roll();
      
      // for cheating purposes by forcing values into the Dies
      void roll( Die d1, Die d2 );
      
      // accessor methods
      Die  getDie1() const;
      Die  getDie2() const;
    private:
      Die mDie1, mDie2;
    };

}

#endif 
