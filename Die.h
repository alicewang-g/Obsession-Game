//
//  Die.h
//  Obsession
//
//

#ifndef Die_h
#define Die_h

namespace cs31
{
    
// This class is completely finished and has no work for CS 31 students to complete
// a randomly tossable and cheatable die that is 6 sided by default
class Die
{
public:
    // by default, a six sided Die
    Die( int sides = 6 );
  
    // toss the Die
    void roll();
  
    // get the value of the Die
    int  getValue( ) const;
    
    // for cheating purposes by forcing a value into the Die
    void setValue( int value );
private:
    int  mSides;
    int  mValue;
};

    
}
#endif /* Die_h */
