/**
 * @file smartbuffer.cpp 
 * @author Mateusz Wasilewski
 * @version 1.1
 * @date 2021-12-28
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#include "smartbuffer.h"
#include <iostream>

SmartBuffer::SmartBuffer(int max_size){
    max_buffer_size = max_size;
    curr_buffer_size = 0;
};

void SmartBuffer::addItemToBuffer(int item) {
    enter();
    if(curr_buffer_size == max_buffer_size) {
        wait(full);
    }
    
    buffer.push(item);
    curr_buffer_size++;

    if(curr_buffer_size == 1) {
        signal(empty);
    }

    leave();
}

int SmartBuffer::removeItemFromBuffer() {
    int consumed_item = 0;

    enter();
    if(curr_buffer_size == 0) {
        wait(empty);
    }

    consumed_item = buffer.front();
    buffer.pop();
    curr_buffer_size--;


    if(curr_buffer_size == max_buffer_size - 1) {
        signal(full);
    }

    leave();
    return consumed_item;
}