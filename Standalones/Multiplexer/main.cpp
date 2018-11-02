/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Lukas
 *
 * Created on 2 listopada 2018, 00:13
 */

#include <cstdlib>
#include "Multiplexer.h"
 
/*
 * 
 */
int main(int argc, char** argv) 
{
    Multiplexer testMux;
    
    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW)
    ->addStateToQueue(HIGH, LOW, LOW)
    ->addStateToQueue(LOW, HIGH, LOW)
    ->addStateToQueue(LOW, LOW, HIGH)
    ->begin();
    
    int cnt = 5;
    while(cnt--)
    {
        delay(100);
        testMux.nextState();
    }
    
   // std::cout << std::endl;
   // std::cout << std::endl;
   // std::cout << std::endl;
    
    //cnt = 10;
   // while(cnt--)
    //{
    //    delay(100);
    //    testMux.prevState();
   // }
            
    return 0;
}

