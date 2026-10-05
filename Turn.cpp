//
//  Turn.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/7/25.
//

#include "Turn.h"

namespace cs31
{

// a Turn represents a Player's turn of play in an Obsession game
// it might be one or two different moves
// the moves must be legally allowable based on the game rules
// by default, neither Move is valid
// by default, howMany is zero
Turn::Turn( ) : mMove1( false, 0 ), mMove2( false, 0 ), mHowMany(0), mFullyConsumed(false)
{
  
}

// a Turn represents a Player's turn of play in an Obsession game
// it might be one or two different moves
// the moves must be legally allowable based on the game rules
// by default, neither Move is valid
// by default, howMany is zero
// then construct this Turn's Moves from the string parameter
Turn::Turn( std::string data ) : mMove1( false, 0 ), mMove2( false, 0 ), mHowMany(0), mFullyConsumed(false)
{
  // where is the end of the first move?
  size_t position = 1;
  bool   endloop = false;
  bool   isValid = true;
  // parse u2d3    or    u2     or    d3   or   d10    d3d1    or d3d10
  if (data.length() >= 2 && data.length() <= 6)
  {
    // go after the first move
    while( position < data.length() && !endloop && isValid)
    {
      switch( data.at( position ) )
      {
        case 'U':
        case 'u':
        case 'd':
        case 'D':
          endloop = true;
          break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          position = position + 1;
          break;
        default:
          isValid = false;
          break;
      }
    }
    if (isValid)
    {
      mMove1 = buildMoveFromString( data.substr(0, position ) );
      mHowMany = 1;
      if (position != data.length())
      {
        // go after the second move
        mMove2 = buildMoveFromString( data.substr( position, data.length() - position ) );
        mHowMany = 2;
      }
    }
  }
}

// accessor method
Move Turn::getMove1() const
{
  return( mMove1 );
}

// accessor method
Move Turn::getMove2() const
{
  return( mMove2 );
}

// accessor method
int  Turn::howManyMovesInThisTurn() const
{
  return( mHowMany );
}

// accessor method
// is this Turn valid?
// CS 31 TODO
// verifies that howMany is either 1 or 2, that each Move is valid
// and that when there are two Moves, if they both are not exactly the same,
// u3u3 is allowed but d3d3 is not allowed
bool Turn::isValid() const
{
    if (howManyMovesInThisTurn() != 1 && howManyMovesInThisTurn() != 2){
        return false;
    }
    if (howManyMovesInThisTurn() == 1){ //when only one move
        if (!getMove1().Move::isValid()){
            return false;
        }
    }
    else if (howManyMovesInThisTurn() == 2){//two moves, need to check if both are valid and they aren't the same
        if (getMove1().Move::isValid() && getMove2().Move::isValid()){ //if both numbers valid
            if (getMove1().getValue() == getMove2().getValue() && getMove1().isUp() == getMove2().isUp()){ // but they are the exact same
                return false;
            }
        }
        if (!getMove1().Move::isValid() || !getMove2().Move::isValid()){ //if one isn't valid
            return false;
        }
    }
  return true; //default
}

// helper method
Move Turn::buildMoveFromString( std::string data )
{
  // pull up or down and a number from the string
  Move result( false, 0 );
  bool isUp = false;
  bool isValid = false;
  size_t position = 0;
  if (data.at( position ) == 'u' || data.at( position ) == 'U')
  {
    isUp = true;
  }
  else if (data.at( position ) == 'd' || data.at( position ) == 'D')
  {
    isUp = false;
  }
  position = 1;
  int value = extractNumber(data, position, isValid);
  if (isValid)
  {
    result = Move( isUp, value );
  }
  return( result );
}

// helper method
// parse out the number characters found at index
// update the index for each number character found
// return true in isValid if there is a value between 1 and 10
int Turn::extractNumber( std::string data, size_t& index, bool& isValid )
{
    // track the integer value found
    int quantity( 0 );
    
    isValid = true;
    // do we have more characters to read??
    // this prevents the function from returning the default quantity value (zero)
    // when no characters are actually read from the airport string at all
    if (index >= data.length())
    {
        isValid = false;
    }
    else
    {
        // do we have more characters to read??
        if (index >= data.length())
        {
            isValid = false;
        }
        else if (data[index] == '0')
        {
            // no leading zeros allowed
            isValid = false;
        }
        else
        {
            // the number should be made up of digits
            while( index < data.length()  &&  isdigit( data[ index ] ) )
            {
                // extract one digit and add it to the cumulative value held in quantity
                int digit = data[ index ] - '0';
                quantity = quantity * 10 + digit;
                index = index + 1;
            }
        }
    }
    // if we got this far, be sure there are some digits read
    if (isValid)
        isValid = (quantity > 0 && quantity < 11);
    return( quantity );

}


bool Turn::matchAgainstDies( DieManager manager )
{
  // does this turn match what is currently rolled??
  // also remember for later whether this turn was fully consumed by these dice
  bool result = false;
  
  if (mHowMany == 1)
  {
    // then this sum must equal the two dies!
    result = (mMove1.getValue() == ( manager.getDie1().getValue() + manager.getDie2().getValue()  ) );
    if (result)
    {
      mFullyConsumed = true;
    }
    // is this a partial usage?   r 6 6  u6??
    else
    {
      result = (mMove1.getValue() == manager.getDie1().getValue()) || (mMove1.getValue() == manager.getDie2().getValue() );
    }
  }
  if (mHowMany == 2)
  {
    // each die must be found in move1 or move2
    if (mMove1.getValue() == manager.getDie1().getValue())
    {
      if (mMove2.getValue() == manager.getDie2().getValue())
      {
        result = true;
        mFullyConsumed = true;
      }
    }
    // other way around...
    else if (mMove1.getValue() == manager.getDie2().getValue())
    {
      if (mMove2.getValue() == manager.getDie1().getValue())
      {
        result = true;
        mFullyConsumed = true;
      }
    }
  }
  
  return( result );
}

bool Turn::wasFullyConsumed()
{
  return( mFullyConsumed );
}

void Turn::setFullyConsumed( bool value )
{
  mFullyConsumed = value;
}


}
