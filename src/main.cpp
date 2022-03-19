
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
#include <utils.hpp>
#include <memory>
#include <arpa/inet.h>

/**
 * @brief service main function.
 *
 * @param[in] argc argument count
 * @param[in] argv argument vector
 * @return int
 */
int main(int argc, char *argv[])
{
    uint32_t source_address, destination_address;
    try
    {
        get_application_addresses(argc, argv, &source_address, &destination_address);
        std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>(ECHO);
        std::unique_ptr<Ipv4> ipv4 = std::make_unique<Ipv4>();
        std::unique_ptr<Socket> socket = std::make_unique<Socket>();

        ipv4->set_protocol_number(ICMP_NUMBER);
        ipv4->set_source_address(source_address);
        ipv4->set_destination_address(destination_address);

        ipv4->set_data(icmp->encode());

        socket->send_raw(ipv4->encode(), destination_address);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}