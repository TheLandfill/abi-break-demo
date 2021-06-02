#include "simple_string.h"
#include <iostream>
#include <cstring>
#include <iomanip>

Simple_String::Simple_String(char * str) :
	data(str), length(strlen(str)) {}

Simple_String::~Simple_String() {
	delete[] data;
}

char *& Simple_String::get_data() {
	return data;
}

unsigned int Simple_String::get_size() {
	return sizeof(Simple_String);
}

uint32_t& Simple_String::get_length() {
	return length;
}

const uint32_t& Simple_String::get_added_data() {
	return added_data;
}

void Simple_String::print_data_layout() {
	void * all_data[] = {
		&data,
		&test,
		&test2,
		&length,
	};
	const char * all_names[] = {
		"data",
		"test",
		"test2",
		"length",
	};
	for (size_t i = 0; i < sizeof(all_data) / sizeof(void *); i++) {
		std::cout << "Offset for " << all_names[i] << ": " << &("            "[0]) + strlen(all_names[i]) << (unsigned long long)((char *)all_data[i] - (char *)this) << "\n";
	}
}

uint16_t& Simple_String::get_test() {
	return test;
}

uint16_t& Simple_String::get_test2() {
	return test2;
}
