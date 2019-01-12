#include <Stepper.h>   
#define STEPS 100 
 
Stepper stepper(STEPS, 8, 9, 10, 11);
int previous = 0;  

void setup()
{
  stepper.setSpeed(30);  
  Serial.begin(9600);
}   

void loop()
{
  int val = analogRead(0);
  Serial.println(val - previous - 512);
  stepper.step(val - previous - 512);
  previous = val - 512;
  delay(50);
}
