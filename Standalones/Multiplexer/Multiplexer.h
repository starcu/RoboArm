/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Multiplexer.h
 * Author: Lukas
 *
 * Description: 8bit mux/demux class 
 * 
 * Created on 1 listopada 2018, 23:11
 */

/*        CD74HC4051
 *      --------------
 *     |  o           |     
 *    -| Y4       Vcc |-
 *    -| Y6        Y2 |-
 *    -| C_IN/OUT  Y1 |-
 *    -| Y7        Y0 |-
 *    -| Y5        Y3 |-
 *    -| EN        S0 |-
 *    -| Vee       S1 |-
 *    -| GND       S2 |-
 *     |              | 
 *      --------------
 */
#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <bcm2835.h>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>

struct State
{
    State(uint8_t _s0, uint8_t _s1, uint8_t _s2) : s0(_s0), s1(_s1), s2(_s2) {}
    uint8_t s0;
    uint8_t s1;
    uint8_t s2;
    
    bool operator==(const State& in) const{
        if(this->s0 == in.s0 && this->s1 == in.s1 && this->s2 == in.s2)
            return true;
        return false;
    }
    
    bool operator!=(const State& in) const {
        if (this->s0 == in.s0 && this->s1 == in.s1 && this->s2 == in.s2)
            return false;
        return true;
    }
    
    explicit operator std::string() const{
        return std::string( "{ "
               + std::to_string(s0) + " " 
               + std::to_string(s1) + " " 
               + std::to_string(s2) + " }");
    }

    friend std::ostream& operator<< (std::ostream &out, const State &s);
};

class Multiplexer {
public:
    Multiplexer() : gpio0(-1), gpio1(-1), gpio2(-1), currentState(LOW,LOW,LOW) {}
    Multiplexer(const Multiplexer& orig) = delete;
    
    virtual ~Multiplexer() 
    {
        #ifdef VERBOSE
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "Setting all pins to high state." << std::endl;
        #endif

        // set common state for rpi gpios (all pins high)
        bcm2835_gpio_write(gpio0, HIGH);
        bcm2835_gpio_write(gpio1, HIGH);
        bcm2835_gpio_write(gpio2, HIGH);
    }
    
    Multiplexer* setCtrlPins(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2);
    Multiplexer* addStateToQueue(uint8_t s0, uint8_t s1, uint8_t s2);
    Multiplexer* addStateToQueue(State& s);
    
    void begin();
    
    void prevState();
    void prevStateWithDelay(uint32_t delayTime);
    void nextState();
    void nextStateWithDelay(uint32_t delayTime);

    void setCurrentState(State& s);
    void setCurrentState(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2);

    template <class F, class OBJ, class ...Args>
    void performForEveryState(F f, OBJ o, Args ...args);

    const State getCurrentState() const
    {
        return currentState;
    }
    
private:
    uint8_t gpio0, gpio1, gpio2; // common in/out choice pins
    std::vector<State> states;
    State currentState;
};

template <class F, class OBJ, class ...Args>
void Multiplexer::performForEveryState(F f, OBJ o, Args ...args)
{
    auto cs = this->getCurrentState();
    auto fnc = std::bind(f, o, std::forward<Args>(args)...);

    for(auto& s: states)
    {
        this->setCurrentState(s);
        fnc(args...);
    }

    this->setCurrentState(cs); // back to the state before loop
}

#endif /* MULTIPLEXER_H */

