const int sampleInterval = 10;
unsigned long prevSample = 0;

int potValue = 0;

unsigned long runningSum = 0;
float runningAvg = 0;
int i = 0;
int trigger = 0;

int beats = 0;
unsigned long lastBeatTime = 0;
unsigned long beatInterval = 0;
int BPM = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(6, OUTPUT);
  analogReference(EXTERNAL);
  // put your setup code here, to run once:
}

void loop() {
  unsigned long currSample = millis();
  if (currSample - prevSample >= sampleInterval) {
    digitalWrite(6, LOW);
    potValue = analogRead(A1);
    prevSample = currSample;
    runningSum += potValue;
    i++;
    if (i == 10) {
      runningAvg = runningSum / i;
      //Serial.println(runningSum);
      if (runningAvg >= 20 && trigger == 0) {
        digitalWrite(6, HIGH);
        trigger = 1;
        beats++;
        beatInterval += currSample - lastBeatTime;
        BPM = 60000 / (beatInterval/beats);
        lastBeatTime = currSample;
        if (beats >= 10) {
          beatInterval = 0;
          beats = 0;
        }
      } else if (runningAvg < 20) {
        trigger = 0;
      }
      Serial.println(BPM);
      runningSum = 0;
      i = 0;
    }
  }
  // put your main code here, to run repeatedly:
}
