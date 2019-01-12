int pot=0;
int led1=7;
int led2=6;
int led3=5;
int val=0;

void setup()
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  val=analogRead(pot);
  Serial.println(val);
  analogWrite(led1,val/4);
  analogWrite(led2,val/4);
  analogWrite(led3,val/4);
  delay(10);
}
