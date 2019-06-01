import processing.serial.*;

Serial myPort;
PFont myFont;

void setup() {
  size(400,200);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  
  // String[] fontList = PFont.list();
  // printArray(fontList);
  myFont = createFont("Trebuchet MS Bold Italic", 48);
  
}

void draw() {
  background(0);
  textFont(myFont);
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

  }
}
