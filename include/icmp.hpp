
/**
 * @file icmp.hpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Control Message Protocol (ICMP) class headers acording
 * rfc792 (https://datatracker.ietf.org/doc/html/rfc792).
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |     Code      |          Checksum             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Data ...
 *  +-+-+-+-+-
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
#include <memory>

/**
 * @brief Summary of Message Types, according rfc792.
 *
 */
typedef enum message_type
{
    ECHO_REPLY = 0,
    DESTINATION_UNREACHABLE = 3,
    SOURCE_QUENCH = 4,
    REDIRECT = 5,
    ECHO = 8,
    TIME_EXCEEDED = 11,
    PARAMETER_PROBLEM = 12,
    TIMESTAMP = 13,
    TIMESTAMP_REPLY = 14,
    INFORMATION_REQUEST = 15,
    INFORMATION_REPLY = 16
} message_type_t;

typedef enum message_code
{
    DEFAULT_CODE = 0,

    NET_UNREACHABLE = 0,
    HOST_UNREACHABLE = 1,
    PROTOCOL_UNREACHABLE = 2,
    PORT_UNREACHABLE = 3,
    FRAGMENTATION_NEEDED = 4,
    SOURCE_ROUTE_FAILED = 5,

    REDIRECT_DATAGRAMS_FOR_NET = 0,
    REDIRECT_DATAGRAMS_FOR_HOST = 1,
    REDIRECT_DATAGRAMS_FOR_TOS_AND_NET = 2,
    REDIRECT_DATAGRAMS_FOR_TOS_AND_HOST = 3,

    TTL_EXCEEDED = 0,
    FRAGMENT_REASSEMBLY_TIME_EXCEEDED = 1,
} message_code_t;

/**
 * @brief ICMP packet class.
 *
 */
class Icmp
{
public:
    /**
     * @brief Construct a new ICMP object
     *
     * @param value
     */
    explicit Icmp(message_type_t type = ECHO_REPLY, message_code_t code = DEFAULT_CODE);

    /**
     * @brief Destroy the ICMP object
     *
     */
    virtual ~Icmp();

    /**
     * @brief Get the type object
     *
     * @return message_type_t
     */
    message_type_t get_type();

    /**
     * @brief Get the code object
     *
     * @return message_code_t
     */
    message_code_t get_code();

    /**
     * @brief Get the identifier object
     * 
     * @return uint16_t 
     */
    uint16_t get_identifier();

    /**
     * @brief Get the sequence number object
     * 
     * @return uint16_t 
     */
    uint16_t get_sequence_number();

    /**
     * @brief Set the type object
     * 
     * @param type 
     */
    void set_type(message_type_t type);

    /**
     * @brief Set the code object
     * 
     * @param code 
     */
    void set_code(message_code_t code);

    /**
     * @brief Set the identifier object
     * 
     * @param identifier 
     */
    void set_identifier(uint16_t identifier);

    /**
     * @brief Set the sequence number object
     * 
     * @param sequence_number 
     */
    void set_sequence_number(uint16_t sequence_number);

    /**
     * @brief Set the data object
     * 
     * @param data 
     */
    void set_data(std::vector<uint8_t> data);

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
    message_type_t type;
    /**
     * @brief The code field depends on the message type. It is used to create an
     * additional level of message granularity.
     */
    message_code_t code;
    /**
     * @brief The checksum field is used to detect data corruption in the ICMPv6
     * message and parts of the IPv6 header.
     */
    uint16_t checksum;
    /**
     * @brief The data received in the echo message must be returned in the echo
     * reply message.
     */
    std::unique_ptr<std::vector<uint16_t>> data;
};

#endif //__ICMP_HPP__