///////////////////////////////////////////////////////////////
//          Copyright Daan Westerhof 2019.                   //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          https://www.boost.org/LICENSE_1_0.txt)           //
///////////////////////////////////////////////////////////////

#ifndef PROJECT_USSR_H
#define PROJECT_USSR_H

#include "hwlib.hpp"
#include <vector>

namespace DSENSOR{

    /**
     * @class distance_sensor
     * @author Daan
     * @date 01/07/19
     * @file USSR.hpp
     * @brief distance_sensor
     * 
     * Abstract class of distance sensors.
     */
    
    class distance_sensor{
    public:
        virtual double get_distance();
        virtual int get_section(int max_distance, int sections, double distance, bool endless);
    };


    /**
     * @class UltraSonic
     * @author Daan
     * @date 01/07/19
     * @brief UltraSonic
     * This class can be used to controll a Ultra Sonic Sound Sensor that has a trigger and echo pin.
     */

    class UltraSonic : public distance_sensor {
        hwlib::pin_out & trigPin;
        hwlib::pin_in & echoPin;
        void write_low(hwlib::pin_out & pin);
        void write_high(hwlib::pin_out & pin);
    public:
            /**
             * @brief Constructor of UltraSonic
             * 
             * This is the constructor of the UltraSonic class
             * @param trigPin the pin wich tells the sensor to emit a pulse
             * @param echoPin the pin wich goes high when the pulse is recieved
             */
    
        UltraSonic(hwlib::pin_out &trigPin, hwlib::pin_in &echoPin) : trigPin(trigPin), echoPin(echoPin) {};
        
        
        /// \brief pin_pulse
        ///
        /// returns the time it took for a pin to go high
        uint_fast64_t pin_pulse();


        /// \brief get distance
        ///
        /// returns the distance read by the sensor in cm.
        double get_distance() override; 

        /// \brief get time
        ///
        /// returns the time it took for the sound pulse to return
        double get_time();

        /// \brief
        /// returns the disctance section of the object
        /// \details
        /// splits a distence in a given amount of sections,
        /// then returns the section in which the closest object is located
        /// the endless bool decides if it returns the max section if distance is bigger than max distence
        /// on false it returns -1 with the condtion that distance > max distance
        ///@param max_distance this parameter sets the maximum distence of the sections
        ///@param sections this parameter is the devider/sections of the max distance
        ///@param this is the value that the distance sensor has outputted
        ///@param endless this parameter decides that if the distance exeeds the maximum it returns -1 or max section.
        int get_section(int max_distance, int sections, double distance, bool endless) override;

    };
    
}


#endif //PROJECT_USSR_H
