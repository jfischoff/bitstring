#ifndef INVALIDATOR_H
#define INVALIDATOR_H

#include "GeneratorContext.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
using namespace std;

#if INVALIDATOR == TRUE
#define test_return(x) return Invalidate(x)
#else
#define test_return(x) return x
#endif

bool ___invalidate___ = true;

template<class T>
T Invalidate(T t) {
    assert(0);
    return t;
}

template<class T>
T* Invalidate(T* t) {
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_int(0, 100);   
    } else {
        return t;
    }
}

template<>
char Invalidate(char t){
    if(___invalidate___) {
        GeneratorContext context;
        return context.gen_char();
    } else {
        return t;
    }
}

template<>
unsigned char Invalidate(unsigned char t){
    if(___invalidate___) {
        GeneratorContext context;
        return context.gen_unsigned_char();
    } else {
        return t;
    }
}

template<>
bool Invalidate(bool t){
    if(___invalidate___) {
        GeneratorContext context;
        return context.gen_int() % 2 == 0;
    } else {
        return t;
    }
}


template <>
int Invalidate(int t){
    if(___invalidate___) {
        GeneratorContext context;
        int return_value = t + context.gen_int();
        //cout << return_value << "\n";
        return return_value;
    } else {
        return t;
    }
}

unsigned int Invalidate(unsigned int t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_int();
    } else {
        return t;
    }
}

template<>
float Invalidate(float t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_float();
    } else {
        return t;
    }
}

template<>
double Invalidate(double t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_double();
    } else {
        return t;
    }
}

template<>
long Invalidate(long t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_long();
    } else {
        return t;
    }
}

template<>
long long Invalidate(long long t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_long();
    } else {
        return t;
    }
}

template<>
unsigned long long Invalidate(unsigned long long t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_long();
    } else {
        return t;
    }
}

template<>
unsigned long Invalidate(unsigned long t){
    if(___invalidate___) {
        GeneratorContext context;
        return t + context.gen_long();
    } else {
        return t;
    }
}

template<>
const char* Invalidate(const char* t)
{
    if(___invalidate___) {
        GeneratorContext context;
        return "Bad String!";
    } else {
        return t;
    }
    
}

#endif //INVALIDATOR_H