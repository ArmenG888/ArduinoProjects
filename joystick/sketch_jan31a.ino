#define VRX_PIN  A0
#define VRY_PIN  A1

int xValue = 0;
int yValue = 0;

void setup() {
  Serial.begin(115200) ;
}

void loop() {
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  Serial.print(xValue);
  Serial.print(",");
  Serial.println(yValue);
  delay(1);
}
