
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
 * @param message_body ICMPv6 messages are grouped into two classes: error messages and
 * informational messages.  Error messages are identified as such by a
 * zero in the high-order bit of their message Type field values. Thus,
 * error messages have message types from 0 to 127; informational
 * messages have message types from 128 to 255.
 */
ICMP::ICMP(uint8_t type, uint8_t code, uint32_t message_body) : 
           type(type), code(code), message_body(message_body)
{
    this->update_checksum();
}

/**
 * @brief Destroy the ICMP::ICMP object
 *
 */
ICMP::~ICMP()
{
}

/**
 * @brief Get the type object
 * 
 * @return uint8_t 
 */
uint8_t ICMP::get_type()
{
    return this->type;
}

/**
 * @brief Get the code object
 * 
 * @return uint8_t 
 */
uint8_t ICMP::get_code()
{
    return this->code;
}

/**
 * @brief Set the type object
 * 
 * @param type 
 * @return true 
 * @return false 
 */
bool ICMP::set_type(uint8_t type)
{
    this->update_checksum();
    return false;
}

/**
 * @brief Set the code object
 * 
 * @param code 
 * @return true 
 * @return false 
 */
bool ICMP::set_code(uint8_t code)
{
    this->update_checksum();
    return false;
}

/**
 * @brief 
 * 
 * @return std::vector<uint8_t> 
 */
std::vector<uint8_t> ICMP::encode()
{
    return std::vector<uint8_t>{0};
}

/**
 * @brief The checksum is the 16-bit one's complement of the one's complement
 * sum of the entire ICMPv6 message, starting with the ICMPv6 message
 * type field, and prepended with a "pseudo-header" of IPv6 header
 * fields, as specified in [IPv6, Section 8.1].  The Next Header value
 * used in the pseudo-header is 58.  (The inclusion of a pseudo-header
 * in the ICMPv6 checksum is a change from IPv4; see [IPv6] for the
 * rationale for this change.)
 * 
 */
void ICMP::update_checksum()
{
    //Todo update checksum.
}