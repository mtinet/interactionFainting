const int ping_L = 2;
const int ping_C = 3;
const int ping_R = 4;

long duration_L, duration_C, duration_R, cm_L, cm_C, cm_R;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, This is Interactive Fainting");
}

void loop() {
  //distance of ping_L
  pinMode(ping_L, OUTPUT);
  digitalWrite(ping_L, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_L, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_L, LOW);

  pinMode(ping_L, INPUT);

  duration_L = pulseIn(ping_L, HIGH);

  //distance of ping_C
  pinMode(ping_C, OUTPUT);
  digitalWrite(ping_C, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_C, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_C, LOW);

  pinMode(ping_C, INPUT);

  duration_C = pulseIn(ping_C, HIGH);

  //distance of ping_R
  pinMode(ping_R, OUTPUT);
  digitalWrite(ping_R, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_R, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_R, LOW);

  pinMode(ping_R, INPUT);

  duration_R = pulseIn(ping_R, HIGH);


  cm_L = microsecondsToCentimeters(duration_L);
  cm_C = microsecondsToCentimeters(duration_C);
  cm_R = microsecondsToCentimeters(duration_R);
      
  Serial.print(cm_L);
  Serial.print("cm  ");
  Serial.print(cm_C);
  Serial.print("cm  ");
  Serial.print(cm_R);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
