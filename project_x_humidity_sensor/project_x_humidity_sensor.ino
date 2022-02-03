#define  SENSOR  12

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint16_t sensor = analogRead(SENSOR);    // Читаем данные с датчика,
  Serial.println(sensor);                  // выводим текущую влажность почвы из датчика в последовательный порт,
  delay(1000);

}
