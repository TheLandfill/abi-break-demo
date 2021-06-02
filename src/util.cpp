#include <cstdint>

bool is_little_endian() {
	uint16_t test = 1;
	uint8_t lesser = ((uint8_t*)&test)[0];
	uint8_t greater = ((uint8_t*)&test)[1];
	return lesser > greater;
}
