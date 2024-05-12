//
// Created by jmmar on 09/05/2024.
//

#ifndef AGENTS_H
#define AGENTS_H
#include <string>
#include <variant>


class Agents {
    using VariantType = std::variant<int, double, std::string, bool>;
public:
    Agents();
    void runTick();
};



#endif //AGENTS_H
