//  Sedak Puri
//  main.cpp
//  Blackjack
//  Compiler: Xcode
//  Created by Sedak Puri on 7/28/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.

#include "Header.h"
using namespace std;

//Setup
bool availableCards[52]; //False if occupied

//Main
int main() {
    //Misc Setup
    resetDeck();
    srand(static_cast<unsigned int>(time(nullptr)));    //Setting seed
    
    //Game Setup
    string name;
    cout<<"Hello user! Welcome to the game of Blackjack! Please enter your something we can call you by to begin..."<<endl;
    getline(cin, name);
    
    //Allocation of Memory
    Player *pUser = new Player(name);
    Player *pDealer = new Player("Dealer");
    if(!pUser || !pDealer){
        cout<<"Fatal error!";
        exit(-1);
    }
    
    //Output and Rules
    cout<<"\nOk "<<pUser->m_name<<", lets see what you're made of!"<<endl;
    string response;
    do{
        cout<<"But before we begin, would you like to know the rules of blackjack? (y or n)"<<endl;
        cin>>response;
        if(response == "y"){
            cout<<"\nBlackjack is a card game where individual players are playing against the dealer and want to get as close to or to the “magic number” 21 (and any number over 21 would result in a bust or a loss). To begin the game of blackjack, players and the dealer receive two cards each (where the player’s cards are dealt face up and the dealer keeps one of his cards face down). The value of a player’s hand is the sum of the value of their cards. At each turn, the player has a choice to “hit” or pass, where if the player hits, the dealer would deal them an additional card to hopefully get the player closer to a hand value closer to but not over 21."<<endl;
            break;
        }
        if(response == "n"){
            break;
        }
    } while(true);

    cout<<"\nOk now that we have that sorted out, let me introduce you to the Menu! (System will only respond to # responses below)"<<endl;
    displayMenu();
    
    //Prompt to begin game!
    cout<<"\n\n"<<pUser->m_name<<" Press and Enter Anything to Begin!"<<endl;
    cin>>response;
    
    cout<<"\n\n\n***** Welcome to Blackjack by Sedak Puri *****"<<endl;
    //Gameloop
    bool gamestate = true;
    int gamecounter = 1;
    do{
        //Initial Output
        cout<<endl<<"\t\t\t  \u2665\u2660\u2666\u2663 Game "<<gamecounter++<<" \u2663\u2666\u2660\u2665"<<endl;
        resetDeck();                                                                  //Resets deck to reduce lag (this is absolutely necessary through testing)
        
        //Initial Deal
        initialDeal(pUser, pDealer);
        
        //Response loop
        bool dealerDone = false, userDone = false, allowDealerMove = true;
        while(true){
            //User Gameplay
            if (!userDone){
                //Get User Input and Interpret it!
                int selection = getInput(pUser);     //Selection Variable can only be 0-4
                if(selection == 0){
                    displayMenu();
                    allowDealerMove = false;
                } else if(selection == 1){
                    pUser->m_displayCards();
                    allowDealerMove = false;
                } else if(selection == 2){
                    Card card = dealACard();
                    cout<<"\n"<<pUser->m_name<<" hit a "<<card.m_rank<<" of "<<card.m_getSymbol()<<!card.m_suit<<card.m_getSymbol()<<" (+"<<card.m_cardValue<<")"<<endl;
                    
                    //Handling case that ace was drawn!
                    if(card.m_cardNum == 1){
                        askUserAceValue(card, pUser);
                    }
                    pUser->m_addCard(card);
                    cout<<"(The value of your hand is now: "<<pUser->m_currentHandSum<<")"<<endl<<endl;
                    allowDealerMove = true;
                } else if(selection == 3){
                    cout<<"Passed! Ending hand value: "<<pUser->m_currentHandSum<<endl<<endl;
                    userDone = true;                                                        //Indicating the user is done hitting
                    allowDealerMove = true;
                } else if(selection == 4){
                    break;
                }
            }
            
            //Checking to see if game has ended (false if game is ended)
            if(!checkEndConditions(pUser, pDealer, userDone, dealerDone)){
                break;
            }
            
            //Computer Gameplay
            if(pDealer->m_currentHandSum > 21)                          //Case: Dealer busted!
                dealerDone = true;
            if (!dealerDone && allowDealerMove){
                bool dealerResponse = computerComputeMove(pDealer);
                if(dealerResponse){
                    Card card = dealACard();
                    cout<<"* "<<pDealer->m_name<<" has hit a "<<card.m_rank<<" of "<<card.m_getSymbol()<<!card.m_suit<<card.m_getSymbol()<<" (+"<<card.m_cardValue<<")"<<endl<<endl;
                    pDealer->m_addCard(card);
                } else if (!dealerResponse){
                    cout<<"* "<<pDealer->m_name<<" has passed!"<<endl<<endl;
                    dealerDone = true;
                }
            }
            
            //Checking to see if game has ended (false if game is ended)
            if(!checkEndConditions(pUser, pDealer, userDone, dealerDone)){
                break;
            }
        }
        
        //Asking user for another round
        do{
            //User input
            cout<<"\nWould you like to play again? (y or n)"<<endl;
            cin>>response;
            if(response == "y"){
               pUser = new Player(name);
               pDealer = new Player("Dealer");
            } else if(response == "n"){
                //Deleting Allocated Memory
                delete pUser;                                                                                                   
                delete pDealer;
                gamestate = false;
            }
        } while((response.length() != 1) && (response != "y") && (response != "n"));
    } while(gamestate);
    cout<<"\n\nThanks for playing!"<<endl;
    return 0;
}

