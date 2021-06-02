#define ABI_BREAK
#include "simple_string.h"
#include <cstring>
#include <iostream>
#include <iomanip>

#define print_class_member(X, Y)  std::cout << "Offset for " << #Y << ": +" << (char *)&(X.Y) - (char *)&X << "\n";

int main() {
	char * example = new char[66];
	strncpy(example, "This is just a short example.", 66);
	Simple_String str{example};
	std::cout << "Where get_data() thinks data is: " << std::hex << static_cast<void*>(str.get_data()) << "\n";
	std::cout << "Where data actually is: " << std::hex << static_cast<void *>(example) << "\n";
	std::cout << "Size of Simple String according to header: " << sizeof(Simple_String) << "\n";
	std::cout << "Size of Simple String according to shared library: " << Simple_String::get_size() << "\n";
	str.print_data_layout();
	print_class_member(str, test);
	print_class_member(str, length);
	print_class_member(str, test2);
	print_class_member(str, data);
	str.test = 7;
	str.length = 1;
	str.test2 = -1;
	std::cout << "test: " << str.test << "\n";
	std::cout << "length: " << str.length << "\n";
	std::cout << "length according to get_length(): " << str.get_length() << "\n";
	std::cout << "test2: " << str.test2 << "\n";
	return 0;
}
