const int sampleInterval = 10;
unsigned long previousMillis = 0;

unsigned long lastPeak = 0;

int potValue = 0;

long runningSum = 0;
float runningAvg = 0;
int i = 0;

int beats = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(6, OUTPUT);
  analogReference(EXTERNAL);
  // put your setup code here, to run once:
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= sampleInterval) {
    potValue = analogRead(A1);
    runningSum += potValue;
    i++;
    if (i == 10) {
      runningAvg = runningSum / i;
      Serial.println(runningSum);
      Serial.println(runningAvg);
      if (runningAvg >= 621) {
        digitalWrite(6, HIGH);
        lastPeak = currentMillis;
        beats++;
      } else if (runningAvg < 621) {
        digitalWrite(6, LOW);
      }
      i = 0;
      runningSum = 0;
      previousMillis = currentMillis;
    }
  }
  // put your main code here, to run repeatedly:
}
