///************************************************************************
//COSC 501                                              
//Barnabas Ravindranath                                 11/19/16
//Program Name:  Programming Assignment 3
// 
#include <cstdlib>
#include<iostream>
#include<string>
#include <ctime>
#include <iomanip>

using namespace std;
char ans;

struct Card{
    int value;
    string suit;
};

void new_line();

class Deck {
    
    public:
    
        //constructor that builds deck
        Deck();

        //an array of struct that represents our deck
        Card cards[52];

        //picks a random card, places card picked at the end of array,
        //and returns card
        Card DrawCard();

private:
    //when dealing card this value keeps track of available cards to deal in the array
    int size;
    
};


class Hand  {
public:
    
   Card hand[52]; 
   int num_of_cards = 0;
   
   int get_value(Card card);
   
   int All_Output(int n);
   
   int Hide(Card card);
   
   int count_ace(int i);
   
   //places card in respective players hand
   Card Place(Card card);
   
private:
    
    //used in get_value
    int card_value;
    
    //used to keep track of card arrays in function All_Output and Place
    int s = 0;
    
    int r = 0;
    
    //array that holds players hand
    Card cards_1[10];
    
    //keeps track of number of aces in hand and allows program
    //know whether to count ace as 1 or 11 deck
    //1 if hand is over 21, and 11 if hand is under 21
    int ace;
    
  
};

//class for player
class Player {
    public:
        
        //constructor
        Player();
        
        //makes the hand class accessible to this player class
        Hand hand;
    
};

//function to check if dealer or player value is 21 and also ask if player wants to draw again
char istwentyone(int x);

//gets final result for dealer and player's hand
void getresult(int dealer_total, int hand_value);


int main() {
    
    do {
        
    srand(time(NULL));
    int a = 0, player_total = 0, dealer_total = 0, num = 0, hand_value = 0;
 
    Deck deck;
    Player player;
    Player dealer;
    
    cout << setw(50) << "ROCK, PAPER, SCISSOR\n" << endl;
    
    cout << "Please Enter Positive Number to start game!";
        cin >> num;
        new_line();
       
        cout << endl << "Dealer's Hand" << endl; 

            dealer_total = dealer_total + dealer.hand.get_value(dealer.hand.Place(deck.DrawCard())); 

            dealer_total = dealer_total + dealer.hand.Hide(dealer.hand.Place(deck.DrawCard()));
         
             
        cout << "Player's Hand" << endl;

            player_total = player_total + player.hand.get_value(player.hand.Place (deck.DrawCard()));

            player_total = player_total + player.hand.get_value(player.hand.Place(deck.DrawCard()));
            
        //stores player's total hand value    
        hand_value = player.hand.count_ace(player_total);
        
        cout << "Your Total is: " << player.hand.count_ace(player_total)  << endl;
        
        //check if player value is 21 and also ask if player wants to draw again
        ans = istwentyone(hand_value);
        
        if((ans == 'Y') || (ans == 'y')) {

            do {

                cout << "Here is Your Current Hand!" << endl;;

                //Displays again players current hand
                while (a < player.hand.num_of_cards) player.hand.All_Output(a++); a=0;

                cout << "Here is Your New Card!" << endl;

                //gives and displays players new card
                player_total = player_total + player.hand.get_value(player.hand.Place(deck.DrawCard()));

                //updates hand value;
                hand_value = player.hand.count_ace(player_total);

                cout << endl << endl << "Your Total is: " << hand_value  << endl;

                //if busted, then we check dealer's card.
                if (hand_value > 21) {
                    cout << "YOU BUSTED!!" << endl;
                    ans = 'N';
                }

                //checks to see if 21 or ask player if he or she wants to draw again
                else ans = istwentyone(hand_value);


            } while((ans == 'Y') || (ans == 'y'));

        }
        
        if ((ans == 'N') || (ans == 'n')) {

            cout << "Dealer's Cards: " << endl;

            //if dealer's hand is over 17, it will not deal itself another card 
            //and just display hand
            if (dealer_total >= 17){
                while (a < dealer.hand.num_of_cards) dealer.hand.All_Output(a++);
                a = 0; 
            }

            //if dealer's hand is under 17, it will deal itself cards until over 17
            if (dealer_total < 17) {

                //condition to check until dealer's hand goes over 17
                while (dealer_total < 17){

                    //displays dealer's hand
                    while(a <dealer.hand.num_of_cards)dealer.hand.All_Output(a++);

                    //deals dealer another card
                    dealer_total = dealer_total + dealer.hand.get_value(dealer.hand.Place(deck.DrawCard()));
                } 
            }

            cout << endl << endl;

            cout << "The Dealer's Total is: " << dealer_total << endl;

            getresult(dealer_total, hand_value); 

        }

            cout << "Want to Play Again? (Yes/No) ";
            cin >> ans;
            new_line();
    
    } while ((ans == 'Y') || (ans == 'y'));
    
    
    return 0; 
}


