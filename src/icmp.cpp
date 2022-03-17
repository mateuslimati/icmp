
/**
 * @file icmp.cpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Control Message Protocol (ICMP) class methods.
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <icmp.hpp>
#include <limits>

/**
 * @brief Construct a new ICMP::ICMP object
 *
 * @param type The type field indicates the type of the message. Its value
 * determines the format of the remaining data.
 * @param code The code field depends on the message type. It is used to create an
 * additional level of message granularity.
 * @param checksum The checksum field is used to detect data corruption in the ICMPv6
 * message and parts of the IPv6 header.
 * @param message_bodyICMPv6 messages are grouped into two classes: error messages and
 * informational messages.  Error messages are identified as such by a
 * zero in the high-order bit of their message Type field values. Thus,
 * error messages have message types from 0 to 127; informational
 * messages have message types from 128 to 255.
 */
ICMP::ICMP(uint8_t type, uint8_t code,
           uint16_t checksum, uint32_t message_body) : 
           type(type), code(code), checksum(checksum), message_body(message_body)
{
}

/**
 * @brief Destroy the ICMP::ICMP object
 *
 */
ICMP::~ICMP()
{
}