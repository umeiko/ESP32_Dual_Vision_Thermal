#pragma once

#include <Arduino.h>
#include "FT6336U.h"
#define TOUCH_SDA 23
#define TOUCH_SCL 18
#define TOUCH_VDD  19



FT6336U touch_dev = FT6336U(TOUCH_SDA, TOUCH_SCL, PinNotUsed, PinNotUsed);

typedef void (*touch_cb_t)(int x, int y);
touch_cb_t touch_cb = nullptr;

void i2c_pullup(){
    pinMode(TOUCH_VDD, OUTPUT);
    digitalWrite(TOUCH_VDD, LOW);
    delay(500);
}

void set_touch_cb(touch_cb_t cb){
    touch_cb = cb;
}

bool touch_init(){
    i2c_pullup();
    delay(500);
    if (!touch_dev.scan_device()){
        Serial.println("FT6336U not found!");
        return false;
    }else{
        Serial.println("FT6336U found!");
        touch_dev.begin();
        touch_dev._touch_init_done = true;
        return true;
    }
}

void gesture_handler(uint8_t gesture){
    static uint8_t last_gesture = Gestures::None;
    if (last_gesture != gesture){
        if (gesture == Gestures::SlideUp){ 
            Serial.println("[TOUCH] Slide Up");
        }else if (gesture == Gestures::SlideDown){
            Serial.println("[TOUCH] Slide Down");
        }
        else if(gesture == Gestures::LongPress){
            Serial.println("[TOUCH] Long Press");
        }else if (gesture == Gestures::SlideLeft){
            Serial.println("[TOUCH] Slide Left");
        }
        else if (gesture == Gestures::SlideRight){
            Serial.println("[TOUCH] Slide Right");
        }
    }
    last_gesture = gesture;
}

void touch_loop(){
    if (!touch_dev._touch_init_done){
        return;
    }
    static bool last_touched = false;
    touch_dev.update();
    bool touched = touch_dev.tp.touching;
    if( !touched ){
        last_touched = false;
    }else{
        int x = touch_dev.tp.y;
        int y = 240-touch_dev.tp.x;
        gesture_handler(touch_dev.tp.gesture);
        Serial.printf("[TOUCH](%d, %d) raw(tp.x=%d, tp.y=%d)\n", x, y, touch_dev.tp.x, touch_dev.tp.y);
        if (touch_cb != nullptr){
            touch_cb(x, y);
        }
    }
}

