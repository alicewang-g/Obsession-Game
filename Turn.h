//
//  Turn.h
//  Obsession
//
//  Created by Howard Stahl on 9/7/25.
//

#ifndef TURN_H
#define TURN_H

#include <string>
#include "Move.h"
#include "DieManager.h"

namespace cs31
{

class Turn
{
public:
  // CS 31 students need to complete the TODO methods in this class
  // a Turn represents a Player's turn of play in an Obsession game
  // it might be one or two different moves
  // the moves must be legally allowable based on the game rules
  Turn();
  // parse any of the following strings into a single valid Move held by this Turn
  // "u2"    "d3"     "u10"    "d10"
  // parse any of the following strings into two valid Moves held by this Turn
  // "u2d3"  "d3u2"   "u10d3"  "u3d10"
  // the following strings should lead to this becoming an invalid Turn
  // "u2u3"  "d2d3"    "u2u2"    "d2d2"
  Turn( std::string data );

  // accessor methods
  Move getMove1() const;
  Move getMove2() const;
  int  howManyMovesInThisTurn() const;
  
  // CS 31 TODO
  // verifies that howMany is either 1 or 2, that each Move is valid
  // and that when there are two Moves, they both are not exactly the same
  bool isValid() const;
  
  // can this Turn's moves be generated from the Die's in the DieManager?
  bool matchAgainstDies( DieManager manager );
  // once matched against a DieManager, where both Die's used and required for the match?
  bool wasFullyConsumed();
  void setFullyConsumed( bool value );
private:
  // this Turn's moves
  Move mMove1, mMove2;
  // the value 1 or 2, depending on how many moves were requested
  int  mHowMany;
  // when the Turn is matched against a DieManager,
  bool mFullyConsumed;
  
  // helper methods
  Move buildMoveFromString( std::string value );
  int extractNumber( std::string data, size_t& index, bool& isValid );

};

}

#endif
