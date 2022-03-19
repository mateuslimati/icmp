/**
 * @file utils.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <stdint.h>

void get_application_addresses(int received_addresses_num, char *received_addresses[],
                               uint32_t *source_address, uint32_t *destination_address);

#endif //__UTILS_HPP__