//
// Created by juuso on 7.11.2019.
//

#include "miscellanous.h"

void min(const int *array, int *min_value, int *min_index){
    int minimum;
    int index;
    minimum = array[0];
    index = 0;
    size_t size = sizeof(*array)/sizeof(array[0]);
    for (int c = 1; c < size; c++)
    {
        if (array[c] < minimum)
        {
            minimum = array[c];
            index = c;
        }
    }
    *min_value = minimum;
    *min_index = index;
}