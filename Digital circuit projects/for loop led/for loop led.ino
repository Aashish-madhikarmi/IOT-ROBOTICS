
void setup()
{
pinMode(2, OUTPUT); // pin 2 to 5 is set as output 
pinMode(3, OUTPUT); 
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
}
 
 void loop()
{
digitalWrite(2, HIGH);//LED 1 is ON
delay(500); // wait half a second
digitalWrite(2, LOW); // Turn LED 1 off
digitalWrite(3, HIGH); // and repeat for LED 2 to 5
delay(500);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
delay(500);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
delay(500);
digitalWrite(5, LOW);
}
 
