
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
 */
ICMP::ICMP(uint8_t type, uint8_t code) : 
           type(type), code(code)
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
 * @brief The checksum is the 16-bit ones's complement of the one's
 * complement sum of the ICMP message starting with the ICMP Type.
 * For computing the checksum , the checksum field should be zero.
 * This checksum may be replaced in the future.
 * 
 */
void ICMP::update_checksum()
{
    //Todo update checksum.
}