#pragma once
#include <cstdint>

class Simple_String {
public:
	Simple_String(char * str);
	~Simple_String();
	char *& get_data();
	static unsigned int get_size();
	uint32_t& get_length();
	void print_data_layout();
	uint16_t& get_test();
	uint16_t& get_test2();
	const uint32_t& get_added_data();
public:
#ifdef ABI_BREAK
	uint16_t test;
	uint32_t length;
	char * data;
	const uint32_t added_data;
	uint16_t test2;
	uint32_t more_added_data;
#else
	char * data = nullptr;
	uint16_t test = 0xaaaa;
	uint32_t length = 0xbbbbbbbb;
	uint16_t test2 = 0xeeee;
	const uint32_t added_data = 0xcccccccc;
#endif
};
