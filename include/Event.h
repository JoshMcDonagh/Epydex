//
// Created by jmmar on 12/05/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include <string>


class Event {
public:
    explicit Event(std::string name);
    std::string getName();

private:
    std::string name_m;
};



#endif //EVENT_H
