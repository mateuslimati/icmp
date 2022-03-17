
/**
 * @file icmp.hpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Control Message Protocol (ICMP) class headers acording
 * rfc792 (https://datatracker.ietf.org/doc/html/rfc792).
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |     Type      |     Code      |          Checksum             |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |                             unused                            |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ICMP_HPP__
#define __ICMP_HPP__

#include <vector>
#include <cstdint>

/**
 * @brief ICMP packet class.
 *
 */
class ICMP
{
public:
    /**
     * @brief Construct a new ICMP object
     *
     * @param value
     */
    explicit ICMP(uint8_t type = 0x00, uint8_t code = 0x00);

    /**
     * @brief Destroy the ICMP object
     *
     */
    virtual ~ICMP();

    /**
     * @brief Get the type object
     * 
     * @return uint8_t 
     */
    uint8_t get_type();

    /**
     * @brief Get the code object
     * 
     * @return uint8_t 
     */
    uint8_t get_code();

    /**
     * @brief Set the type object
     * 
     * @param type 
     * @return true 
     * @return false 
     */
    bool set_type(uint8_t type);

    /**
     * @brief Set the code object
     * 
     * @param code 
     * @return true 
     * @return false 
     */
    bool set_code(uint8_t code);

    /**
     * @brief This method transform ICMP packet fields in an array.
     *
     * @return Array encoded packet.
     */
    std::vector<uint8_t> encode();

protected:
    /**
     * @brief This method updates packet checksum.
     * 
     */
    void update_checksum();

private:
    /**
     * @brief The type field indicates the type of the message. Its value
     * determines the format of the remaining data.
     */
    uint8_t type;
    /**
     * @brief The code field depends on the message type. It is used to create an
     * additional level of message granularity.
     */
    uint8_t code;
    /**
     * @brief The checksum field is used to detect data corruption in the ICMPv6
     * message and parts of the IPv6 header.
     */
    uint16_t checksum;
};

#endif //__ICMP_HPP__