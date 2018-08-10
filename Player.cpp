//  Sedak Puri
//  Player.cpp
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/31/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.

#include "Player.h"
const string suitStr[] = {"Hearts", "Spades", "Diamonds", "Clubs"};
const string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

//Constructor
Player::Player(string name){
    this->m_name = name;
    m_currentHandSum = 0;
}

//Adding a card to a vector that represents the hand
void Player::m_addCard(Card c){
    m_cardsHeld.push_back(c);
    m_updateCurrentHandSum();
}

//Method to display the cards held in someone's hand
void Player::m_displayCards(){
    int sizeCounter = static_cast<int>(m_cardsHeld.size());
    cout<<"\nCards Held: [";
    for(Card c: m_cardsHeld){
        cout<<c.m_rank<<" of "<<suitStr[c.m_suit];
        if ((m_cardsHeld.size() > 1) && (--sizeCounter != 0)){
            cout<<", ";
        }
    }
    cout<<"]"<<endl<<"Current Sum of Hand: "<<m_currentHandSum<<endl<<endl;
}

//Method to update one's current hand sum based on the cards held in hand (parsing through the vector of cards)
void Player::m_updateCurrentHandSum(){
    int sum = 0;
    for(Card c: m_cardsHeld){
        sum += c.m_cardValue;
    }
    m_currentHandSum = sum;
}