Deck::Deck() {
    
    size = 52;

    string array[4] = {"Spades", "Heart", "Diamond", "Clubs"};
    
    int y = 0, count = 0;
    
    for (int x = 0; x < 52; x++) { 
        //Each suit has 13 cards, this restarts count at 2
        if (y % 13 == 0) { 
            y = 0;  
            cards[x].value = 2; 
            cards[x].suit = array[count];
        }
        //this gives each suit card a value from 2-14
        //giving the cards this value range will help distinguish 
        //between jacks, queens, kings, and aces in get value function
        else { 
            cards[x].value = y+2; 
            cards[x].suit = array[count];
            if (y % 12 == 0) count++;    
        }
        y++;
    }
}

Card Deck::DrawCard() {
    
    int a = rand() % size;
    Card temp = cards[a];
    cards[a] = cards[size-1]; //places card at the end of the array
    cards[size-1] = temp;
    size--;
    return temp;
    
}
        
int Hand::get_value(Card card) {
    
   
    //returns values for 2-10
    if (card.value < 11) {
        
        card_value = card_value + card.value;
 
        cout << "<" << card.value << "><" << card.suit << ">\n\n";
        
        return card.value;
    }
    //returns value for Jack, Queen, and King
    else if((card.value >= 11) && (card.value < 14 )){

        //card_value = card_value + 10;
       
        if (card.value == 11) cout << "<" << "J" << "><" << card.suit << ">\n\n";
        
        if (card.value == 12) cout << "<" << "Q" << "><" << card.suit << ">\n\n";
     
        if (card.value == 13) cout << "<" << "K" << "><" << card.suit << ">\n\n";
  
        return 10;    
    }
  
    //returns value of ace
    else if(card.value == 14){
        
        //card_value = card_value + 11;
        
        cout << "<" << "A" << "><" << card.suit << ">\n\n";
        
        ace = ace + 1; //updates how many ace in hand
        
        return 11;
    }    
}

Player::Player(){ }

int Hand::Hide(Card card)
{
      
    //returns values for 2-10
    if (card.value < 11) {
        
        card_value = card_value + card.value;
        
        cout << "HIDDEN CARD\n\n";
        
        return card.value;
        
    }
    //returns value for Jack, Queen, and King
    else if((card.value >= 11) && (card.value < 14 )){
        
       // card_value = card_value + 10;

        if (card.value == 11) {
            
            cout << "HIDDEN CARD\n\n";
  
        }
        if (card.value == 12) {
            
            cout << "HIDDEN CARD\n\n";
  
        }
        if (card.value == 13) {
            
            cout << "HIDDEN CARD\n\n";
        }
          return 10;  
    }
    //returns value of ace
    else if(card.value == 14){
 
       // card_value = card_value + 11;
        
        cout << "HIDDEN CARD\n\n";
        
        return 11;
    }
}

int Hand::All_Output(int n){
    
    int value;
    
    value = get_value(cards_1[r+n]);
    
    return value;
  
}

Card Hand::Place(Card card) {
    
    //keep track of number of cards in hand
    num_of_cards = num_of_cards + 1;
    
    cards_1[s] = card;
    
    s++;
    
    return card;

}

void new_line() {
    
    using namespace std;
    
    char symbol;
    
    do {  
        cin.get(symbol);
    } while (symbol != '\n');
}

int Hand::count_ace(int i) {
    
    if ((ace > 0) && (i > 21)) {
        
        while((ace > 0) && (i > 21)){
            i = i - 10;
            ace--;
            
        }
        return i;
    }
    
    else return i; 
}

char istwentyone(int x) {
    
    char ans;
    
    //congratulates winner
    if (x == 21) {
        cout << "CONGRATULATIONS!! It's a BlackJack " << endl;
         ans = 'N';
    }
    //gets and returns answer to continue playing
    else {
         cout << "Can I draw another card for you now? (Yes/No) ";
         cin >> ans;
         new_line();
         cout << endl;
         
    }
    return ans;
    
}


void getresult(int dealer_total, int hand_value) {
    
      //if both get 21, then tie goes to dealer
    if ((dealer_total == 21) && ((hand_value >= 21) || (hand_value <= 21))) { 
        cout << "Dealer Wins!!" << endl;     
        if(hand_value == 21){
        cout << "Tie goes to the Dealer!! Since both You and the Dealer have 21!!" << endl;}    
    }
    
    else if ((hand_value == 21) && ((dealer_total > 21) || (dealer_total < 21))){
        cout << "Player Wins!!" << endl;
    }
    
    //if player busted, and dealer's hand is lower than 21, dealer wins
    else if((hand_value > 21) && (dealer_total < 21)){
        cout << "Dealer Wins!!" << endl;

    } 
    
    //if dealer busted, and player's hand is lower than 21, player wins
    else if ((hand_value < 21) && (dealer_total > 21)){
        cout << "Dealer has Busted!! You won!!" << endl;
       
    }
    
    //if both busted, then tie goes to dealer
    else if ((hand_value > 21) && (dealer_total > 21)){
        cout << "Both Player and the Dealer Busted and Tie Goes to the Dealer!" << endl;
       
    }
    
    //checks values when both dealer and player's hand is under 21
    else {
        if ((21 - hand_value) < (21 - dealer_total)) {
            cout << "Player Wins!!" << endl;
        }
        else if ((21 - dealer_total) < (21-hand_value)) {
            cout << "Dealer Wins!!" << endl;
        }
        else {
            cout << "Both Player and the Dealer tied! And Tie Goes to the Dealer!" << endl;
       
        }
    }
}
