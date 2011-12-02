#include "BitString.h"
#include <string.h>
#include "Invalidator.hpp"
#include "GeneratorContext.h"

BitString::BitString() {
    clear();
}

void BitString::clear(){
    m_BitIndex = 0;
    m_Failed   = false;      

    for(int i = 0; i < MAX_BYTE_COUNT; i++) {
        m_Bytes[i] = 0;
    }
}

bool BitString::is_cleared() {
    bool result = true;
    for(int i = 0; i < MAX_BYTE_COUNT; i++) {
        result &= m_Bytes[i] == 0;
    }
    
    return result;
}

void BitString::reset_index()
{
    m_BitIndex = 0;
}

BitString::BitString(const BitString& other) {
    copy(other);
}

BitString& BitString::operator=(const BitString& other) {
    copy(other);
    return *this;
}

void BitString::copy(const BitString& other) {
    m_BitIndex = other.m_BitIndex;
    m_Failed   = other.m_Failed;
    memcpy(m_Bytes, other.m_Bytes, MAX_BYTE_COUNT);
}

unsigned char BitString::peek_byte() {
    int byte_index = get_byte_index();
    test_return(m_Bytes[byte_index]);    
}

bool BitString::peek_bit() {
    unsigned char byte = peek_byte();
    int bit_offset = get_bit_offset();
    test_return((byte >> bit_offset) & 1) ; 
}

bool BitString::read_bit() {
    bool return_value = peek_bit();
    increment_index();
    test_return(return_value);
}

void BitString::set_byte(unsigned char byte) {
    int byte_index = get_byte_index();
    m_Bytes[byte_index] = Invalidate(byte);
}

void BitString::write_bit(bool bit) {
    unsigned char byte = peek_byte();
    int bit_offset = get_bit_offset();
    unsigned char result_byte = set_bit(byte, bit_offset, Invalidate(bit)); 
    set_byte(result_byte);
    increment_index();
}

int BitString::get_byte_index() {
    return m_BitIndex / 8;
}

int BitString::get_bit_offset() {
    return m_BitIndex % 8;
}

unsigned int BitString::read_bits_as_int(int bit_count) {
    assert(bit_count > 0);
    unsigned int return_value = 0;
    
    for(int index = 0; index < bit_count; index++) {
        bool bit = read_bit();
        return_value |= (bit << index); 
    }
    
    test_return(return_value);
}

void BitString::write_bits_from_int(int bit_count, unsigned int value) {
    assert(bit_count > 0);
    for(int index = 0; index < bit_count; index++) {
        bool bit = test_bit(value, index); 

        write_bit(bit);
    }

}

unsigned long long BitString::read_bits_as_long(int bit_count) {
    assert(bit_count > 0);
    unsigned long long return_value = 0;

    for(unsigned long long index = 0; index < bit_count; index++) {
        bool bit = read_bit();
        unsigned long long long_bit = bit;
        unsigned long long mask = bit << index;

        return_value = set_bit_long(return_value, index, bit);
    }
    
    return return_value;
}

void BitString::write_bits_from_long(int bit_count, unsigned long long value){
    assert(bit_count > 0);

    for(int index = 0; index < bit_count; index++) {
        bool bit = test_bit_long(value, index); 
        write_bit(bit);
    }

}

unsigned char BitString::read_byte() {
    unsigned char return_value = read_bits_as_int(8);
    test_return(return_value);
}

void BitString::write_byte(unsigned char byte) {
    write_bits_from_int(8, (unsigned int)byte);
}

float BitString::read_as_float() {
    int result = read_as_int();
    test_return(*(float*)&result);
}

void BitString::write_as_float(float value) {
    value = Invalidate(value);
    write_as_int(*(int*)&value);
}
 
void BitString::write_as_int(int value) {
    write_bits_from_int(32, Invalidate(value));
}

void BitString::write_as_double(double value) {
    value = Invalidate(value);

    long long long_value = *(long long*)&value;

    write_as_long(long_value);
}

void BitString::write_as_long(long long value) {
    write_bits_from_long(64, Invalidate(*((unsigned long long*)&value)));
}

double BitString::read_as_double() {
    long long value = read_as_long();

    double double_value = *(double*)&value;

    test_return(double_value);
}

long long BitString::read_as_long() { 
    unsigned long long result = read_bits_as_long(64);
    test_return(*(long long*)&result);
}

