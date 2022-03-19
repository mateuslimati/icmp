/**
 * @file socket.hpp
 * @author Mateus Lima Alves (mateuslima.ti@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <string>
#include <sys/epoll.h>
#include <list>
#include <memory>
#include <vector>

#define SOCKET_WAIT_TIMEOUT 500 // In milliseconds.

class Socket
{
public:
    explicit Socket();
    virtual ~Socket();

    void send_raw(std::vector<uint8_t> raw, uint32_t destination_address);
private:
    int s_file_descriptor;
};

#endif //__SOCKET_HPP__

/** @} */