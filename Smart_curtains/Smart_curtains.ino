#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 9
#define in4 10

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(3, INPUT);
pinMode(11, INPUT);
}

void loop() {
  

  if (digitalRead(3)==HIGH)
  {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(4000); //задержка 5 секунд
  }

   if (digitalRead(3)==LOW)
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
   //задержка 5 секунд
  }
  
  //Back
  if (digitalRead(11)==HIGH)
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(4000);
  }
  
 
  if (digitalRead(11)==LOW)
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  }
}
