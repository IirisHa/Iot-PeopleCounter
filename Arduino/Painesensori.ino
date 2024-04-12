int force = 0;
int threshold = 100;
int peopleCount = 0;


void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}


void loop()
{
  force = analogRead(A0);
  if (force > threshold) {
    Serial.println(force);
    peopleCount++;
    Serial.print("Henkilö kulki sensorin ohi. Ihmisiä yhteensä: ");
    Serial.println(peopleCount);
  }


  delay(1000);
}
