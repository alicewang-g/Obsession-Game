//
//  Ring.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//

#include "Ring.h"

namespace cs31
{

// a Ring holds a value and a particular RingState
Ring::Ring( int value ) : mValue( value ), mState( Ring::RingState::DOWN)
{
  
}

// accessor method
int Ring::getValue( ) const
{
  return( mValue );
}

// accessor method
Ring::RingState Ring::getState( ) const
{
  return( mState );
}

// CS 31 TODO
// change the RingState to RingState::UP
// DOWN and SAFE can be turned into UP
void Ring::pushUp()
{
    RingState result = getState();
    if (result != RingState::UP){
        mState = Ring::RingState::UP;
    }
}

// CS 31 TODO
// change the RingState to RingState::DOWN
// only UP can be turned into DOWN
void Ring::pushDown()
{
    RingState result = getState();
    if (result == RingState::UP){
        mState = Ring::RingState::DOWN;
    }
}

// CS 31 TODO
// change the RingState to RingState::SAFE
// only UP can be turned into SAFE
void Ring::makeSafe()
{
    RingState result = getState();
    if (result == RingState::UP){
        mState = Ring::RingState::SAFE;
    }
}

}
