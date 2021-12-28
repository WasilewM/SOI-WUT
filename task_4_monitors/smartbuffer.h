/**
 * @file smartbuffer.h 
 * @author Mateusz Wasilewski
 * @version 1.1
 * @date 2021-12-28
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#pragma once
#include "monitor.h"
#include <semaphore.h>
#include <queue>

class SmartBuffer: public Monitor
{
private:
    Condition full, empty;
    std::queue <int> buffer;
    int curr_buffer_size;
    int max_buffer_size;
public:
    SmartBuffer(int max_size);
    void addItemToBuffer(int item);
    int removeItemFromBuffer();
};