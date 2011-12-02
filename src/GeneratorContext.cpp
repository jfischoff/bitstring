#include "GeneratorContext.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

GeneratorContext::GeneratorContext(){
    
}

GeneratorContext::GeneratorContext(const GeneratorContext& other){
    
}

GeneratorContext& GeneratorContext::operator=(const GeneratorContext& other){
    copy(other);
    return *this;
}

void GeneratorContext::copy(const GeneratorContext& other){
    
}

int GeneratorContext::gen_int(int start, int end){
    double d_start = start;
    double d_end = end;
    double percent = (double)rand() / ((double)RAND_MAX);
    return (int)((percent * (d_end - d_start)) + d_start);
}

double GeneratorContext::gen_double(double start, double end){
    double percent = (double)rand() / ((double)RAND_MAX);
    return (percent * (end - start)) + start;
}

char GeneratorContext::gen_char() {
    return (char)gen_int(-128, 127);
}

unsigned char GeneratorContext::gen_unsigned_char() {
    return (unsigned char)gen_int(0, 255);
}

void GeneratorContext::gen_bytes(char* bytes, int length) {
    for(int i = 0; i < length; i++) {
        bytes[i] = gen_char();
    }
}

unsigned char GeneratorContext::gen_non_null_char() {
    return (unsigned char)gen_int(1, 255);
}

void GeneratorContext::gen_string(char* bytes, int length) {
    for(int i = 0; i < length - 1 ; i++) {
        bytes[i] = gen_non_null_char();
    }
    
    bytes[length - 1] = '\0';
}

float GeneratorContext::gen_float(float start, float end) {
    double percent = (double)rand() / ((double)RAND_MAX);
    return (percent * (end - start)) + start;
}

long GeneratorContext::gen_long(long start, long end) {
    double percent = (double)rand() / ((double)RAND_MAX);
    //cout << "start "<< start << "\n";
    //cout << "end " << end << "\n";
    //cout << "percent " << percent << "\n";
    unsigned long length = end - start;
    double scaled = percent * length;
    return ((long)scaled) + start;
}

//bool GeneratorContext::gen_bool() {
//    return rand() % 2 == 0;
//}