//
//  Player.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//
#include <iostream>
#include "Player.h"
#include "Settings.h"

namespace cs31
{

Player::Player( std::string name ) : mName( name )
{
  // set up the Ring's 1 thru SIZE
  for (int i = 1; i < SIZE; i++)
  {
    Ring r( i );
    mRings[ i ] = r;
  }
}

// can this turn be used at this time in the game?
// The turn parameter is being passed by reference because the calling
// code needs to know that the turn was fully consumed
bool Player::acceptableTurn( Turn & t, DieManager manager, Player otherPlayer )
{
  bool result = false;
  // copy this Player and use it for useTurn because we don't
  // want to change the state of the Player involved
  // we are just trying to see if this move is legal - we are not make the move
  Player copyOfThisPlayer = *this;
  if (copyOfThisPlayer.useTurn( t, otherPlayer ))
  {
    if (t.matchAgainstDies(manager))
    {
      result = true;
    }
  }
  return( result );
}

// try first to play the turn parameter in the Rings of the otherPlayer (via pushDown)
// if that does not use up all the turn's moves, then yourself
// performs pushUp
// returns true when both Moves are used
// for readability sake, Ring changes get printed out when noOutput is false
bool Player::useTurn( Turn & t, Player & otherPlayer, bool noOutput )
{
  bool result = false;
  if (t.isValid())
  {
    if (useMoves( t.getMove1(), t.getMove2(), otherPlayer, noOutput ))
    {
      result = true;
    }
  }
  return( result );
}

// try first to play both moves in the Rings of the otherPlayer (via pushDown)
// if that does not use up all the Dies then try yourself to perform valid
// pushUp operations
// returns true when both Moves are used
// for readability sake, Ring changes get printed out when noOutput is false
bool Player::useMoves( Move m1, Move m2, Player & otherPlayer, bool noOutput )
{
  bool result = false;
  bool used1 = false;
  bool used2 = false;
  if (m1.isValid())
  {
    if (m1.isUp())
    {
      // on you
      if (pushRingUp( m1.getValue(), noOutput ))
        used1 = true;
      
      result = used1;
    }
    else
    {
      // on other player
      Die d;
      d.setValue( m1.getValue() );
      used1 = otherPlayer.pushDown(d);
      result = used1;
    }
  }
  if (m2.isValid())
  {
    if (m2.isUp())
    {
      // on you
      if (pushRingUp( m2.getValue(), noOutput ))
        used2 = true;
    }
    else
    {
      // on other player
      Die d;
      d.setValue( m2.getValue() );
      used2 = otherPlayer.pushDown(d);
    }
    result = used1 && used2;
  }
  return( result );
}


// try first to play both dies in the Rings of the otherPlayer (via pushDown)
// if that does not use up both Moves then try yourself to perform valid
// pushUp operations
// returns true when both Dies are used
// for readability sake, Ring changes get printed out when noOutput is false
bool Player::useDies( Die d1, Die d2, Player & otherPlayer, bool noOutput )
{
  int value1 = d1.getValue();
  int value2 = d2.getValue();
  int sum = value1 + value2;
  bool used1 = false, used2 = false;
  
  // work on the other player
  Die total;
  total.setValue(sum);
  if (otherPlayer.pushDown(total, noOutput ))
  {
    used1 = true;
    used2 = true;
  }
  else
  {
    if (otherPlayer.pushDown( d1, noOutput ))
    {
      used1 = true;
    }
    if (otherPlayer.pushDown( d2, noOutput ))
    {
      used2 = true;
    }
  }
  
  // work on yourself
  // try using the sum
  if (!used1 && !used2)
  {
    if (sum < SIZE)
    {
      if (pushRingUp( sum, noOutput ))
      {
        used1 = true;
        used2 = true;
      }
    }
  }
  // then try using the individual dies
  if (!used1)
  {
    if (pushRingUp( value1, noOutput ))
      used1 = true;
  }
  if (!used2)
  {
    if (pushRingUp( value2, noOutput ))
      used2 = true;
  }
  return( used1 && used2 );
}

// perform pushDown on yourself
// run by the other play to set you back
// for readability sake, Ring changes get printed out when noOutput is false
bool Player::pushDown( Die d, bool noOutput )
{
  int value = d.getValue();
  bool result = false;
    
  if (pushRingDown(value, noOutput))
    result = true;
  return( result );
}

// lock in all the Rings that are up and make them safe
// for readability sake, Ring changes are printed out
bool Player::endTurn( )
{
  bool result = false;
  for (int i = 1; i <= SIZE; i++)
  {
    if (pushRingSafe(i, false))
      result = true;
  }
  return( result );
}

// CS 31 TODO
// are all this Player's Rings up or safe?
bool Player::allUpOrSafe() const
{
    bool result = false;
    int count = 0;
    for (int i = 1; i < SIZE; i++){
        Ring want = getRing(i);
        if (want.Ring::getState() == Ring::RingState::UP || want.Ring::getState() == Ring::RingState::SAFE){
                count++;
            //std::cout << count << " ";
            }
    }
    if (count == SIZE - 1){ //because size si 11 but why??
        result = true;
    }
    
    return result; //cheating change back
}

// return a string showing all the Rings in this Player
std::string Player::display() const
{
  std::string s;
  for (int i = 1; i < SIZE; i++)
  {
    Ring r = mRings[ i ];
    s += std::to_string( r.getValue() ) + " - ";
    switch( r.getState() )
    {
      case Ring::RingState::DOWN:
        s += "down";
        break;
      case Ring::RingState::UP:
        s += "up  ";
        break;
      case Ring::RingState::SAFE:
        s += "safe";
        break;
    }
    s += '\n';
  }

  return( s );
}

// CS 31 TODO
// accessor method
Ring Player::getRing( int i ) const
{
  return( mRings[ i ] );
}

// helper method
bool Player::pushRingUp( int i, bool noOutput )
{
  bool result = false;
  switch (mRings[i].getState())
  {
    case Ring::RingState::SAFE:
      // SAFE can be turned into UP!!!
      if (!noOutput)
        std::cout << mName << "-Ring[ " << i << " ] going from SAFE to UP" << std::endl;
      mRings[ i ].pushUp();
      result = true;
      break;
    case Ring::RingState::DOWN:
      if (!noOutput)
        std::cout << mName << "-Ring[ " << i << " ] going from DOWN to UP" << std::endl;
      mRings[ i ].pushUp();
      result = true;
      break;
    case Ring::RingState::UP:
      // ignore
      break;
  }
  return( result );
}

// helper method
bool Player::pushRingDown( int i, bool noOutput )
{
  bool result = false;
  switch (mRings[i].getState())
  {
    case Ring::RingState::SAFE:
      // ignore
      break;
    case Ring::RingState::DOWN:
      // ignore
      break;
    case Ring::RingState::UP:
      if (!noOutput)
        std::cout << mName << "-Ring[ " << i << " ] going from UP to DOWN" << std::endl;
      mRings[ i ].pushDown();
      result = true;
      break;
  }
  return( result );
}

// helper method
bool Player::pushRingSafe( int i, bool noOutput )
{
  bool result = false;
  switch (mRings[i].getState())
  {
    case Ring::RingState::SAFE:
      // ignore
      break;
    case Ring::RingState::DOWN:
      // ignore
      break;
    case Ring::RingState::UP:
      if (!noOutput)
        std::cout << mName << "-Ring[ " << i << " ] going from UP to SAFE" << std::endl;
      mRings[ i ].makeSafe();
      result = true;
      break;
  }
  return( result );
}

}
