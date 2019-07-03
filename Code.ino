/*PWM Info
 * With both trims on 50% in radio control (steer CH1 and throtle CH2), neutral pulse lasts 1500 us -250us negative and 250us positive 
 * Positive pulse in steering indicates a right turn
 * Aux channel has 2 states, off which is aprox 1125us, and on which is 2000us
 * We will use <1500 for controller, else we listen to Pi
 * When controller is off both channels report neutral and aux reports off
 * Never use absolute values since these measurements aren't 100% correct, give around 50us of margin
 * 
 * A2 = Throttle
 * A3 = Steer
 * PD2 = D2 in board = Aux (Obey Pi or controller)
 * 
 * 12 = D12 in board = PI Throttle
 * 13 = D13 in board = PI Steer
 */
 
#include "motordriver_4wd.h"
#include "seeed_pwm.h"

void setup(){ 
    MOTOR.init(); //Init all pin
    pinMode(A3, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(PD2, INPUT_PULLUP);

    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
}

void loop(){
  int currentSpeed1=0, currentSpeed2=0, currentSteering=0, pinSpeed, pinDirection;
  unsigned char currentDirection1=0, currentDirection2=0;
  unsigned long pulseDuration=0, pulseDuration2;
  while(1){
    /*Check if we should listen to Pi or Controller*/
    pulseDuration = pulseIn(PD2, HIGH);
    if(pulseDuration < 1500){
      /*Listen to controller*/
      pinSpeed = A2;
      pinDirection = A3;
    }else{
      /*Listen to Pi*/
      pinSpeed = 12;
      pinDirection = 13;
    }
    /*Check pulse for speed*/
    pulseDuration = pulseIn(pinSpeed, HIGH);

    /*Parche para Pi*/
    if(pinSpeed==12){
      /*If new pulse difference is minimum don't adjust, this is needed since the Raspberys PWM isn't precise*/
      abs(pulseDuration2 - pulseDuration)<10 ? pulseDuration=pulseDuration2 : pulseDuration2=pulseDuration; 
    }
    
    if(pulseDuration<1450 && pulseDuration!=0){
      /*Going in reverse*/
      currentDirection1 = 0;
      currentSpeed1 = (int)((1450-pulseDuration)/2);/*Should give 0-100 range*/
    }else if(pulseDuration>1450 && pulseDuration<1550 && pulseDuration!=0){
      /*Stationary*/
      currentDirection1 = 0;
      currentSpeed1 = 0;
    }else if(pulseDuration>1550 && pulseDuration!=0){
      /*Going forward*/
      currentDirection1 = 1;
      currentSpeed1 = (int)((pulseDuration-1550)/2);/*Should give 0-100 range*/
    }
  
    /*For now, assume we're going straight*/
    currentSpeed2 = currentSpeed1;
    currentDirection2 = !currentDirection1;
  
    /*Check pulse for steer*/
    pulseDuration = pulseIn(pinDirection, HIGH);
  
    if(pulseDuration<1450 && pulseDuration!=0){
        /*Going left*/
        if(pulseDuration<1350){
          /*Tight left*/
          currentDirection1 = !currentDirection1;
          currentSpeed1 = (int)((currentSpeed1)*(1350-pulseDuration)/100);/*Should scale speed from 0 - 100% but in reverse, to aid with tight turns*/
        }else{
          currentSpeed1 = (int)((currentSpeed1)*(pulseDuration-1350)/100);/*Should scale speed from 0 - 100%*/
        }
    }else if(pulseDuration>1550){
      /*Going right*/
        if(pulseDuration>1650){
          /*Tight right*/
          currentDirection2 = !currentDirection2;
          currentSpeed2 = (int)((currentSpeed2)*(pulseDuration-1650)/100);/*Should scale speed from 0 - 100% but in reverse, to aid with tight turns*/
        }else{
          currentSpeed2 = (int)((currentSpeed2)*(1650-pulseDuration)/100);/*Should scale speed from 0 - 100%*/
        }
    }
  
    MOTOR.setSpeedDir1(currentSpeed1, currentDirection1);/*Side where ON/OFF switch is located*/
    MOTOR.setSpeedDir2(currentSpeed2, currentDirection2);/*Opposite side*/
    
  }
}
