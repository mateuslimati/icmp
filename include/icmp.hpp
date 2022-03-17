
/**
 * @file icmp.hpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Control Message Protocol (ICMP) class headers acording
 * rfc4443 (https://datatracker.ietf.org/doc/html/rfc4443).
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |     Type      |     Code      |          Checksum             |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                                                               |
 *     +                         Message Body                          +
 *     |                                                               |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
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
    explicit ICMP(uint8_t type = 0x00, uint8_t code = 0x00,
                  uint16_t checksum = 0x0000, uint32_t message_body = 0x00000000);

    /**
     * @brief Destroy the ICMP object
     *
     */
    virtual ~ICMP();

    /**
     * @brief This method transform ICMP packet fields in an array.
     *
     * @return Array encoded packet.
     */
    std::vector<uint8_t> Encode();

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
    /**
     * @brief ICMPv6 messages are grouped into two classes: error messages and
     * informational messages.  Error messages are identified as such by a
     * zero in the high-order bit of their message Type field values. Thus,
     * error messages have message types from 0 to 127; informational
     * messages have message types from 128 to 255.
     *
     */
    uint32_t message_body;
};

#endif //__ICMP_HPP__