
/**
 * @file ipv4.cpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief Internet Protocol version 4 (IPv4) class methods.
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <ipv4.hpp>
#include <limits>
#include <iterator>

/**
 * @brief Construct a new Ipv 4:: Ipv 4 object
 *
 */
Ipv4::Ipv4()
{
    this->version = IP_VERSION;

    this->ihl = IP_MIN_IHL;

    this->type_of_service |= (uint8_t)TOS_ROUTINE;
    this->type_of_service &= (uint8_t)~TOS_DELAY;
    this->type_of_service &= (uint8_t)~TOS_THROUGHPUT;
    this->type_of_service &= (uint8_t)~TOS_REABILITY;

    this->total_length = IP_MIN_LENGTH;

    this->flags |= (uint8_t)FLAG_DF;
    this->flags &= (uint8_t) ~(FLAG_MF);

    this->ttl = DEFAULT_TTL;

    this->options = std::shared_ptr<std::vector<uint16_t>>(new std::vector<uint16_t>);
    this->data = std::shared_ptr<std::vector<uint8_t>>(new std::vector<uint8_t>);
}

/**
 * @brief Destroy the Ipv 4:: Ipv 4 object
 *
 */
Ipv4::~Ipv4()
{
}

/**
 * @brief Get the protocol number object
 *
 * @return uint8_t
 */
uint8_t Ipv4::get_protocol_number()
{
    return this->protocol;
}

/**
 * @brief Get the source address object
 *
 * @return uint32_t
 */
uint32_t Ipv4::get_source_address()
{
    return this->source_address;
}

/**
 * @brief Get the destination address object
 *
 * @return uint32_t
 */
uint32_t Ipv4::get_destination_address()
{
    return this->destination_address;
}

/**
 * @brief Set the protocol number object
 *
 * @param uint8_t
 */
void Ipv4::set_protocol_number(uint8_t protocol_number)
{
    this->protocol = protocol_number;
}

/**
 * @brief Set the source address object
 *
 * @param source_address
 */
void Ipv4::set_source_address(uint32_t source_address)
{
    this->source_address = source_address;
}

/**
 * @brief Set the destination address object
 *
 * @param destination_address
 */
void Ipv4::set_destination_address(uint32_t destination_address)
{
    this->destination_address = destination_address;
}

/**
 * @brief Set the data object
 * 
 * @param data 
 */
void Ipv4::set_data(std::vector<uint8_t> data)
{
    this->data.reset(new std::vector<uint8_t>(data.begin(), data.end()));
    this->total_length = IP_MIN_LENGTH + this->data->size();
}

/**
 * @brief
 *
 * @return std::vector<uint8_t>
 */
std::vector<uint8_t> Ipv4::encode()
{
    std::vector<uint8_t> encoded_data = {};

    encoded_data.push_back((this->version << 4) | this->ihl);
    encoded_data.push_back(this->type_of_service);
    encoded_data.push_back((uint8_t)(this->total_length >> 8) & __UINT8_MAX__);
    encoded_data.push_back((uint8_t)this->total_length & __UINT8_MAX__);
    encoded_data.push_back((uint8_t)(this->identification >> 8) & __UINT8_MAX__);
    encoded_data.push_back((uint8_t)this->identification & __UINT8_MAX__);
    encoded_data.push_back((uint8_t)(this->flags << 5) | ((this->fragment_offset >> 8) & 0x3));
    encoded_data.push_back((uint8_t)(this->fragment_offset));
    encoded_data.push_back((uint8_t)this->ttl);
    encoded_data.push_back((uint8_t)this->protocol);
    encoded_data.push_back((uint8_t)(this->source_address >> 24));
    encoded_data.push_back((uint8_t)(this->source_address >> 16));
    encoded_data.push_back((uint8_t)(this->source_address >> 8));
    encoded_data.push_back((uint8_t)this->source_address);
    encoded_data.push_back((uint8_t)(this->destination_address >> 24));
    encoded_data.push_back((uint8_t)(this->destination_address >> 16));
    encoded_data.push_back((uint8_t)(this->destination_address >> 8));
    encoded_data.push_back((uint8_t)this->destination_address);

    this->update_checksum();
    encoded_data.push_back((uint8_t)(this->checksum >> 8));
    encoded_data.push_back((uint8_t)this->checksum & __UINT8_MAX__);

    for (auto it = this->options->begin(); it != this->options->end(); ++it)
    {
        encoded_data.push_back((uint8_t)(*it >> 8));
        encoded_data.push_back((uint8_t)(*it & __UINT8_MAX__));
    }
    for (auto it = this->data->begin(); it != this->data->end(); ++it)
    {
        encoded_data.push_back(*it);
    }
    return encoded_data;
}

/**
 * @brief A checksum on the header only.  Since some header fields change
 * (e.g., time to live), this is recomputed and verified at each point
 * that the internet header is processed.
 *
 */
void Ipv4::update_checksum()
{
    uint32_t checksum_tmp;
    checksum_tmp = ((this->version << 12) | (this->ihl << 8) |
                   (this->type_of_service));
    checksum_tmp += this->total_length;
    checksum_tmp += this->identification;
    checksum_tmp += (this->flags << 13) | (this->fragment_offset);
    checksum_tmp += (this->ttl << 8) | (this->protocol);
    checksum_tmp += ((this->source_address >> 16) & __UINT16_MAX__);
    checksum_tmp += (this->source_address & __UINT16_MAX__);
    checksum_tmp += ((this->destination_address >> 16) & __UINT16_MAX__);
    checksum_tmp += (this->destination_address & __UINT16_MAX__);
    for (auto it = this->options->begin(); it != this->options->end(); ++it)
    {
        checksum_tmp += *it;
    }
    checksum_tmp += (uint16_t)(checksum_tmp >> 16);
    checksum_tmp = (uint16_t)(__UINT16_MAX__ - (uint16_t)checksum_tmp);
    this->checksum = (uint16_t)checksum_tmp;
}