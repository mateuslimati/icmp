
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
#include <iterator>
#include <iostream>
#include <exceptions.hpp>

/**
 * @brief Construct a new Icmp::Icmp object
 *
 * @param type The type field indicates the type of the message. Its value
 * determines the format of the remaining data.
 * @param code The code field depends on the message type. It is used to create an
 * additional level of message granularity.
 */
Icmp::Icmp(message_type_t type, message_code_t code)
{
    this->data = std::make_shared<std::vector<uint16_t>>();
    this->set_type(type);
    this->set_code(code);
}

/**
 * @brief Destroy the Icmp::Icmp object
 *
 */
Icmp::~Icmp()
{
}

/**
 * @brief Get the type object
 *
 * @return message_type_t
 */
message_type_t Icmp::get_type()
{
    return this->type;
}

/**
 * @brief Get the code object
 *
 * @return message_code_t
 */
message_code_t Icmp::get_code()
{
    return this->code;
}

/**
 * @brief Get the identifier object
 *
 * @return uint16_t
 */
uint16_t Icmp::get_identifier()
{
    if (this->type == ECHO_REPLY || this->type == ECHO)
    {
        return this->data->at(0);
    }
    throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this attribute."));
}

/**
 * @brief Get the sequence number object
 *
 * @return uint16_t
 */
uint16_t Icmp::get_sequence_number()
{
    if (this->type == ECHO_REPLY || this->type == ECHO)
    {
        return this->data->at(1);
    }
    throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this attribute."));
}

/**
 * @brief Get the data object
 *
 * @return std::vector<uint16_t>
 */
std::vector<uint16_t> Icmp::get_data()
{
    return *this->data.get();
}

/**
 * @brief Set the type object
 *
 * @param type
 */
void Icmp::set_type(message_type_t type)
{
    switch (type)
    {
    case ECHO:
    {
        this->data.reset(new std::vector<uint16_t>(2, 0));
        break;
    }
    case ECHO_REPLY:
    case DESTINATION_UNREACHABLE:
    case SOURCE_QUENCH:
    case REDIRECT:
    case TIME_EXCEEDED:
    case PARAMETER_PROBLEM:
    case TIMESTAMP:
    case TIMESTAMP_REPLY:
    case INFORMATION_REQUEST:
    case INFORMATION_REPLY:
    default:
    {
        throw Exception(EXCEPTION_MSG("ICMP - Packet type not implemented yet."));
    }
    }
    this->type = type;
}

/**
 * @brief Set the code object
 *
 * @param code
 */
void Icmp::set_code(message_code_t code)
{
    switch (this->type)
    {
    case ECHO_REPLY:
    case SOURCE_QUENCH:
    case ECHO:
    case PARAMETER_PROBLEM:
    case TIMESTAMP:
    case TIMESTAMP_REPLY:
    case INFORMATION_REQUEST:
    case INFORMATION_REPLY:
    {
        if (code != DEFAULT_CODE)
        {
            throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this code."));
        }
        break;
    }
    case DESTINATION_UNREACHABLE:
    {
        if (code != NET_UNREACHABLE && code != HOST_UNREACHABLE &&
            code != PROTOCOL_UNREACHABLE && code != PORT_UNREACHABLE &&
            code != FRAGMENTATION_NEEDED && code != SOURCE_ROUTE_FAILED)
        {
            throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this code."));
        }
        break;
    }
    case REDIRECT:
    {
        if (code != REDIRECT_DATAGRAMS_FOR_NET && code != REDIRECT_DATAGRAMS_FOR_HOST &&
            code != REDIRECT_DATAGRAMS_FOR_TOS_AND_NET && code != REDIRECT_DATAGRAMS_FOR_TOS_AND_HOST)
        {
            throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this code."));
        }
        break;
    }
    case TIME_EXCEEDED:
    {
        if (code != TTL_EXCEEDED && code != FRAGMENT_REASSEMBLY_TIME_EXCEEDED)
        {
            throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this code."));
        }
        break;
    }
    default:
    {
        throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this code."));
    }
    }
    this->code = code;
    return;
}

