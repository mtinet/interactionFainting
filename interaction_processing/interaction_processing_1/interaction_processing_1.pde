import processing.serial.*;

Serial myPort;
PFont mono;

void setup() {
  size(400,200);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  
  mono = createFont("HanSantteutDotumBold-48.vlw", 32);
  
}

void draw() {
  background(0);
  textFont(mono);
  textSize(24);
  textAlign(CENTER);
  fill(255);
  text("Hello, This is InteractionFainting", 200, 50);
  if (myPort.available() > 0) {
    char inByte = myPort.readChar();
    print(inByte);
    fill(255,255,0);
    textSize(48);
    text(inByte, 200, 150);
    delay(500);
    fill(0,0,0);
  }
}
