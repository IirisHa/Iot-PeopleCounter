int count = 0;
int maxCount = 6;
bool lightShowBool = false;
int forceThreshold = 100;

const int echo = 7;
const int trigger = 8;
int distanceThreshold = 100;
bool personDetected = false;

const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

const int DISPLAY_TIME = 500;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  color();
}

void color()
{
  if (lightShowBool) {
    lightShow();
    return;
  }
  if (count == maxCount) {
    analogWrite(RED_LED_PIN, 255);
    analogWrite(GREEN_LED_PIN, 0);
    analogWrite(BLUE_LED_PIN, 0);
  }
  else if (count <= maxCount/2) {
    analogWrite(RED_LED_PIN, 0);
    analogWrite(GREEN_LED_PIN, 255);
    analogWrite(BLUE_LED_PIN, 0);
  }
  else {
    analogWrite(RED_LED_PIN, 255);
    analogWrite(GREEN_LED_PIN, 50);
    analogWrite(BLUE_LED_PIN, 0);
  }
}

void lightShow() {
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 0);
  analogWrite(BLUE_LED_PIN, 255);
  delay(DISPLAY_TIME);
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 0);
  analogWrite(BLUE_LED_PIN, 0);
  delay(DISPLAY_TIME);
}

void loop()
{
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if (data == "1") {
      lightShowBool = true;
    }
    else if (data == "0") {
      lightShowBool = false;
    }
  }
  int force = analogRead(A0);
  if (force > forceThreshold && count > 0) {
    count--;
    Serial.println(count);
  }
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float distance = pulseIn(echo, HIGH) / 58;

  if (distance < distanceThreshold) {
    if (!personDetected && count < maxCount) {
      count++;
      Serial.println(count);
      personDetected = true;
    }
  } else {
    if (personDetected) {
      personDetected = false;
    }
  }
  color();
  delay(1000);
}