//Method to reset the deck
void resetDeck(){
    for (int i = 0; i < 52; i++){
        availableCards[i] = true;
    }
}

//Method to display the menu of options
void displayMenu(){
    cout<<"\nOperations: "<<endl
    <<"0\t\tShow Menu"<<endl
    <<"1\t\tShow Cards In Hand and Current Hand Sum"<<endl
    <<"2\t\tHit"<<endl
    <<"3\t\tPass"<<endl
    <<"4\t\tExit Current Game"<<endl;
}

//Method to get user input on what command to perform
int getInput(Player *pUser){
    double responseTime = 0;
    string input;
    clock_t begin, end;
    do{
        begin = clock();
        cout<<"---------------------------------------------"<<endl;
        cout<<"What would you like to do? (Enter 0 for Menu)"<<endl;
        cout<<"---------------------------------------------"<<endl;
        cout<<"(The value of your hand is now: "<<pUser->m_currentHandSum<<")"<<endl<<endl;
        cin>>input;
        end = clock();
    } while((input.length() != 1) || ((atoi(input.c_str()) != 0) && (atoi(input.c_str()) != 1) && (atoi(input.c_str()) != 2) && (atoi(input.c_str()) != 3) && (atoi(input.c_str()) != 4)));
    if (atoi(input.c_str()) == 2)
        responseTime = double(end - begin);
    return atoi(input.c_str());
}

//Method to deal a random card
Card dealACard(){
    unsigned int cardIndex;
    static unsigned int cardsDealt = 0;
    
    //Random number generation
    do{
        cardIndex = rand() % 52 + 1;                 //cardNum range from 1-52
        
        //Checking if card already drawn
        if(availableCards[cardIndex]){
            availableCards[cardIndex] = false;
            cardsDealt++;
            break;
        }
    } while(true);
    
    //Returning the card
    return convertValue(cardIndex);
}

//Method to convert a card value into a card object
Card convertValue(int cardValue){
    if((cardValue > 0) && (cardValue <= 13)){
        return Card(ranks[cardValue % 13], 1 + (cardValue % 13), static_cast<Suit>(0));
    } else if((cardValue > 13) && (cardValue <= 26)){
        return Card(ranks[cardValue % 13], 1 + (cardValue % 13), static_cast<Suit>(1));
    } else if((cardValue > 26) && (cardValue <= 39)){
        return Card(ranks[cardValue % 13], 1 + (cardValue % 13), static_cast<Suit>(2));
    } else {                                                                      //Condition: (cardValue > 39) && (cardValue <= 52)
        return Card(ranks[cardValue % 13], 1 + (cardValue % 13), static_cast<Suit>(3));
    }
}

//Method to compute a move for the computer (based on the rules of blackjack)
bool computerComputeMove(Player *pDealer){
    //Dealer must hit on 16 or below
    if(pDealer->m_currentHandSum <= 16){
        return true;
    //Dealer must stand on 17-21
    } else {
        return false;
    }
}

