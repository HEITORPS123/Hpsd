#ifndef GUARD_TUPLA_H
#define GUARD_TUPLA_H

#include <string>

class Tupla{
    public:
        Tupla(std::string id);
        int Frequencia();
        std::string Get_id();
        void operator++();
        Tupla operator*();
    
    private:
        std::string docid_;
        int freq_;
};

#endif