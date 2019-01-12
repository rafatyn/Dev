#include <IRremote.h>
int RECV_PIN = 11;
int LED1 = 7;
int LED2 = 6;
int LED3 = 5;

long up = 0x00FF629D;
long dw = 0x00FFA857;
long lf = 0x00FF22DD;
long rh = 0x00FFC23D;
long ok = 0x00FF02FD;
long At = 0x00FF42BD;
long Ah = 0x00FF52AD;

long bt0 = 0x00FF4AB5;
long bt1 = 0x00FF6897;
long bt2 = 0x00FF9867;
long bt3 = 0x00FFB04F;
long bt4 = 0x00FF30CF;
long bt5 = 0x00FF18E7;
long bt6 = 0x00FF7A85;
long bt7 = 0x00FF10EF;
long bt8 = 0x00FF38C7;
long bt9 = 0x00FF5AA5;

IRrecv irrecv(RECV_PIN);
decode_results results;

void dump(decode_results *results) 
{
  if (results->decode_type == UNKNOWN) {
     Serial.println("Could not decode message");
  }else {
    Serial.print("Decoded: ");
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
}

void setup()
{
  pinMode(RECV_PIN, INPUT);   
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}
int on = 0;
unsigned long last = millis();

void loop() 
{
  if (irrecv.decode(&results)) 
   {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) {
       on = !on;
       digitalWrite(13, on ? HIGH : LOW);
       dump(&results);
    }
    if (results.value == bt1 ) {
       digitalWrite(LED1, HIGH);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
    } else if (results.value == bt2 ) {
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, HIGH);
       digitalWrite(LED3, LOW);
    } else if (results.value == bt3 ) {
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, HIGH);
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}