int BitString::read_as_int() {
    test_return(read_bits_as_int(32));
}

void BitString::read_string(char* buffer) {

    unsigned char current_byte = -1;
    int byte_index = 0;
    while(current_byte != 0) {

        current_byte = read_byte();

        char char_byte = *(char*)&current_byte;

        buffer[byte_index] = Invalidate(char_byte);
        byte_index++;
    }
}

int BitString::bits_available() {
    return (8 * MAX_BYTE_COUNT) - Invalidate(m_BitIndex);
}

int BitString::bytes_available() {
    test_return(bits_available() / 8);
}

void BitString::increment_to_byte_boundary() {
    m_BitIndex = ((Invalidate(m_BitIndex) / 8) + 1) * 8;
    assert(m_BitIndex < (MAX_BYTE_COUNT * 8));
}

unsigned char* BitString::get_byte_pointer() {
    test_return(&m_Bytes[get_byte_index()]);
}

unsigned char* BitString::next_byte_pointer() {
    increment_to_byte_boundary();
    test_return(get_byte_pointer());
}

int BitString::strnlen(const char* value, int max_length) {
    int length = max_length;
    for(int length = 0; length < max_length; length++) {
        if(value[length] == 0) return length;
    }
    
    test_return(length);
}

void BitString::write_string(const char* value) {
    int too_much_space = bytes_available() + 1;
    int length = strnlen(value, too_much_space);
    
    if(length == too_much_space) {
        m_Failed = true;
        return; 
    }
    
    for(int i = 0; i < length; i++) {
        write_byte(*(unsigned char*)&value[i]);
    }
    write_byte(0);
}

void BitString::gen_valid(GeneratorContext& context) {
    //generator a list of random bytes
    context.gen_bytes((char*)m_Bytes, MAX_BYTE_COUNT);
    //generator a random int for how many bits are used
    m_BitIndex = context.gen_int(0, (MAX_BYTE_COUNT * 8) - 1);
    m_Failed = true;
}

void BitString::gen_invalid(GeneratorContext& context) {
    context.gen_bytes((char*)m_Bytes, MAX_BYTE_COUNT);
    m_BitIndex = context.gen_int(MAX_BYTE_COUNT * 8);   
}

bool BitString::is_valid() {
    return m_BitIndex <= 8 * MAX_BYTE_COUNT && m_Failed == false;
}

void BitString::set_byte_at(unsigned char byte, int index) {
    m_Bytes[index] = byte;
}

unsigned char BitString::get_byte_at(int index) {
    return m_Bytes[index];
}

void BitString::rewind(int bits) {
    m_BitIndex -= bits;
    m_BitIndex = max(m_BitIndex, 0);
}


bool BitString::test_bit(unsigned int value, int index)
{
    return (value >> index) & 0x1;
}

unsigned int BitString::set_bit(unsigned int value, int index, bool set_value)
{
    unsigned int return_value = 0;
    
    if(set_value) {
        return_value = value | (0x1 << index);
    } else {
        return_value = value & (~(0x1 << index));
    }
    
    return return_value;
}

bool BitString::test_bit(unsigned char value, int index)
{
    return (value >> index) & 0x1;
}

unsigned char BitString::set_bit(unsigned char value, int index, bool set_value)
{
    unsigned char return_value = 0;
    
    if(set_value) {
        return_value = value | (0x1 << index);
    } else {
        return_value = value & (~(0x1 << index));
    }
    
    return return_value;
}

bool BitString::test_bit_long(unsigned long long value, int index)
{
    return (value >> index) & 0x1;
}

unsigned long long BitString::set_bit_long(unsigned long long value, int index, bool set_value)
{
    unsigned int* first_value_section = (unsigned int*)&value;
    unsigned int first_part = *first_value_section;

    unsigned int second_part = *(first_value_section + 1);
 
    if(index < 32){
        first_part = set_bit(first_part, index, set_value);
    } else {
        second_part = set_bit(second_part, index - 32, set_value);        
    }
    
    unsigned long long result = first_part;
    unsigned int* first_section = (unsigned int*)&result;
    unsigned int* next_part = first_section + 1;
    *next_part = second_part;
    
    return result;
}

void BitString::set_bit_index(int bit_index) {
    m_BitIndex = bit_index;
}

int BitString::get_bit_index() {
    return m_BitIndex;
}

void BitString::increment_index() {
    m_BitIndex++;
}