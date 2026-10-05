//
//  main.cpp
//  Obsession
//
//  Created by Howard Stahl on 9/6/25.
//

#include <iostream>
#include <string>
#include <cassert>
#include "Die.h"
#include "DieManager.h"
#include "Ring.h"
#include "Player.h"
#include "Obsession.h"
#include "Turn.h"
using namespace cs31;
using namespace std;

int main()
{
    using namespace cs31;
    using namespace std;
  
    cout <<
        "This is the Obsession Game. Play with (p), Quit with (q), and Endround with (e). Your goal is to have all numbers SAFE before the computer. When prompted with turn:, type in your move: i.e. u3u4 to move spots 3 and 4 up. Your number will become safe if it survives being up for a full turn. \n";
    // interactive main to play the Obsession game
    Obsession game;
    game.roll();
    Turn t;
    bool stopLooping = false;
  
    std::string value;
    std::string action, message = "(p)lay (e)ndround (q)uit: ";
    cout << game.display( message ) << endl;
    
    do
    {
        getline( cin, action );
        while (action.size() == 0)
        {
            getline( cin, action );  // no blank entries allowed....
        }
        switch (action[0])
        {
          default:
            continue;
          case 'Q':
          case 'q':
            stopLooping = true;
            break;
          case 'P':
          case 'p':
            cout << "turn:";
            cin >> value;
            cout << endl;
            t = Turn( value );
            if (t.isValid() && game.acceptableHumanTurn(t))
            {
              game.acceptHumanTurn(t, false);
            }
            if (t.wasFullyConsumed())
            {
              game.roll();
              cout << game.display( message ) << endl;
              stopLooping = game.isGameOver();
              break;
            }
            else
            {
              // if the turn was not fully consumed,
              // fall thru to run the computer's turn
              cout << ">>>turn not fully consumed - round needs to end<<<" << endl;
            }
            // g31 will warn about the lack of a break here
            // but it is actually desired
          case 'E':
          case 'e':
            // since Human turn ended, end the computerTurn from before
            game.endComputerTurn();
            do
            {
              game.roll();
              game.showDice();
              game.display();
            } while( game.computerPlay() );
            // since the Computer turn ended, end the humanTurn from before
            game.endHumanTurn();
            game.roll();
            cout << game.display( message ) << endl;
            stopLooping = game.isGameOver();
            break;
        }
        
    } while( !stopLooping  );
    cout << game.endingMessage() << endl;


    return( 0 );
}


