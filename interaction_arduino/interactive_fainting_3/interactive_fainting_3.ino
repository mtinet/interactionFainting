const int ping_L = 2;
const int ping_C = 3;
const int ping_R = 4;
const int LED_L = 7;
const int LED_C = 6;
const int LED_R = 5;

const int maxD = 20;

long duration, cm;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, This is Interactive Fainting");

  pinMode(LED_L, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_R, OUTPUT);
}

void loop() {
  ping(ping_L, LED_L);
  ping(ping_C, LED_C);
  ping(ping_R, LED_R);

  delay(50);
}

boolean ping(int pingPin, int ledPin) {
  int d = getDistance(pingPin);
  boolean pinActivated = false;
  if (d < maxD) {
    digitalWrite(ledPin, HIGH);
    pinActivated = true;
    Serial.print("Now Activated ");
    Serial.println(ledPin);
  } else {
    digitalWrite(ledPin, LOW);
    pinActivated = false;
  }
  return pinActivated;
}

long getDistance(int pingPin) {
  //distance of ping
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);

  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  
  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
