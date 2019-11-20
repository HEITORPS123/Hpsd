#include "tupla.h"

using std::string;
using std::vector;
using std::cout;

Tupla::Tupla(string id)
{
    docid_ = id;
    freq_ = 1;
}

int Tupla::Frequencia()
{ 
    return freq_;
}

string Tupla::Get_id()
{
    return docid_; 
}

Tupla Tupla::operator*(){
    return *this;
}

void Tupla::operator++(){
    freq_++;
}


