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

/*         HCT4051
 *      --------------
 *     |  o           |     
 *    -| O4       Vcc |-
 *    -| O6        O2 |-
 *    -| C_IN/OUT  O1 |-
 *    -| O7        O0 |-
 *    -| O5        O3 |-
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
        #ifdef DEBUG
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "Setting all pins to high state." << std::endl;
        #endif

        // set common state for rpi (all pins high)
        bcm2835_gpio_write(gpio0, HIGH);
        bcm2835_gpio_write(gpio1, HIGH);
        bcm2835_gpio_write(gpio2, HIGH);
    }
    
    Multiplexer* setCtrlPins(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2);
    Multiplexer* addStateToQueue(uint8_t s0, uint8_t s1, uint8_t s2);
    
    void begin();
    
    void prevState();
    void nextState(); 
    
    void setCurrentState(State& s);
    void setCurrentState(uint8_t _gpio0, uint8_t _gpio1, uint8_t _gpio2);

    const State getCurrentState() const
    {
        return currentState;
    }
    
private:
    uint8_t gpio0, gpio1, gpio2; // common in/out choice pins
    std::vector<State> states;
    State currentState;
};

#endif /* MULTIPLEXER_H */

