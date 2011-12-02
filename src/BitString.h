class GeneratorContext;

class BitString
{
	public:
        BitString();
        BitString(const BitString& bitString);
        BitString& operator=(const BitString& other);
        void copy(const BitString& other);
        
        void clear();
        
        bool failed();
        
        unsigned int read_bits_as_int(int bit_count);
        void write_bits_from_int(int bit_count, unsigned int value);
        
        unsigned long long read_bits_as_long(int bit_count);
        void write_bits_from_long(int bit_count, unsigned long long value);

        bool read_bit();
        void write_bit(bool bit);
        
        unsigned char read_byte();
        void write_byte(unsigned char byte);
        
        float read_as_float();
        void write_as_float(float value);
        
        double read_as_double();
        void write_as_double(double value);
        
        long long read_as_long();
        void write_as_long(long long value);
        
        int read_as_int();
        void write_as_int(int value);
        
        void read_string(char* buffer);
        void write_string(const char* value);
        
        bool peek_bit();
        unsigned char peek_byte();
        
        int get_byte_index();
        int get_bit_offset();
        
        int bits_available();
        int bytes_available();
        
        void increment_to_byte_boundary();
        
        unsigned char* next_byte_pointer();
        unsigned char* get_byte_pointer();
        
        void set_byte(unsigned char byte);
        
        void set_byte_at(unsigned char byte, int index);
        unsigned char get_byte_at(int index);
        
        int strnlen(const char* value, int max_length);
        
        void gen_valid(GeneratorContext& context);
        void gen_invalid(GeneratorContext& context);
        bool is_valid();
        
        bool is_cleared();
        
        void reset_index(); 
        
        void rewind(int bits);
        
        bool test_bit(unsigned int value, int index);
        unsigned int set_bit(unsigned int value, int index, bool set_value);

        bool test_bit(unsigned char value, int index);
        unsigned char set_bit(unsigned char value, int index, bool set_value);
        
        bool test_bit_long(unsigned long long value, int index);
        unsigned long long set_bit_long(unsigned long long value, int index, bool set_value);
        
        int get_bit_index();
        void set_bit_index(int bit_index);
        
        void increment_index();
        
        
	    
	private:
        bool m_Failed;
        static const int MAX_BYTE_COUNT = 1024;
        int m_BitIndex;
        
        unsigned char m_Bytes[MAX_BYTE_COUNT];
};