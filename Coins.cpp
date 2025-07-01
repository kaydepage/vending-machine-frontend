#include "Coins.h"

// Code adapted from lecture red7 lecture material: DeckArray.

Coins::Coins(){
    denoms = NUM_DENOMINATIONS;
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
        coins[i] = nullptr;
    }
}

Coins::Coins(Coins& other) {
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
      coins[i] = nullptr;
    }
    denoms = other.denoms;
    for (int i = 0; i < denoms; ++i) {
        coins[i] = new Coin(*other.coins[i]);
    }    
}

Coins::~Coins() {
    clear();
}

int Coins::size() {
    return denoms;
}

Coin* Coins::get(int index){
    Coin* coin = nullptr;
    if (index >=0 && index < denoms) {
        coin = coins[index];
    }
    return coin;
}

void Coins::add(Coin* coin, int index){
    if (coin != nullptr && index >= 0 && index < denoms) {
        coins[index] = coin;
    }
}

void Coins::clear(){
    for (int i = 0; i < denoms; ++i) {
      delete coins[i];
      coins[i] = nullptr;
   }
}

void Coins::resetCoins(){
    for (int i = 0; i < denoms; ++i) {
      coins[i]->setCount(DEFAULT_COIN_COUNT);
   }
}
