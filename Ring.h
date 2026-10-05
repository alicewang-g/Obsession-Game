//
//  Ring.h
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//

#ifndef Ring_H
#define Ring_H

namespace cs31
{

class Ring
{
public:
  // each Ring will have one of the following state values
  enum class RingState { DOWN, UP, SAFE };
  
  // CS 31 students need to complete the TODO methods in this class
  // a Ring holds a value and a particular RingState
  Ring( int value=0 );
  
  // accessor methods
  int      getValue( ) const;
  RingState getState( ) const;
  
  // CS 31 TODO
  // change the RingState to RingState::UP
  // DOWN and SAFE can be turned into UP
  void pushUp();
  // CS 31 TODO
  // change the RingState to RingState::DOWN
  // only UP can be turned into DOWN
  void pushDown();
  // CS 31 TODO
  // change the RingState to RingState::SAFE
  // only UP can be turned into SAFE
  void makeSafe();
private:
  int mValue;
  RingState mState;
};

}

#endif
