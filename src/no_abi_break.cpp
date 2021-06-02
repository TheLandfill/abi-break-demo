#include "util.h"
#include "simple_string.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

#define print_class_member(X, Y)  std::cout << std::left << std::setw(25) << std::setfill(' ') << "Offset for " #Y ": " << (char *)&(X.Y) - (char *)&X << "\n";
#define print_output(X, Y) std::cout << std::left << std::setw(16) << std::setfill(' ') << #Y ":" << std::setfill('0') << std::setw(sizeof(X.Y) * 2) << std::right << std::hex << X.Y << "\n";

void no_abi_break() {
	char * example = new char[66];
	strncpy(example, "This is just a short example.", 66);
	Simple_String str{example};
	std::unordered_map<uint8_t*, Layout_Spec> old_addr {
		OLD_CLASS_ELEMENT(str, data),
		OLD_CLASS_ELEMENT(str, test),
		OLD_CLASS_ELEMENT(str, length),
		OLD_CLASS_ELEMENT(str, test2),
		OLD_CLASS_ELEMENT(str, added_data),
	};
	std::unordered_map<uint8_t*, Layout_Spec> updated_addr {
		CLASS_ELEMENT(str, data),
		CLASS_ELEMENT(str, test),
		CLASS_ELEMENT(str, length),
		CLASS_ELEMENT(str, test2),
		CLASS_ELEMENT(str, added_data),
	};
	std::cout << "Address of str: " << (void*)&str << "\n";
	std::cout << "Size of Simple String according to header:         " << sizeof(Simple_String) << "\n";
	std::cout << "Size of Simple String according to shared library: " << Simple_String::get_size() << "\n";
	std::cout << "\n";
	str.print_data_layout();
	std::cout << "\n";
	print_class_member(str, data);
	print_class_member(str, test);
	print_class_member(str, length);
	print_class_member(str, test2);
	std::cout << "\n";
	print_output(str, test);
	print_output(str, get_test())
	print_output(str, length);
	print_output(str, get_length())
	print_output(str, test2);
	print_output(str, get_test2())
	std::cout << "\n";

	std::vector<uint8_t> original;
	std::vector<uint8_t> last;
	std::cout << "New Layout:       ";
	print_class_layout(&str, updated_addr);
	std::cout << "\n";
	std::cout << "Old Layout:       ";
	print_class_layout(&str, old_addr);
	std::cout << "\n";
	std::cout << "Original:         ";
	print_binary_layout(&str, original, last);

	str.test = 0x1111;
	std::cout << "str.test:         ";
	print_binary_layout(&str, original, last);

	str.get_test() = 0x1212;
	std::cout << "get_test():       ";
	print_binary_layout(&str, original, last);

	str.length = 0x22222222;
	std::cout << "str.length:       ";
	print_binary_layout(&str, original, last);

	str.get_length() = 0x23232323;
	std::cout << "str.length:       ";
	print_binary_layout(&str, original, last);

	str.test2 = 0x3333;
	std::cout << "str.test2:        ";
	print_binary_layout(&str, original, last);

	str.get_test2() = 0x6969;
	std::cout << "get_test2():      ";
	print_binary_layout(&str, original, last);

	std::cout << "\n";
	print_output(str, test);
	print_output(str, get_test())
	print_output(str, length);
	print_output(str, get_length())
	print_output(str, test2);
	print_output(str, get_test2())
	std::cout << "Where get_data() thinks data is: " << static_cast<void *>(str.get_data()) << "\n";
	std::cout << "Where data actually is:          " << static_cast<void *>(example) << "\n";
}
