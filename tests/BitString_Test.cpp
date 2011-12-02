#define INVALIDATOR FALSE
//#include "../src/Invalidator.hpp"
#include "../src/BitString.h"
#include "../src/GeneratorContext.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

extern bool ___invalidate___;

bool test_long_write_read(unsigned long long value, int bits, BitString& bitString)
{
    bool result = true;
    bitString.write_bits_from_long(bits, value);
    bitString.rewind(bits);
    unsigned long read_value = bitString.read_bits_as_long(bits);
    
    unsigned long xored = read_value ^ value;
   
    if(value != read_value) {
        cout << "\nFailed write_bits_from_long with value " << value << 
        " and read_value " << 
              read_value << " bits " << bits << " diff " << xored << endl;
         bitString.write_bits_from_long(64, read_value);
    
         result = false;
    }
    
    return result;
}

int main(int argc, const char** argv, char **envp, char **apple) {
    srand ( time(NULL) );
    ___invalidate___ = false;
    //unit tests
    BitString bitString0;
    GeneratorContext context;
   /*
    
    if(!bitString0.is_valid())
        cout << "is_valid failed\n";
    
    if(bitString0.get_bit_offset() != 0)
        cout << "get_bit_offset failed\n";
        
    if(bitString0.get_byte_index() != 0)
        cout << "get_byte_index failed\n";
        
    bitString0.set_byte(1);
    if(bitString0.peek_byte() != 1)
        cout << "set_byte / peek_byte failed\n";
        
    if(bitString0.is_cleared())
        cout << "is_cleared failed\n";
        
    bitString0.clear();
    
    if(bitString0.is_cleared() == false)
        cout << "clear failed!\n";
        
    bitString0.write_bit(true);
    bitString0.reset_index();
    if(bitString0.peek_bit() != true)
        cout << "set_byte / peek_bit failed\n";
        
    if(bitString0.read_bit() != true)
        cout << "set_byte / read_bit failed\n";
      
    
    bitString0.clear();
    
    
    int bits = 17;
    int value = 70000;
    int read_value = 0;
    
    
    bitString0.write_bits_from_int(bits, value);
    bitString0.rewind(bits);
    read_value = bitString0.read_bits_as_int(bits);
    
    if(read_value != value)
        cout << "write_bits/read_bits failed\n";

    


        
    bitString0.gen_valid(context);

    //need enough bits for the test
    if(bitString0.bits_available() > bits + 1) {
        cout << "Test Started\n";
        bitString0.write_bit(false);
        bitString0.rewind(1);
        if(bitString0.peek_bit() != false)
            cout << "set_byte / peek_bit failed\n";
        
        if(bitString0.read_bit() != false)
            cout << "set_byte / read_bit failed\n";

        
        bitString0.set_bit_index(4);
        
        bitString0.write_bits_from_int(bits, value);
        bitString0.rewind(bits);
        read_value = bitString0.read_bits_as_int(bits);
    
        if(read_value != value)
            cout << "write_bits/read_bits failed after gen_valid with value = " << value << " and read_value " << read_value << "\n";
    }

*/
    

    BitString bitString;
    bitString.gen_valid(context);
    
    test_long_write_read(16683730362329794560ULL, 64, bitString);
    
    
    for(int i = 0; i < 1000; i++) {
        cout << "*";
        
        bitString.gen_valid(context);
        //BitString original_bitstring(bitString);
        
        //add a byte and then make sure that index is correct
        
        int available_bits = bitString.bits_available();
        
        if(available_bits > 0 && false) {
            
            int max_int_value = min(available_bits, 32);
        
            //test that all the functions are invalid
        
            int bits  = context.gen_int(1, max_int_value);
            unsigned int value = context.gen_int(0); 
            //clear the other bits
            value = value << (32 - bits);
            value = value >> (32 - bits);
        
            bitString.write_bits_from_int(bits, value);
            bitString.rewind(bits);
            unsigned int read_value = bitString.read_bits_as_int(bits);
           
            if(value != read_value) {
                cout << "\nFailed write_bits_from_int with value " << value << " and read_value " 
                     << read_value << endl;
            }
        }
        
        
        if(available_bits > 0) {
            int max_int_value = min(available_bits, 64);
        
            //test that all the functions are invalid
        
            int bits  = context.gen_int(1, max_int_value);
            unsigned long long value = context.gen_long(); 
            //clear the other bits
            value = value << (64 - bits);
            value = value >> (64 - bits);
        
            test_long_write_read(value, bits, bitString);
        }
        
        bitString.gen_valid(context);
        
        if(bitString.bits_available() > 32 && false) {
            int int0 = context.gen_int();
            bitString.write_as_int(int0);
            bitString.rewind(32);
            int read_int0 = bitString.read_as_int();
            if(int0 != read_int0) {
                cout << "\nFailed write_as_int with int0 " << int0 << " and read_as_int " 
                     << read_int0 << endl;
            }            
        }
        
        bitString.gen_valid(context);
        
        if(bitString.bits_available() > 8 && false) {
            unsigned char byte0 = context.gen_char();
            bitString.write_byte(byte0);
            bitString.rewind(8);
            unsigned char read_byte0 = bitString.read_byte();
            if(read_byte0 != byte0) {
                cout << "\nFailed write_byte with byte0 " << byte0 << " and read_byte " 
                     << read_byte0 << endl;
            }
        
        }
        
        bitString.gen_valid(context);
        
        if(bitString.bits_available() > 32) {
            float float0 = context.gen_float();
            bitString.write_as_float(float0);
            bitString.rewind(32);
            float read_float0 = bitString.read_as_float();
            if(read_float0 != float0) {
                cout << "\nFailed write_float with float0 " << float0 << " and read_float " 
                     << read_float0 << endl;
            }
            
        }
        
        bitString.gen_valid(context);
        if(bitString.bits_available() > 64) {
            double double0 = context.gen_double();
            bitString.write_as_double(double0);
            bitString.rewind(64);
            double read_double0 = bitString.read_as_double();
            if(read_double0 != double0) {
                cout << "\nFailed write_double with double0 " << double0 << " and read_double0 " 
                     << read_double0 << endl;
            }
        }
        
        bitString.gen_valid(context);
        if(bitString.bits_available() > 64) {
            long long0 = context.gen_long();
            bitString.write_as_long(long0);
            bitString.rewind(64);
            long read_long0 = bitString.read_as_long();
            if(read_long0 != long0) {
                cout << "\nFailed write_long with long0 " << long0 << " and read_long0 " 
                     << read_long0 << endl;
            }
        }
    
        
        bitString.gen_valid(context);
        if(bitString.bytes_available() > sizeof(1)) {
        
            int string_count = context.gen_int(2, bitString.bytes_available());
            //cout << "string count " << string_count << "\n";
            //int string_count = 5;
        
            char* buffer = (char*)malloc(string_count);
            for(int index = 0; index < string_count; index++) {
                buffer[index] = 0;
            }
            //cout << "buffer " << buffer << "\n";        
            context.gen_string(buffer, string_count);
            //cout << "buffer " << buffer << "\n";
            bitString.write_string(buffer);
            bitString.rewind(string_count * 8);
            char* read_string = (char*)malloc(string_count); 
            bitString.read_string(read_string);

            if(strncmp(read_string, buffer, string_count)) {
                cout << "Failed write_string with buffer " << buffer << " and read_string " 
                     << read_string << endl;
            }
        
            free(buffer);
            free(read_string);
        }
        
        
    }



    return 0;
}






