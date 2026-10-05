//
//  Obsession.h
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//

#ifndef OBSESSION_H
#define OBSESSION_H

#include "Die.h"
#include "DieManager.h"
#include "Player.h"
#include "Turn.h"


namespace cs31
{

class Obsession
{
public:
  // CS 31 students need to complete the TODO methods in this class
  // Each Obsession game holds two players, a Human and a Computer
  // as well as a DieManager
  Obsession();
  
  // the possible states of the game
  enum class GameOutcome { HUMANWONGAME, COMPUTERWONGAME, TIEDGAME, GAMENOTOVER };
  
  // various output methods
  std::string display( std::string msg = "" );
  std::string endingMessage( ) const;
  void showDice();

  // randomly roll the dies
  void roll();
  // cheat the game's dies
  void roll( Die d1, Die d2 );
  // play the turn parameter on the human player
  bool acceptHumanTurn( Turn & t, bool noOutput=true );
  // can the turn parameter be played on the human player at this moment in the game?
  bool acceptableHumanTurn( Turn & t );
  // play the human's turn using the DieManager's dies
  bool humanPlay( );
  // cheat the human's turn
  bool humanPlay( Die d1, Die d2 );
  // turn all the human's up Rings into safe Rings
  void endHumanTurn( );
  // CS 31 TODO
  // play the computer's turn using the DieManager's dies
  bool computerPlay( );
  // CS 31 TODO
  // cheat the computer's turn
  bool computerPlay( Die d1, Die d2 );
  // CS 31 TODO
  // turn all the computer's up Rings into safe Rings
  void endComputerTurn( );
  
  // CS 31 TODO
  // determine the current state of the game
  Obsession::GameOutcome determineGameOutcome( ) const;
  // has the game ended?
  bool isGameOver() const;
  
  // accessor methods
  Player getHuman() const;
  Player getComputer() const;
private:
  Player mHuman, mComputer;
  DieManager mDieManager;
};

}

#endif 
