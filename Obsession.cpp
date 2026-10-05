//
//  Obsession.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//
#include <iostream>
#include <string>
#include <sstream>
#include "Obsession.h"


namespace cs31
{

// setup the game
// by naming the players, the output is abit more readable
Obsession::Obsession() : mHuman( "Human" ), mComputer( "Computer" )
{
  
}

// output method
void Obsession::showDice()
{
  std::cout << "---     \t\t---        \t\t---DIES\t\t";
  std::cout << mDieManager.getDie1().getValue() << " " << mDieManager.getDie2().getValue();
  std::cout << std::endl;
}

// output method
std::string Obsession::display( std::string msg )
{
  std::string s;
  s += "---HUMAN\t\t---COMPUTER\t\t---DIES\t\t";
  s += std::to_string( mDieManager.getDie1().getValue() );
  s += " ";
  s += std::to_string( mDieManager.getDie2().getValue() );
  s += "\n";
  
  std::string htext = mHuman.display();
  std::istringstream h(htext); // Create an input string stream from the htext
  std::string hline;
  
  std::string ctext = mComputer.display();
  std::istringstream c(ctext); // Create an input string stream from the ctext
  std::string cline;
  
  // Loop through the string stream, extracting lines separated by '\n'
  while (std::getline(h, hline, '\n')) {
    std::getline( c, cline, '\n' );
    s += hline;
    s += "\t\t";
    s += cline;
    s += "\n";
  }
  
  s += msg;
  return( s );
}

// output method
std::string Obsession::endingMessage( ) const
{
  std::string result = "";
  GameOutcome outcome = determineGameOutcome();
  switch( outcome )
  {
    case GameOutcome::GAMENOTOVER:
      result = "Obsession ended without a winner!";
      break;
    case GameOutcome::TIEDGAME:
      result = "Neither Player won!";
      break;
    case GameOutcome::HUMANWONGAME:
      result = "Obsession was won by the Human player!";
      break;
    case GameOutcome::COMPUTERWONGAME:
      result = "Obsession was won by the Computer player!";
      break;
  }
  return( result );
}

// randomly roll the dies
void Obsession::roll()
{
  mDieManager.roll();
}

// cheat the game's dies
void Obsession::roll( Die d1, Die d2 )
{
  // cheating..
  mDieManager.roll( d1, d2 );
}

// can this turn be played at this time by the Human player?
bool Obsession::acceptableHumanTurn( Turn & t )
{
  return( mHuman.acceptableTurn( t, mDieManager, mComputer ) );
}

// play the turn parameter on the human player
bool Obsession::acceptHumanTurn( Turn & t, bool noOutput )
{
  bool result = false;
  if (t.isValid())
  {
    result = mHuman.useTurn(t, mComputer, noOutput);
  }
  return( result );
}

// play the human's turn using the DieManager dies
// return true if human play can keep rolling
bool Obsession::humanPlay( )
{
  return( humanPlay( mDieManager.getDie1(), mDieManager.getDie2() ) );
}

// cheat the human's turn
// return true if human play can keep rolling
bool Obsession::humanPlay( Die d1, Die d2 )
{
  bool result = false;
  if (mHuman.useDies( d1, d2, mComputer ))
  {
    result = true;
  }
  return( result );
}

// CS 31 TODO
// play the computer's turn using the DieManager dies
// return true if computer play can keep rolling
bool Obsession::computerPlay( )
{
  // for now...
    return( computerPlay( mDieManager.getDie1(), mDieManager.getDie2() ) );
}

// CS 31 TODO
// cheat the computer's turn
// return true if computer play can keep rolling
bool Obsession::computerPlay( Die d1, Die d2 )
{
    bool result = false;
    if (mComputer.useDies( d1, d2, mHuman ))
    {
      result = true;
    }
    return( result );
}

// turn all the human's up Rings into safe Rings
// all Ring's with state UP get turned into state SAFE
void Obsession::endHumanTurn( )
{
  mHuman.endTurn();
}

// CS 31 TODO
// turn all the computer's up Rings into safe Rings
// all Ring's with state UP get turned into state SAFE
void Obsession::endComputerTurn()
{
    mComputer.endTurn();
}


// CS 31 TODO
// determine the current state of the game
// game ends when one or both plays have all safe Rings
Obsession::GameOutcome Obsession::determineGameOutcome( ) const
{
  Obsession::GameOutcome outcome = Obsession::GameOutcome::GAMENOTOVER;
    if (mHuman.Player::allUpOrSafe() && mComputer.Player::allUpOrSafe()){//uses code in player class for alluporsafe
        outcome = Obsession::GameOutcome::TIEDGAME;
    }
    else if (mHuman.Player::allUpOrSafe()){
        outcome = Obsession::GameOutcome::HUMANWONGAME;
    }
    else if (mComputer.Player::allUpOrSafe()){
        outcome = Obsession::GameOutcome::COMPUTERWONGAME;
    }
    
  return( outcome );
}

// has the game ended?
// game ends when one or both plays have all safe Rings
bool Obsession::isGameOver() const
{
  return( determineGameOutcome() != Obsession::GameOutcome::GAMENOTOVER );
}

// accessor method
Player Obsession::getHuman() const
{
  return( mHuman );
}

// accessor method
Player Obsession::getComputer() const
{
  return( mComputer );
}


}
