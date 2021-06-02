#pragma once
#include <cstdint>

class Simple_String {
public:
	Simple_String(char * str);
	~Simple_String();
	char * get_data();
	static unsigned int get_size();
	uint32_t get_length();
	void print_data_layout();
public: // I don't want to implement getters and setters for a proof of concept
#ifdef ABI_BREAK
	uint32_t length;
	uint16_t test;
	uint16_t test2;
#else
	uint16_t test;
	uint32_t length;
	uint16_t test2;
#endif
	char * data;
};
