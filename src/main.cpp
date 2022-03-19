
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
#include <socket.hpp>
#include <memory>

/**
 * @brief service main function.
 *
 * @param[in] argc argument count
 * @param[in] argv argument vector
 * @return int
 */
int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>(ECHO);
        std::unique_ptr<Ipv4> ipv4 = std::make_unique<Ipv4>();
        std::unique_ptr<Socket> socket = std::make_unique<Socket>();

        icmp->set_identifier(0x1234);
        icmp->set_sequence_number(0x0002);

        ipv4->set_protocol_number(ICMP_NUMBER);
        ipv4->set_source_address(0xc0a8641F);
        ipv4->set_destination_address(0x08080808);
        
        ipv4->set_data(icmp->encode());

        socket->send_raw(ipv4->encode(), 0x08080808);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_SUCCESS;
}