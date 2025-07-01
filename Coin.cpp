#include "Coin.h"
#include <string>

 
Coin::Coin(Denomination _denomination, unsigned _count){
    this->denom = _denomination;
    this->count = _count;
}

Coin::Coin(Coin& other){
    this->denom = other.denom;
    this->count = other.count;
}

Coin::~Coin() {
}

Denomination Coin::getDenom() {
    return denom;
}

void Coin::setDenom(int _denom) {
    if(_denom == 1000) {
        this->denom = TEN_DOLLARS;
    } else if (_denom == 500) {
        this->denom = FIVE_DOLLARS;
    } else if (_denom == 200) {
        this->denom = TWO_DOLLARS;
    } else if (_denom == 100) {
        this->denom = ONE_DOLLAR;
    } else if (_denom == 50) {
        this->denom = FIFTY_CENTS;
    } else if (_denom == 20) {
        this->denom = TWENTY_CENTS;
    } else if (_denom == 10) {
        this->denom = TEN_CENTS;
    } else if (_denom == 5) {
        this->denom = FIVE_CENTS;
    }
}

unsigned Coin::getCount() {
    return count;
}

void Coin::setCount(unsigned _count) {
    this->count = _count;
}

bool Coin::positiveCount(){
    return count > 0;
}