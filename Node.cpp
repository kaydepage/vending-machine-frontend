#include "Node.h"

Node::Node(): data {new Stock()}{
};
Node::~Node(){
    delete data;
};