// Ultraäänisensori
const int echo = 7;
const int trigger = 8;
int threshold = 100; // Arvo, jonka yläpuolella sensori havaitsee ihmisen
int peopleCount = 0; // Laskuri ihmisten määrälle
float dist;
bool personDetected = false; // Muuttuja, joka pitää kirjaa siitä, onko henkilö havaittu

void setup() {
  Serial.begin(9600); // Käynnistä sarjayhteys
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  dist = pulseIn(echo, HIGH);
  dist = dist / 58;

  // Tarkista, onko sensorin arvo alittanut kynnyksen
  if (dist < threshold) {
    // Jos sensorin arvo on ylittänyt kynnyksen, lisää laskuria yhdellä ja tulosta viesti
    if (!personDetected) {
      peopleCount++;
      Serial.print("Ihmisiä yhteensä: ");
      Serial.println(peopleCount);
      personDetected = true; // Aseta henkilön havaitsemisen tilaksi true
    }
  } else {
    // Jos sensorin arvo ei alittanut kynnystä, tarkista onko henkilö havaittu aiemmin ja aseta muuttuja sen mukaisesti
    if (personDetected) {
      personDetected = false; // Aseta henkilön havaitsemisen tilaksi false
    }
  }
  delay(1000);
}
