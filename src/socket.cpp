/**
 * @file socket.cpp
 * @author Mateus Alves (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <socket.hpp>
#include <exceptions.hpp>
#include <iostream>

/**
 * @brief Construct a new Socket:: Socket object
 *
 */
Socket::Socket()
{
    int ret, fd, option;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (fd < 0)
    {
        std::cout << "Socket - Could not create socket. Erro " << errno << " FD " << fd << std::endl;
        throw Exception(EXCEPTION_MSG("Socket - Could not create socket"));
    }

    ret = setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &option, sizeof(option));
    if (ret == -1)
    {
        throw Exception(EXCEPTION_MSG("Socket - Could not set socket options."));
    }

    this->s_file_descriptor = fd;
}

/**
 * @brief Destroy the Socket:: Socket object
 *
 */
Socket::~Socket()
{
}

/**
 * @brief
 *
 * @param raw
 * @return int
 */
int Socket::send_raw(std::vector<uint8_t> raw, uint32_t destination_address)
{
    int bytes_sent;
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = destination_address;
    localaddr.sin_port = 0; // Any local port will do

    /* Send packet */
    return sendto(this->s_file_descriptor, raw.data(), raw.size(), 0,
                  (struct sockaddr *)&localaddr, sizeof(localaddr));
}
