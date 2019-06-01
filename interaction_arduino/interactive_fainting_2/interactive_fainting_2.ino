const int ping_L = 2;
const int ping_C = 3;
const int ping_R = 4;

long duration, cm;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, This is Interactive Fainting");
}

void loop() {
  Serial.print(getDistance(ping_L));
  Serial.print("cm  ");
  Serial.print(getDistance(ping_C));
  Serial.print("cm  ");
  Serial.print(getDistance(ping_R));
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long getDistance(int pingNum) {
  //distance of ping
  pinMode(pingNum, OUTPUT);
  digitalWrite(pingNum, LOW);
  delayMicroseconds(2);
  digitalWrite(pingNum, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingNum, LOW);

  pinMode(pingNum, INPUT);

  duration = pulseIn(pingNum, HIGH);

  cm = microsecondsToCentimeters(duration);
  
  return(cm);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
