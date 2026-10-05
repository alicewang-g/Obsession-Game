//
//  Player.h
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Ring.h"
#include "Die.h"
#include "Turn.h"
#include "DieManager.h"
#include "Settings.h"
#include <string>

namespace cs31
{

class Player

{
public:
  // CS 31 students need to complete the TODO methods in this class
  // represents one player from an Obsession game which maybe be optionally named
  // each player tracks SIZE Rings
  // each of its methods gets called as an Obsession game is played
  // for readability sake, each player can be given a name which will get printed
  // when Ring changes take place
  Player( std::string name="" );
  
  // return a string showing all the Rings in this Player
  std::string display() const;

  // can this turn be used at this time in the game?
  bool acceptableTurn( Turn & t, DieManager manager, Player otherPlayer );
  
  // try first to play the turn parameter in the Rings of the otherPlayer (via pushDown)
  // if that does not use up all the turn's moves, then yourself
  // performs pushUp
  // returns true when both Moves are used
  bool useTurn( Turn & t, Player & otherPlayer, bool noOutput=true );
  // try first to play both moves in the Rings of the otherPlayer (via pushDown)
  // if that does not use up all the Dies then try yourself to perform valid
  // pushUp operations
  // returns true when both Moves are used
  bool useMoves( Move m1, Move m2, Player & otherPlayer, bool noOutput=true );
  // try first to play both dies in the Rings of the otherPlayer (via pushDown)
  // if that does not use up both Moves then try yourself to perform valid
  // pushUp operations
  // returns true when both Dies are used
  bool useDies( Die d1, Die d2, Player & otherPlayer, bool noOutput=true );
  // lock in all the Rings that are up and make them safe
  bool endTurn( );
  
  // perform pushDown on yourself
  // run by the other play to set you back
  bool pushDown( Die d, bool noOutput=true );
  
  // CS 31 TODO
  // are all this Player's Rings up or safe?
  bool allUpOrSafe() const;
  // CS 31 TODO
  // accessor method
  Ring getRing( int i ) const;
private:
  // for easier coding, ignore the Ring with value 0...
  Ring mRings[ SIZE+1 ];
  std::string mName;
  
  // helper method
  // push a particular Ring up
  // return true if a Ring change actually occurred
  // for readability sake, print out the Ring change when noOutput is false
  bool pushRingUp( int i, bool noOutput );
  // helper method
  // push a particular Ring down
  // return true if a Ring change actually occurred
  // for readability sake, print out the Ring change when noOutput is false
  bool pushRingDown( int i, bool noOutput );
  // helper method
  // make a particular Ring safe
  // return true if a Ring change actually occurred
  // for readability sake, print out the Ring change when noOutput is false
  bool pushRingSafe( int i, bool noOutput );
};


}

#endif
