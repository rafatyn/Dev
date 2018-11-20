void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(Serial.available())
  {
    int data=Serial.read();
    if(data=='A'){
      digitalWrite(LED_BUILTIN,HIGH);
    }else{
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
}
