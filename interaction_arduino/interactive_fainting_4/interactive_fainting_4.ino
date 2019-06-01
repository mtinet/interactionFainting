const int ping_L = 2;
const int ping_C = 3;
const int ping_R = 4;
const int LED_L = 7;
const int LED_C = 6;
const int LED_R = 5;

const int LED = 13;

const int maxD = 20;

long duration, cm;

int slide = 0;
boolean left = false;
boolean center = false;
boolean right = false;

long int lastTouch = -1;
int resetAfter = 2000;
int afterSlideDelay = 500;
int afterSlideOppositeDelay = 1500;

int SLIDELEFT_BEGIN = -1;
int SLIDELEFT_TO_CENTER = -2;

int SLIDENONE = 0;

int SLIDERIGHT_BEGIN = 1;
int SLIDERIGHT_TO_CENTER = 2;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello, This is Interactive Fainting");

  pinMode(LED_L, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_R, OUTPUT);
}


void loop() {
  left = ping(ping_L, LED_L);
  center = ping(ping_C, LED_C);
  right = ping(ping_R, LED_R);

  if (left || center || right) {
    lastTouch = millis();
  }

  if (millis()-lastTouch>resetAfter) {
    slide = 0;
    digitalWrite(LED, LOW);
    Serial.println("Reset slide and timer.");
  }

  if (slide >= SLIDENONE) {
    if ((left) && (!right))
      slide = SLIDERIGHT_BEGIN;
    if (center && (slide == SLIDERIGHT_BEGIN))
      slide = SLIDERIGHT_TO_CENTER;
    if (right && (slide == SLIDERIGHT_TO_CENTER))
      slideNow('R');
  }

  if (slide <= SLIDENONE) {
    if (right && (!left))
      slide = SLIDELEFT_BEGIN;
    if (center &&slide == SLIDELEFT_BEGIN)
      slide = SLIDELEFT_TO_CENTER;
    if (left && slide == SLIDELEFT_TO_CENTER) {
      slideNow('L');
    }
  }
  
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

void slideNow(char direction) {
  if ('R' == direction) 
    Serial.println("F");
  if ('L' == direction)
    Serial.println("B");
  digitalWrite(LED, HIGH);
  delay(afterSlideDelay);
  slide = SLIDENONE;
}
