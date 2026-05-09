#pragma once
#include <Arduino.h>
#include "screen.hpp"

void serial_start() {
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待串口连接
  }
  Serial.println("Serial communication initialized.");
}

// Supports 'h' for help menu
// Supports 'echo' for echoing input
// Supports 'screen' commands for display control
void serial_loop(){
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim(); // Remove leading and trailing whitespaces
        
        if (input == "h") {
            // ==== English Help Menu ====
            Serial.println("\r\n=========================================");
            Serial.println("          ESP32 Serial Console           ");
            Serial.println("=========================================");
            Serial.println("[ General Commands ]");
            Serial.println("  h                     - Show this help message");
            Serial.println("  echo <message>        - Echo the input message back to you");
            Serial.println("");
            Serial.println("[ Screen Control ]");
            Serial.println("  screen on             - Turn on the screen smoothly");
            Serial.println("  screen off            - Turn off the screen smoothly");
            Serial.println("  screen brightness <X> - Set brightness level (X: 5~255)");
            Serial.println("=========================================\r\n");
            
        } else if (input.startsWith("echo ")) {
            String message = input.substring(5); // Extract message after "echo "
            Serial.println("Echo: " + message);
            
        } else if (input.startsWith("screen ")) {  // Intercept screen control commands
            screen_cli(input);
            
        } else if (input.length() > 0) { // Prevent blank enter keys from triggering unknown command
            Serial.println("Unknown command: '" + input + "'. Type 'h' for help.");
        }
    }
}