#include "simple_string.h"
#include <iostream>
#include <cstring>

Simple_String::Simple_String(char * str) :
	length(strlen(str)), data(str) {}

Simple_String::~Simple_String() {
	delete[] data;
}

char * Simple_String::get_data() {
	return data;
}

unsigned int Simple_String::get_size() {
	return sizeof(Simple_String);
}

uint32_t Simple_String::get_length() {
	return length;
}

void Simple_String::print_data_layout() {
	void * all_data[] = {
		&length,
		&data
	};
	const char * all_names[] = {
		"length",
		"data"
	};
	for (size_t i = 0; i < sizeof(all_data) / sizeof(void *); i++) {
		std::cout << all_names[i] << " offset: +" << (char *)all_data[i] - (char *)this << "\n";
	}
}
