char str[16];
int light = 0;

void setup() {
  Serial.begin(9600);
}
  
void loop() {  
  light = 100 - (static_cast<float>(analogRead(0)) * 100 / 1024);
  sprintf(str, "L:%3d", light);
  Serial.println(str);
  delay(1000);
}
