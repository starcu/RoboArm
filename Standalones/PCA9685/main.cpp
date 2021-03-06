/*
 * author: Lukas
 *
 */

#include "PCA9685.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <vector>

const uint16_t chNum = 6;
const std::vector<uint16_t> widths {1000, 1100, 1200, 1300, 1400, 1500};

int main(int argc, char **argv) 
{
	PCA9685 pca(chNum);

    while (true) 
    {
    	for(uint16_t i=0; i<chNum; ++i)
    	{
    		pca.writeToChannel(i)->setWidth(widths.at(i));
    	}
    	std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0; 
}
