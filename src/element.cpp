#include "element.h"

Element::Element(unsigned int key_)
    : key(key_)
{
}
Element::Element()
{
    srand(time(NULL));
    key = rand()%99 + 1;
    /*std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);*/
}
void Element::setKey(unsigned int x)
{
    key = x;
}
unsigned int Element::getKey()
{
    return this->key;
}



