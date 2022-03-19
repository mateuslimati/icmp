/**
 * @file utils.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <utils.hpp>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <exceptions.hpp>
#include <vector>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

/**
 * @brief Get the application addresses object
 * 
 * @param received_addresses_num 
 * @param received_addresses 
 * @param source_address 
 * @param destination_address 
 */
void get_application_addresses(int received_addresses_num, char *received_addresses[],
                               uint32_t *source_address, uint32_t *destination_address)
{
    if (received_addresses_num < 3)
    {
        throw Exception(EXCEPTION_MSG("UTILS - You need to pass <source IP> <destination IP>"));
    }

    *source_address = inet_addr(received_addresses[1]);
    if (*source_address < 0)
    {
        throw Exception(EXCEPTION_MSG("UTILS - Source IP invalid"));
    }
    *destination_address = inet_addr(received_addresses[2]);
    if (*destination_address < 0)
    {
        throw Exception(EXCEPTION_MSG("UTILS - Destination IP invalid"));
    }
}