
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
#include <memory>
#include <iomanip>
/**
 * @brief service main function.
 *
 * @param[in] argc argument count
 * @param[in] argv argument vector
 * @return int
 */
int main(int argc, char *argv[])
{
    std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>(ECHO);
    icmp->set_identifier(0x1234);
    icmp->set_sequence_number(0x0001);

    std::cout << std::showbase      // show the 0x prefix
              << std::internal      // fill between the prefix and the number
              << std::setfill('0') // fill with 0s
              << std::hex;
    std::vector<uint8_t> message = icmp->encode();

    for (auto it = message.begin(); it != message.end(); it++)
    {
        std::cout << std::setw(4) << static_cast<unsigned>(*it) << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}