#define in1 2 //L298n Motor Driver pins.
#define in2 4

void setup() {


  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);


}

void loop() {


  if (brightness == 255)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(2500);
    Serial.println("Curtain opened");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  else
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(2500);
    Serial.println("Curtain opened");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}
