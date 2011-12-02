#ifndef GENERATORCONTEXT_H
#define GENERATORCONTEXT_H

#include <limits.h>
#include <float.h>
#include <stdlib.h>

class GeneratorContext
{
public:
    GeneratorContext();
    GeneratorContext(const GeneratorContext& other);
    GeneratorContext& operator=(const GeneratorContext& other);
    void copy(const GeneratorContext& other);
    
    int gen_int(int start=INT_MIN, int end=INT_MAX);
    double gen_double(double start=__DBL_MIN__, double end=__DBL_MAX__);
    void gen_bytes(char* bytes, int length);
    char gen_char();
    float gen_float(float start=__FLT_MIN__, float end=__FLT_MAX__);
    long  gen_long(long start=LONG_MIN, long end=LONG_MAX);
    bool gen_bool();
    unsigned char gen_unsigned_char();
    unsigned char gen_non_null_char();
    void gen_string(char* bytes, int length);
};

#endif //GENERATORCONTEXT_H