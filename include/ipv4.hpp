
/**
 * @file ipv4.hpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Protocol version 4 (IPv4) class headers acording
 * rfc792 (https://datatracker.ietf.org/doc/html/rfc791).
 *
 *    0                   1                   2                   3
 *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |Version|  IHL  |Type of Service|          Total Length         |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |         Identification        |Flags|      Fragment Offset    |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |  Time to Live |    Protocol   |         Header Checksum       |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                       Source Address                          |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                    Destination Address                        |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                    Options                    |    Padding    |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __IPV4_HPP__
#define __IPV4_HPP__

#include <vector>
#include <cstdint>
#include <memory>

/**
 * @brief This document describes version 4.
 * 
 */
#define IP_VERSION                  4U

/**
 * @brief Several networks offer service precedence, which somehow treats 
 * high precedence traffic as more important than other traffic (generally
 * by accepting only traffic above a certain precedence at time of high
 * load).  The major choice is a three way tradeoff between low-delay,
 * high-reliability, and high-throughput.
 * 
 */
#define TOS_ROUTINE                 (0U << 5)
#define TOS_PRIORITY                (1U << 5)
#define TOS_IMMEDIATE               (2U << 5)
#define TOS_FLASH                   (3U << 5)
#define TOS_FLASH_OVERRIDE          (4U << 5)
#define TOS_CRITIC_ECP              (5U << 5)
#define TOS_INTERNETWORK_CONTROL    (6U << 5)
#define TOS_NETWORK_CONTROL         (7U << 5)

/**
 * @brief The use of the Delay, Throughput, and Reliability indications may
 * increase the cost (in some sense) of the service.  In many networks
 * better performance for one of these parameters is coupled with worse
 * performance on another.  Except for very unusual cases at most two
 * of these three indications should be set.
 */
#define TOS_DELAY                   (1U << 4)
#define TOS_THROUGHPUT              (1U << 3)
#define TOS_REABILITY               (1U << 2)

#define IP_MIN_LENGTH               (uint16_t)0x14

#define IP_MIN_IHL                  (uint8_t)(IP_MIN_LENGTH / sizeof(uint32_t))

/**
 * @brief Various Control Flags.
 * 
 */
#define FLAG_DF                     (1U << 1)
#define FLAG_MF                     (1U << 0)

#define DEFAULT_TTL                 (uint8_t)0x40

enum protocol_number
{
    ICMP_NUMBER = 1,
    TCP_NUMBER = 6
};

/**
 * @brief IPv4 packet class.
 *
 */
class Ipv4
{
public:
    /**
     * @brief Construct a new Ipv 4 object
     * 
     * @param type 
     * @param code 
     */
    explicit Ipv4();

    /**
     * @brief Destroy the Ipv 4 object
     * 
     */
    virtual ~Ipv4();

    /**
     * @brief Get the protocol number object
     * 
     * @return uint8_t 
     */
    uint8_t get_protocol_number();

    /**
     * @brief Get the source address object
     * 
     * @return uint32_t 
     */
    uint32_t get_source_address();

    /**
     * @brief Get the destination address object
     * 
     * @return uint32_t 
     */
    uint32_t get_destination_address();

    /**
     * @brief Set the protocol number object
     * 
     * @param uint8_t 
     */
    void set_protocol_number(uint8_t protocol_number);

    /**
     * @brief Set the source address object
     * 
     * @param source_address 
     */
    void set_source_address(uint32_t source_address);

    /**
     * @brief Set the destination address object
     * 
     * @param destination_address 
     */
    void set_destination_address(uint32_t destination_address);

    /**
     * @brief Set the data object
     * 
     * @param data 
     */
    void set_data(std::vector<uint8_t> data);

    /**
     * @brief This method transform IPv4 packet fields in an array.
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
     * @brief The Version field indicates the format of the internet header. 
     */
    uint8_t version : 4;
    /**
     * @brief Internet Header Length is the length of the internet header in 32
     * bit words, and thus points to the beginning of the data. Note that
     * the minimum value for a correct header is 5.
     */
    uint8_t ihl : 4;
    /**
     * @brief The Type of Service provides an indication of the abstract
     * parameters of the quality of service desired. These parameters are
     * to be used to guide the selection of the actual service parameters
     * when transmitting a datagram through a particular network. 
     */
    uint8_t type_of_service;
    /**
     * @brief Total Length is the length of the datagram, measured in octets,
     * including internet header and data. This field allows the length of
     * a datagram to be up to 65,535 octets.
     */
    uint16_t total_length;
    /**
     * @brief An identifying value assigned by the sender to aid in assembling the
     * fragments of a datagram.
     */
    uint16_t identification;
    /**
     * @brief Various Control Flags. 
     */
    uint8_t flags : 3;
    /**
     * @brief This field indicates where in the datagram this fragment belongs.
     * The fragment offset is measured in units of 8 octets (64 bits).  The
     * first fragment has offset zero.
     */
    uint16_t fragment_offset : 13;
    /**
     * @brief This field indicates the maximum time the datagram is allowed to
     * remain in the internet system.  If this field contains the value
     * zero, then the datagram must be destroyed.  This field is modified
     * in internet header processing.  The time is measured in units of
     * seconds, but since every module that processes a datagram must
     * decrease the TTL by at least one even if it process the datagram in
     * less than a second, the TTL must be thought of only as an upper
     * bound on the time a datagram may exist.  The intention is to cause
     * undeliverable datagrams to be discarded, and to bound the maximum
     * datagram lifetime.
     */
    uint8_t ttl;
    /**
     * @brief This field indicates the next level protocol used in the data
     * portion of the internet datagram.  The values for various protocols
     * are specified in "Assigned Numbers" (https://datatracker.ietf.org/doc/html/rfc790)
     */
    uint8_t protocol;
    /**
     * @brief A checksum on the header only.  Since some header fields change
     * (e.g., time to live), this is recomputed and verified at each point
     * that the internet header is processed.
     */
    uint16_t checksum;
    /**
     * @brief The source address.
     */
    uint32_t source_address;
    /**
     * @brief The destination address.
     */
    uint32_t destination_address;
    /**
     * @brief The options may appear or not in datagrams.  They must be
     * implemented by all IP modules (host and gateways).  What is optional
     * is their transmission in any particular datagram, not their
     * implementation.
     */
    std::shared_ptr<std::vector<uint16_t>> options;
    /**
     * @brief 
     * 
     */
    std::shared_ptr<std::vector<uint8_t>> data;
};

#endif //__IPV4_HPP__