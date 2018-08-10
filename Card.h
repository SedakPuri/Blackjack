//  Sedak Puri
//  Card.hpp
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/31/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.

#ifndef Card_hpp
#define Card_hpp
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Enums
enum Suit{hearts, spades, diamonds, clubs};

//Card Class
class Card{
public:
    Card(string, int, Suit);
    string m_getSymbol();
    int m_cardNum;              //Value of card acting as an index (range: 1-13)
    int m_cardValue;            //Value of card with respect to blackjack (face cards worth 10, aces worth 1 or 11, and number words worth their respective value)
    string m_rank;
    Suit m_suit;
};

#endif /* Card_hpp */
