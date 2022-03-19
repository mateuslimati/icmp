
/**
 * @file main.cpp
 * @author Mateus Lima (mateuslima.ti@gmail.com)
 * @brief Service main file
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <main.hpp>
#include <icmp.hpp>
#include <ipv4.hpp>
#include <memory>
#include <iomanip>
#include <ctime>

/**
 * @brief service main function.
 * 
 * @param[in] argc argument count
 * @param[in] argv argument vector
 * @return int 
 */
int main(int argc, char *argv[])
{
    std::unique_ptr<Ipv4> ipv4 = std::make_unique<Ipv4>();
    ipv4->set_protocol_number(ICMP_NUMBER);
    ipv4->set_source_address(0xc0a8641B);
    ipv4->set_destination_address(0x08080808);

    std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>(ECHO);
    icmp->set_identifier(0x1234);
    icmp->set_sequence_number(0x0001);

    ipv4->set_data(icmp->encode());

    std::time_t result = std::time(nullptr);
    std::cout << std::showbase     // show the 0x prefix
              << std::internal     // fill between the prefix and the number
              << std::setfill('0') // fill with 0s
              << std::hex;

    std::vector<uint8_t> ip_msg = ipv4->encode();
    for (auto it = ip_msg.begin(); it != ip_msg.end(); it++)
    {
        std::cout << std::setw(4) << static_cast<unsigned>(*it) << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}