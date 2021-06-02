#pragma once
#include <cstdint>
#include <vector>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <string>

bool is_little_endian();

#define COLOR_RESET "\x1b[38;2;255;255;255m"
#define COLOR_FIRST "\x1b[38;2;128;128;128m"
#define COLOR_CHANGE "\x1b[38;2;255;0;255m"
#define COLOR_DIFFER_ORIGINAL "\x1b[38;2;255;0;0m"
#define COLOR_ORIGINAL_MATCH "\x1b[38;2;128;255;128m"
#define CLASS_ELEMENT(Y, X) { (uint8_t*)&Y.X + is_little_endian() * (sizeof(Y.X) - 1), { #X, sizeof(Y.X) } }
#define OLD_CLASS_ELEMENT(Y, X) { (uint8_t*)&Y.get_##X() + is_little_endian() * (sizeof(Y.get_##X()) - 1), { #X, sizeof(Y.get_##X()) } }

struct Layout_Spec {
	std::string str;
	size_t size;
};

template <typename T>
void print_class_layout(const T * var, std::unordered_map<uint8_t *, Layout_Spec>& addr) {
	const char * cur_str = nullptr;
	uint8_t * bytes = (uint8_t*)var;
	size_t index = 0;
	size_t fifth_space = 0;
	size_t num_bytes = 0;
	if (is_little_endian()) {
		for (long long i = sizeof(T) / sizeof(uint8_t) - 1; i >= 0; i--) {
			if (addr.count(bytes + i)) {
				const Layout_Spec& cur_layout = addr[bytes + i];
				cur_str = cur_layout.str.c_str();
				num_bytes = cur_layout.size;
				index = 0;
			}
			if (cur_str == nullptr || cur_str[index] == '\0') {
				cur_str = nullptr;
			}
			if (cur_str == nullptr) {
				if (num_bytes > 0) {
					std::cout << "__";
				} else {
					std::cout << "..";
				}
			} else {
				if (num_bytes > 0) {
					num_bytes--;
					std::cout << cur_str[index];
					if (cur_str[index + 1] == '\0') {
						std::cout << "_";
					} else {
						std::cout << cur_str[index + 1];
					}
					index += 2;
					if (cur_str[index] == '\0') {
						cur_str = nullptr;
					}
				} else {
					std::cout << "..";
				}
			}
			fifth_space++;
			if (fifth_space == 2) {
				if (addr.count(bytes + i - 1)) {
					std::cout << "|";
				} else if (cur_str == nullptr || cur_str[index] == '\0') {
					if (num_bytes > 0) {
						std::cout << " ";
					} else {
						std::cout << "|";
					}
				} else {
					if (num_bytes > 0) {
						std::cout << cur_str[index];
					} else {
						std::cout << "|";
					}
					index++;
				}
				fifth_space = 0;
			}
		}
	} else {
		for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i++) {
			if (addr.count(bytes + i)) {
				const Layout_Spec& cur_layout = addr[bytes + i];
				cur_str = cur_layout.str.c_str();
				num_bytes = cur_layout.size;
				index = 0;
			}
			if (cur_str == nullptr || cur_str[index] == '\0') {
				cur_str = nullptr;
			}
			if (cur_str == nullptr) {
				if (num_bytes > 0) {
					std::cout << "__";
				} else {
					std::cout << "..";
				}
			} else {
				if (num_bytes > 0) {
					num_bytes--;
					std::cout << cur_str[index];
					if (cur_str[index + 1] == '\0') {
						std::cout << "_";
					} else {
						std::cout << cur_str[index + 1];
					}
					index += 2;
					if (cur_str[index] == '\0') {
						cur_str = nullptr;
					}
				} else {
					std::cout << "..";
				}
			}
			fifth_space++;
			if (fifth_space == 2) {
				if (addr.count(bytes + i - 1)) {
					std::cout << "|";
				} else if (cur_str == nullptr || cur_str[index] == '\0') {
					if (num_bytes > 0) {
						std::cout << " ";
					} else {
						std::cout << "|";
					}
				} else {
					if (num_bytes > 0) {
						std::cout << cur_str[index];
					} else {
						std::cout << "|";
					}
					index++;
				}
				fifth_space = 0;
			}
		}
	}
}

template <typename T>
void print_binary_layout(const T * var, std::vector<uint8_t>& original, std::vector<uint8_t>& last) {
	uint8_t* binary_layout = (uint8_t*)var;
	bool fill_original = original.empty();
	if (fill_original) {
		original.resize(sizeof(T) / sizeof(uint8_t));
	}
	if (last.empty()) {
		last.resize(sizeof(T) / sizeof(uint8_t));
	}
	if (is_little_endian()) {
		for (long long i = sizeof(T) / sizeof(uint8_t) - 1; i > 0; i -= 2) {
			if (fill_original) {
				original[i] = binary_layout[i];
				original[i - 1] = binary_layout[i - 1];
				last[i] = binary_layout[i];
				last[i - 1] = binary_layout[i - 1];
				std::cout << COLOR_FIRST;
			} else {
				if (binary_layout[i - 1] == original[i - 1] && binary_layout[i] == original[i]) {
					std::cout << COLOR_ORIGINAL_MATCH;
				} else if(binary_layout[i - 1] == last[i - 1] && binary_layout[i] == last[i]) {
					std::cout << COLOR_DIFFER_ORIGINAL;
				} else {
					std::cout << COLOR_CHANGE;
				}
				last[i] = binary_layout[i];
				last[i - 1] = binary_layout[i - 1];
			}
			uint16_t cur_val = binary_layout[i - 1] | binary_layout[i] << 8;
			std::cout << std::setw(4) << std::setfill('0') << std::right << std::hex << std::noshowbase << cur_val << " ";
		}
	} else {
		for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i += 2) {
			last[i] = binary_layout[i];
			last[i + 1] = binary_layout[i + 1];
			if (fill_original) {
				original[i] = binary_layout[i];
				original[i + 1] = binary_layout[i + 1];
				last[i] = binary_layout[i];
				last[i + 1] = binary_layout[i + 1];
				std::cout << COLOR_FIRST;
			} else {
				if (binary_layout[i + 1] == original[i + 1] && binary_layout[i] == original[i]) {
					std::cout << COLOR_ORIGINAL_MATCH;
				} else if(binary_layout[i + 1] == last[i + 1] && binary_layout[i] == last[i]) {
					std::cout << COLOR_DIFFER_ORIGINAL;
				} else {
					std::cout << COLOR_CHANGE;
				}
				last[i] = binary_layout[i];
				last[i + 1] = binary_layout[i + 1];
			}
			std::cout << std::setw(4) << std::setfill('0') << std::right << std::hex << std::noshowbase << *(uint16_t*)&binary_layout[i] << " ";
		}
	}
	std::cout << COLOR_RESET << "\n";
}
