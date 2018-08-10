//  Sedak Puri
//  Player.hpp
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/31/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.

#ifndef Player_hpp
#define Player_hpp
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

//Player Class
class Player{
public:
    Player(string);
    void m_addCard(Card);
    void m_displayCards();
    void m_updateCurrentHandSum();
    string m_name;
    int m_currentHandSum;
private:
    vector<Card> m_cardsHeld;
};
#endif /* Player_hpp */
