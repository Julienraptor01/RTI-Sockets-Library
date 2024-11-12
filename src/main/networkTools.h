#ifndef NETWORKTOOLS_H
#define NETWORKTOOLS_H

#include <cstdint>

/**
 * @brief A structure to represent an IPv4 address
 */
typedef union ipv4Address {
	uint8_t bytes[4];
	uint32_t address;
} ipv4Address;

/**
 * @brief Convert a string to an IPv4 address
 * @param string The string to convert
 * @param address The address to store the result
 * @return true if the conversion was successful, false otherwise
 * @note The string must be in the format "a.b.c.d" where a, b, c, and d are integers between 0 and 255
 */
bool stringToIPv4Address(const char string[], ipv4Address *address);
/**
 * @brief Convert an IPv4 address to a string
 * @param address The address to convert
 * @param string The string to store the result
 * @return true if the conversion was successful, false otherwise
 * @note The string must be at least 16 bytes long
 */
void ipv4AddressToString(ipv4Address address, char string[]);

#endif
