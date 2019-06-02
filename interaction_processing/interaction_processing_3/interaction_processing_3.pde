import processing.serial.*;

Serial myPort;
PFont myFont;

int slideStep = 75;
PImage currentImage, nextImage;

int imgIndex = 0;

int slideOffset;

String[] fileList;

class FilterImages implements java.io.FilenameFilter {
  public boolean accept(File dir, String fname) {
    String[] extensions = {".png", ".jpeg", ".gif", ".tga", ".jpg"};
    
    for (int i = 0; i < extensions.length; i++) {
      if (fname.toLowerCase().endsWith(extensions[i])) {
        return true;
      }
    }
    return false;
  }
}

void loadFileNames() {
  java.io.File dir = new java.io.File(dataPath(""));
  fileList = dir.list(new FilterImages());
}



void setup() {
  // size(400,200);
  fullScreen();
  
  loadFileNames();
  
  imageMode(CENTER);
  
  print(dataPath("") + '/' + fileList[0]);
  currentImage = loadImage(dataPath("") + '/' + fileList[0]);
  currentImage.resize(0, height);
  
  //It need to check com port number or com port list
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  
  // String[] fontList = PFont.list();
  // printArray(fontList);
  myFont = createFont("Trebuchet MS Bold Italic", 48);
}


void draw() {
  background(0);
  image(currentImage, width/2, height/2);
  
  if (slideOffset != 0) {
    image(nextImage, slideOffset + width/2, height/2);
    if (slideOffset > 0) {
      slideOffset -= slideStep;      if (slideOffset < 0) {
        slideOffset = 0;
      }
    }
    if (slideOffset < 0) {
      slideOffset += slideStep;
      if (slideOffset > 0) {
        slideOffset = 0;
      }
    }
    if (slideOffset == 0) {
      currentImage = nextImage;
    }
  } else {
    if (myPort.available() > 0) {
      char inByte = myPort.readChar();
      print(inByte);
      
      if (inByte == 'F') {
        reverseSlide();
      }
      if (inByte == 'B') {
        advanceSlide();
      }
      
      nextImage = loadImage(dataPath("")  + '/' + fileList[imgIndex]);
      nextImage.resize(0, height);
      
    }
  }
}

void advanceSlide() {
  imgIndex++;
  if (imgIndex >= fileList.length) {
    imgIndex = 0;
  }
  slideOffset = width;
}

void reverseSlide() {
  imgIndex--;
  if (imgIndex < 0) {
    imgIndex = fileList.length - 1;
  }
  slideOffset = width * -1;
}
