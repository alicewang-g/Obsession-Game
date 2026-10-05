//
//  Move.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/7/25.
//

#include "Move.h"
#include "Settings.h"


namespace cs31
{

// a Move holds a direction and a value to represent half of Player's Turn
Move::Move( bool upMove, int value ) : mIsUp( upMove ), mValue( value )
{
  
}

// a Move direction is either Up or Down
// only one of these two operations will ever return true for a particular Move
bool Move::isUp() const
{
  return( mIsUp );
}

bool Move::isDown() const
{
  return( !mIsUp );
}

// accessor method
int  Move::getValue() const
{
  return( mValue );
}

// verifies that value is in the range between 1 and SIZE inclusive
bool Move::isValid() const
{
  return( mValue >= 1 && mValue <= SIZE );
}

}
