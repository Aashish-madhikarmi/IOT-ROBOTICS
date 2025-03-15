

void setup()  
 {  
  pinMode(2,OUTPUT);   // declare LED pins as output pins  
  pinMode(3,OUTPUT);  
  pinMode(4,OUTPUT);  
  pinMode(5,OUTPUT);
 }  
 
 void loop()  
 {  
  for(int i=0;i<16;i++)  // increment automatically from 0 to 15 
  {  
   int a=i%2;      // calculate LSB   
   int b=i/2 %2;     
   int c=i/4 %2;        
   int d=i/8 %2;  //claculate MSB
   digitalWrite(5,d);   //write MSB
   digitalWrite(4,c);   
   digitalWrite(3,b);    
   digitalWrite(2,a);  // write LSB  
   
   delay(1000);     // wait for a second  
  }  
 }  
