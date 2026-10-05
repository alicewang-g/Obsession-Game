//
//  Move.h
//  Obsession
//
//  Created by Howard Stahl on 9/7/25.
//

#ifndef MOVE_H
#define MOVE_H

namespace cs31
{

class Move
{
public:
  // This class is completely finished and has no work for CS 31 students to complete
  // a Move holds a direction and a value to represent half of Player's Turn
  Move( bool upMove, int value );
  
  // a Move direction is either Up or Down
  // only one of these two operations will ever return true for a particular Move
  bool isUp() const;
  bool isDown() const;
  // accessor method
  int  getValue() const;
  
  // verifies that value is in the range between 1 and SIZE inclusive
  bool isValid() const;
private:
  bool mIsUp;  // true means up, false means down
  int  mValue; // a number between 1 and SIZE
};


}


#endif
