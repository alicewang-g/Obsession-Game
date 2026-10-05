//
//  Die.cpp
//  Obsession
//
//

#include "Die.h"
#include <random>

namespace cs31
{

// by default, a six sided Die
Die::Die( int sides ) : mSides( sides ), mValue( 0 )
{

}
    
// toss the Die by randoming selecting a value between 1 and mSides inclusive
void Die::roll()
{
  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_int_distribution<> dist(1, mSides);
  mValue = dist(e2);
}

// get the value of the Die
int  Die::getValue( ) const
{
  return( mValue );
}

// for cheating purposes by forcing a value into the Die
void Die::setValue( int value )
{
  mValue = value;
}

}
