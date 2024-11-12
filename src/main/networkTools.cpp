#include "networkTools.h"

#include <cstdio>

bool stringToIPv4Address(const char string[], ipv4Address *address) {
	uint8_t a, b, c, d;
	if (sscanf(string, "%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d) != 4) {
		return false;
	}
	address->bytes[0] = a;
	address->bytes[1] = b;
	address->bytes[2] = c;
	address->bytes[3] = d;
	return true;
}

void ipv4AddressToString(ipv4Address address, char string[]) {
	sprintf(string, "%hhu.%hhu.%hhu.%hhu", address.bytes[0], address.bytes[1], address.bytes[2], address.bytes[3]);
}
