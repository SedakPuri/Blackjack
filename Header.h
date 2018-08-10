//  Sedak Puri
//  Header.h
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/28/18.
//  Copyright © 2018 Sedak Puri. All rights reserved

#ifndef Header_h
#define Header_h
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

//Prototype
void resetDeck();
Card dealACard();
Card convertValue(int);
void displayCards();
void displayMenu();
int getInput(Player *ptrPlayer);
bool computerComputeMove(Player *pDealer);
void initialDeal(Player *pUser, Player *pDealer);
string getSymbol(int suit);
void askUserAceValue(Card &c, Player *pUser);
bool checkEndConditions(Player *pUser, Player *pDealer, bool userDone, bool dealerDone);

//Conversion from a suit to a string for output
string operator ! (Suit &s);

//Constant arrays
const string suitStr[] = {"Hearts", "Spades", "Diamonds", "Clubs"};
const string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

#endif /* Header_h */
