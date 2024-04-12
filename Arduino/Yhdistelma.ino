int force = 0;
int forceThreshold = 100;
int distanceThreshold = 100;

const int echo = 7;
const int trigger = 8;
float dist;
bool personDetected = false;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}


void loop()
{
  force = analogRead(A0);
  if (force > forceThreshold) {
    Serial.println(-1);
  }
  
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  dist = pulseIn(echo, HIGH);
  dist = dist / 58;

  if (dist < distanceThreshold) {
    if (!personDetected) {
      Serial.println(1);
      personDetected = true;
    }
  } else {
    if (personDetected) {
      personDetected = false;
    }
  }
  delay(1000);
}
