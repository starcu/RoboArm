/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Multiplexer.cpp
 * Author: Lukas
 * 
 * Created on 1 listopada 2018, 23:11
 */

#include "Multiplexer.h"

Multiplexer* Multiplexer::setCtrlPins(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2)
{
    #ifdef DEBUG
    std::cout << "[" << __func__ << "] "
            << "Pins set: " 
            << std::to_string(_gpio0) 
            << " " 
            << std::to_string(_gpio1) 
            << " " 
            << std::to_string(_gpio2) 
            << std::endl;
    #endif
    
    gpio0 = _gpio0;
    gpio1 = _gpio1;
    gpio2 = _gpio2;
    
    bcm2835_init();
    bcm2835_gpio_fsel(gpio0, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(gpio1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(gpio2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_delay(100);
    
    return this;
}

Multiplexer* Multiplexer::addStateToQueue(uint8_t s0, uint8_t s1, uint8_t s2)
{
    #ifdef DEBUG
    std::cout << "[" << __func__ << "]" << std::endl;
    #endif

    states.emplace_back(s0, s1, s2);
    return this;
}

void Multiplexer::begin()
{
    #ifdef DEBUG
    std::cout << "[" << __func__ << "] MUX start working..." << std::endl;
    #endif
    this->setCurrentState(states.front()); // first state from vector
}

void Multiplexer::prevState()
{
    #ifdef DEBUG
    std::cout << "[" << __func__ << "]" << std::endl;
    #endif        
            
    static auto riter = states.rbegin();
    
    for(riter; riter != states.rend(); ++riter)
    {
        if(*riter == currentState) // find the start point (currentState)
            break;
    }
        
    if(riter != states.rend()-1) // if not the first state
        riter += 1;              //   get the next state
    else                         // if yes
        riter = states.rbegin(); //   back to the front
    
    setCurrentState(*riter);
}

void Multiplexer::nextState()
{
    #ifdef DEBUG
    std::cout << "[" << __func__ << "]" << std::endl;
    #endif

    static auto iter = states.begin();
     
    for(iter; iter != states.end(); ++iter)
    {
        if(*iter == currentState) // find the start point (currentState)
            break;
    }
    
    if(iter != states.end()-1) // if not the last state
        iter += 1;             //   get the next state
    else                       // if yes
        iter = states.begin(); //   back to the begin
    
    setCurrentState(*iter);
}

void Multiplexer::setCurrentState(State& s)
{ 
    currentState = s;
    
    #ifdef DEBUG
    std::cout << "(State& s)] Setting state " 
              << std::string(currentState) << std::endl;
    #endif

    bcm2835_gpio_write(gpio0, currentState.s0);
    bcm2835_gpio_write(gpio1, currentState.s1);
    bcm2835_gpio_write(gpio2, currentState.s2);
}

void Multiplexer::setCurrentState(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2)
{
    currentState = {_gpio0, _gpio1, _gpio2};
    
    #ifdef DEBUG
    std::cout << "Setting state " 
              << std::string(currentState) << std::endl;
    #endif

    bcm2835_gpio_write(gpio0, currentState.s0);
    bcm2835_gpio_write(gpio1, currentState.s1);
    bcm2835_gpio_write(gpio2, currentState.s2);
}