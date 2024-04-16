int count = 0;
int maxCount = 10;

int forceThreshold = 100;

const int echo = 7;
const int trigger = 8;
int distanceThreshold = 100;
bool personDetected = false;

const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

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
    analogWrite(RED_LED_PIN, 127);
    analogWrite(GREEN_LED_PIN, 127);
    analogWrite(BLUE_LED_PIN, 0);
  }
}

void loop()
{
  int force = analogRead(A0);
  if (force > forceThreshold && count > 0) {
    count--;
    Serial.println(count);
    color();
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
      color();
    }
  } else {
    if (personDetected) {
      personDetected = false;
    }
  }
  delay(1000);
}