//Method to ask the user if they want to count the ace as an 11 or 1
void askUserAceValue(Card &card, Player *pUser){
    string input;
    do{
        cout<<"Would you like to count this card as a 1 or 11?"<<endl;
        cin>>input;
        
        //Adjusting the value of ace respectively
        if(input == "1"){
            card.m_cardValue = 1;              //Case: Ace counted as 1
            pUser->m_updateCurrentHandSum();
        }
        if (input == "11"){
            card.m_cardValue = 11;             //Case: Ace counted as 11
            pUser->m_updateCurrentHandSum();
        }
    } while ((input != "1") && (input != "11"));
}

//Method to check ending conditions to see if either the user or dealer has won
bool checkEndConditions(Player *pUser, Player *pDealer, bool userDone, bool dealerDone){
    //Condition: If the player has blackjack, they win, unless the dealer also has blackjack, in which case the game is a tie.
    if((pUser->m_currentHandSum == 21) && (pDealer->m_currentHandSum == 21)){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"GAME OVER: There is a tie! Both the deler and yourself have a Blackjack!!"<<endl;
        cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return false;
    } else if (pUser->m_currentHandSum == 21){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"GAME OVER: Blackjack, you won! Your hand value is 21! Congratulations!"<<endl;
        cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return false;
    } else if (pDealer->m_currentHandSum == 21){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"GAME OVER: Sorry, the dealer won and received a blackjack! Better luck next time "<<pUser->m_name<<"!"<<endl;
        cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
       cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return false;
    }
    
    //Condition: If the dealer busts and the player doesn't, the player wins. + Condition: If the player busts, the dealer wins.
    if(pDealer->m_currentHandSum > 21){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"GAME OVER: You win! The dealer has busted!"<<endl;
        cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return false;
    } else if (pUser->m_currentHandSum > 21){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"GAME OVER: You lost! You have busted!"<<endl;
        cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
       cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        return false;
    }
    
    //Condition: If the player and the dealer both don't bust, whoever is closest to 21 wins.
    if(userDone && dealerDone){                                                                   //The user is done hitting and passing!
        if(pUser->m_currentHandSum > pDealer->m_currentHandSum){
           cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout<<"GAME OVER: You win!"<<endl;
            cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
           cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        } else if (pDealer->m_currentHandSum > pUser->m_currentHandSum){
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout<<"GAME OVER: You Lost!"<<endl;
            cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        } else if (pUser->m_currentHandSum == pDealer->m_currentHandSum){
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout<<"GAME OVER: You have tied the dealer!"<<endl;
            cout<<"Ending Hands:\tYour Hand: "<<pUser->m_currentHandSum<<"\tDealer Hand: "<<pDealer->m_currentHandSum<<endl;
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
        return false;
    }
    return true;
}

//Method to handle the initial 4 deals
void initialDeal(Player *pUser, Player *pDealer){
    cout<<"-------------"<<endl;
    cout<<"Initial Deal!"<<endl;
    cout<<"-------------"<<endl;
    
    for (int i = 0; i < 4; i++){
        Card card = dealACard();
        
        if (i < 2){                  //Users Initial Deal
            cout<<"\n"<<pUser->m_name<<" received a "<<card.m_rank<<" of "<<card.m_getSymbol()<<!card.m_suit<<card.m_getSymbol()<<" (+"<<card.m_cardValue<<")"<<endl;
            
            //Handling case that ace was drawn!
            if(card.m_cardNum == 1){
                askUserAceValue(card, pUser);
            }
            pUser->m_addCard(card);
            cout<<"(The value of your hand is now: "<<pUser->m_currentHandSum<<")"<<endl<<endl;
        } else if (i == 2){           //Dealers Initial Deal (facedown)
            cout<<"\n"<<"* "<<pDealer->m_name<<" was dealt themself a facedown card..."<<endl;
            pDealer->m_addCard(card);
        } else if (i == 3){           //Dealers Initial Deal (faceup)
            cout<<"\n"<<"* "<<pDealer->m_name<<" received a "<<card.m_rank<<" of "<<card.m_getSymbol()<<!card.m_suit<<card.m_getSymbol()<<" (+"<<card.m_cardValue<<")"<<endl<<endl;
            pDealer->m_addCard(card);
        }
    }
}

//Conversion from suit enum to string for simplicity of output
string operator ! (Suit &s){
    return suitStr[s];                                              //Implicit conversion (Suit -> Int)
}
