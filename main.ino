[시리얼 확인]

#define IR2 A2
#define IR4 A4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int IR2value = analogRead(IR2);
  int IR4value = analogRead(IR4);
  Serial.print("IR2value : ");
  Serial.println(IR2value);
  Serial.print("IR4value : ");
  Serial.println(IR4value);
  Serial.println("");
  delay(1000);
}