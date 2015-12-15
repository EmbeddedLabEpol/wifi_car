#include <IRremote.h>
 
#include "engine.hpp"


#define przodu 0xE0E006F9
#define tylu   0xE0E08679
#define lewo    0xE0E0A659
#define prawo   0xE0E046B9
#define _STOP  0xE0E016E9
#define w_PRAWO 0xE0E0E01F
#define w_LEWO   0xE0E048B7

#define szybko 0xE0E008F7
#define wolno  0xE0E0D02F



#define irPin 11


IRrecv irrecv(irPin);
decode_results results;
volatile unsigned int speed_car = 0;
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
      Serial.println("przedu");
      motor.go_forward();
      motor.set_power(speed_car);
      Serial.println(speed_car);
    }

else if (results.value == szybko)
    {
      Serial.println("szybko");
      if (speed_car < 245){
      speed_car+=10;
      }
       Serial.println(speed_car);
       motor.set_run_time(millis());
    }

else if (results.value == wolno)
    {
      Serial.println("wolno");
     if ( speed_car > 20){
      speed_car-=10;
     }
     Serial.println(speed_car);
     motor.set_run_time(millis());
    }


else if (results.value == w_LEWO)
    {
      Serial.println("wlewo");
      motor.turn_left(speed_car/2);
      
    }

else if (results.value == w_PRAWO)
    {
      Serial.println("w_prawo");
     motor.turn_right(speed_car/2);
    }



    
    else if (results.value == tylu)
    {
      Serial.println("tylu");
     motor.go_back();
     motor.set_power(speed_car);
     Serial.println(speed_car);
    }
    else if (results.value == _STOP)
    {
      Serial.println("stop");
     motor.hard_stop();
    }
    else if (results.value == lewo)
    {
      Serial.println("lewo");
     motor.rotation_left();
     motor.set_power(250);
    }
    else if (results.value == prawo)
    {
      Serial.println("prawo");
      motor.rotation_right();
      motor.set_power(250);
    }



   
    irrecv.resume();
  }

  motor.timeout(2000);
}
