//
// Created by jmmar on 12/05/2024.
//

#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>


class Property {
public:
    explicit Property(std::string name);
    std::string getName();

private:
    std::string name_m;
};



#endif //PROPERTY_H
