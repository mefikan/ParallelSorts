#ifndef PARALLELSORTS_ELEMENT_H
#define PARALLELSORTS_ELEMENT_H

#include <stdio.h>
#include <time.h>
#include <string>

class Element {
    std::string data;
public:
    void num_generate();
    unsigned int key;
    void setKey(unsigned int x);
    unsigned int getKey();
    Element(unsigned int key_);
    Element();
    bool operator>(Element &el) {return this->getKey() > el.getKey();};
    bool operator<(Element &el) {return this->getKey() < el.getKey();};
};


#endif //PARALLELSORTS_ELEMENT_H