/**
 * @brief Set the identifier object
 *
 * @param identifier
 */
void Icmp::set_identifier(uint16_t identifier)
{
    switch (this->type)
    {
    case ECHO_REPLY:
    case ECHO:
    {
        (*this->data)[0] = identifier;
        break;
    }
    case DESTINATION_UNREACHABLE:
    case SOURCE_QUENCH:
    case REDIRECT:
    case TIME_EXCEEDED:
    case PARAMETER_PROBLEM:
    case TIMESTAMP:
    case TIMESTAMP_REPLY:
    case INFORMATION_REQUEST:
    case INFORMATION_REPLY:
    default:
    {
        throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this attribute."));
    }
    }
    return;
}

/**
 * @brief Set the sequence number object
 *
 * @param sequence_number
 */
void Icmp::set_sequence_number(uint16_t sequence_number)
{
    switch (this->type)
    {
    case ECHO_REPLY:
    case ECHO:
    {
        (*this->data)[1] = sequence_number;
        break;
    }
    case DESTINATION_UNREACHABLE:
    case SOURCE_QUENCH:
    case REDIRECT:
    case TIME_EXCEEDED:
    case PARAMETER_PROBLEM:
    case TIMESTAMP:
    case TIMESTAMP_REPLY:
    case INFORMATION_REQUEST:
    case INFORMATION_REPLY:
    default:
    {
        throw Exception(EXCEPTION_MSG("ICMP - This packet type don't have this attribute."));
    }
    }
}

/**
 * @brief Set the data object
 *
 * @param data
 */
void Icmp::set_data(std::vector<uint16_t> data)
{
    switch (this->type)
    {
    case ECHO_REPLY:
    case ECHO:
    {
        this->data->insert(this->data->end(),
                           std::make_move_iterator(data.begin()),
                           std::make_move_iterator(data.end()));
        break;
    }
    case DESTINATION_UNREACHABLE:
    case SOURCE_QUENCH:
    case REDIRECT:
    case TIME_EXCEEDED:
    case PARAMETER_PROBLEM:
    case TIMESTAMP:
    case TIMESTAMP_REPLY:
    case INFORMATION_REQUEST:
    case INFORMATION_REPLY:
    default:
        break;
    }
    return;
}

/**
 * @brief
 *
 * @return std::vector<uint8_t>
 */
std::vector<uint8_t> Icmp::encode()
{
    std::vector<uint8_t> encoded_data = {};

    this->update_checksum();

    encoded_data.push_back(this->type);
    encoded_data.push_back(this->code);
    encoded_data.push_back(this->checksum >> 8);
    encoded_data.push_back(this->checksum & __UINT8_MAX__);

    for (auto it = this->data->begin(); it != this->data->end(); ++it)
    {
        encoded_data.push_back((uint8_t)(*it >> 8));
        encoded_data.push_back((uint8_t)(*it & __UINT8_MAX__));
    }
    return encoded_data;
}

/**
 * @brief The checksum is the 16-bit ones's complement of the one's
 * complement sum of the ICMP message starting with the ICMP Type.
 * For computing the checksum , the checksum field should be zero.
 * This checksum may be replaced in the future.
 *
 */
void Icmp::update_checksum()
{
    uint32_t checksum_tmp;
    checksum_tmp = (this->type << 8) | this->code;
    for (auto it = this->data->begin(); it != this->data->end(); ++it)
    {
        checksum_tmp += *it;
    }
    checksum_tmp += (uint16_t)(checksum_tmp >> 16);
    checksum_tmp = (uint16_t)(__UINT16_MAX__ - (uint16_t)checksum_tmp);
    this->checksum = (uint16_t)checksum_tmp;
    return;
}
