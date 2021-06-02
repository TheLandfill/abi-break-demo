#include <unordered_map>
#define ABI_BREAK
#include "util.h"
#include "simple_string.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

#define print_class_member(X, Y)  std::cout << std::left << std::setw(25) << std::setfill(' ') << "Offset for " #Y ": " << std::dec << (unsigned long long)((char *)&(X.Y) - (char *)&X) << "\n";
#define print_output(X, Y) std::cout << std::left << std::setw(16) << std::setfill(' ') << #Y ":" << std::setfill('0') << std::setw(sizeof(X.Y)) << std::right << std::hex << X.Y << "\n";

#ifdef WIN32
#include <windows.h>
#define SETUP_ANSI_TERMINAL setup_ansi_terminal();
void setup_ansi_terminal() {
	DWORD l_mode;
	HANDLE hstd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hstd == INVALID_HANDLE_VALUE) {
		MDXX_warn("Won't be able to display ANSI terminal characters.\n");
		return;
	}
	GetConsoleMode(hstd, &l_mode);
	SetConsoleMode(hstd, l_mode | DISABLE_NEWLINE_AUTO_RETURN | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else
#define SETUP_ANSI_TERMINAL
#endif

void no_abi_break();

void abi_break() {
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
		CLASS_ELEMENT(str, more_added_data)
	};
	std::cout << "Address of str: " << (void*)&str << "\n";
	std::cout << "Size of Simple String according to header:         " << std::dec << sizeof(Simple_String) << "\n";
	std::cout << "Size of Simple String according to shared library: " << std::dec << Simple_String::get_size() << "\n";
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

	str.more_added_data = 0xffffffff;
	std::cout << "more_added_data:  ";
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
	std::cout << "What data should be:             " << static_cast<void *>(example) << "\n";

	std::cout << "New Layout:       ";
	print_class_layout(&str, updated_addr);
	std::cout << "\n";
	std::cout << "Old Layout:       ";
	print_class_layout(&str, old_addr);
	std::cout << "\n";
	str.data = example;
	std::cout << "str.data:        ";
	print_binary_layout(&str, original, last);
	str.get_data() = example;
	std::cout << "get_data():      ";
	print_binary_layout(&str, original, last);

	std::cout << "\x1b[38;2;255;255;255m";
}

int main() {
	SETUP_ANSI_TERMINAL
	std::cout << COLOR_RESET;
	const char * barrier_str = "____________________________________________________________________________________________________\n";
	std::cout << barrier_str;
	std::cout << "\n";
	std::cout << "                                          Without ABI breaks\n";
	std::cout << barrier_str;
	std::cout << "\n";
	no_abi_break();
	std::cout << barrier_str;
	std::cout << "\n\n\n";
	std::cout << barrier_str;
	std::cout << "\n";
	std::cout << "                                            With ABI breaks\n";
	std::cout << barrier_str;
	std::cout << "\n";
	abi_break();
	std::cout << barrier_str;
	std::cout << "\n\n\n";
	std::cout << "The only reason the program didn't crash was because I reset the `data` the\ndestructor was looking for.\n";
	return 0;
}
