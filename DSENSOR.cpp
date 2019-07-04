#include <utility>

//
// Created by User on 2-5-2019.
//
#include "DSENSOR.hpp"

namespace DSENSOR{

void UltraSonic::write_low(hwlib::pin_out & pin){
    pin.write(false);
    pin.flush();
}

void UltraSonic::write_high(hwlib::pin_out & pin){
    pin.write(true);
    pin.flush();
}


int UltraSonic::get_section(int max_distance, int sections, double distance, bool endless){
    int section = max_distance / sections;
    if(distance >= max_distance){
        if(endless){
            return sections;
        }else{
            return -1;
        }
    }if((distance >= (max_distance - section)) && distance < max_distance){
        return sections;
    } else{
        return UltraSonic::get_section(max_distance - section, sections - 1, distance,  endless);
    }
}

double UltraSonic::get_distance(){
    double duration = UltraSonic::get_time();
    double distance = (duration/2)*0.0343;
    return distance;
}



double UltraSonic::get_time(){
    write_low(trigPin);
    write_high(trigPin);
    hwlib::wait_us(10);
    write_low(trigPin);

    double duration = UltraSonic::pin_pulse();
    return duration;
}



uint_fast64_t UltraSonic::pin_pulse(){
    while(!echoPin.read()){};
    uint_fast64_t start_time = hwlib::now_us();
    while(echoPin.read()){
    };
    uint_fast64_t end_time = hwlib::now_us();
    return end_time - start_time;
}

}
