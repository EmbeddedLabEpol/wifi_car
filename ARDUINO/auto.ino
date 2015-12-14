#include <IRremote.h>
 
#include "engine.hpp"


#define przodu 0xE0E006F9
#define tylu   0xE0E08679
#define lewo   0xE0E0A659
#define prawo  0xE0E046B9
#define _STOP  0xE0E016E9

#define irPin 11


IRrecv irrecv(irPin);
decode_results results;

Engine motor;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.print ("dziala");
  motor.init(10,9,8,7,6,5);
}


void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("0x");
    Serial.println(results.value, HEX);
    delay(50);
    if (results.value == przodu)
    {
      
      motor.go_forward();
      motor.set_power(200);
    }
    else if (results.value == tylu)
    {
     motor.go_back();
     motor.set_power(200);
    }
    else if (results.value == _STOP)
    {
     motor.hard_stop();
    }
    else if (results.value == lewo)
    {
     motor.rotation_left();
     motor.set_power(200);
    }
    else if (results.value == prawo)
    {
      motor.rotation_right();
      motor.set_power(200);
    }



   
    irrecv.resume();
  }

  motor.timeout();
}
