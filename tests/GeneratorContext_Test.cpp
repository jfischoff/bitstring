#include "../src/GeneratorContext.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


int main(int argc, const char** argv, char **envp, char **apple)
{
    srand ( time(NULL) );
    GeneratorContext gen; 
    
    /*cout << gen.gen_int() << endl;
    cout << gen.gen_int(10) << endl;
    cout << gen.gen_int(1, 4) << endl;
    
    cout << gen.gen_double() << endl;
    cout << gen.gen_double(10.0) << endl;
    cout << gen.gen_double(1.0, 4.0) << endl;
    */
    

    return 0;
}