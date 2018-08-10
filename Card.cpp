//  Sedak Puri
//  Card.cpp
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/31/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.
//

#include "Card.h"
using namespace std;

//Constructor
Card::Card(string name, int cardNum, Suit s){
    this->m_rank = name;
    this->m_suit = s;
    this->m_cardNum = cardNum;
    
    //Initializing Value
    if((this->m_cardNum >= 1) && (this->m_cardNum < 11)){
        this->m_cardValue = this->m_cardNum;       //Cards between 1-10 are worth their respective values (Ace already adjusted for)
    } else if (this->m_cardNum >= 11){
        this->m_cardValue = 10;                  //Face cards are worth 10
    }
}

//Method for the visual display of symbols
string Card::m_getSymbol(){
    switch (m_suit) {
        case 0:
            return "\u2665";
        case 1:
            return "\u2660";
        case 2:
            return "\u2666";
        case 3:
            return "\u2663";
    }
    return "";
}
