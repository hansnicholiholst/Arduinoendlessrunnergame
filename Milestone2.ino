#include <LiquidCrystal.h>
static int runningposition = 1; // for running animation
const int buttonPin = 2; // connecting pushbutton
int buttonState = 0; // variable for detecting if the pushbutton is pressed
int speed = 250; // starting speed(ms).  
int charPos = 1;
int score = 0;
LiquidCrystal lcd(11, 9, 6, 5, 4, 3); //setting starting character state
static int runningsprite11 = B00110;
static int runningsprite12 = B00110;
static int runningsprite13 = B00000;
static int runningsprite14 = B00110;
static int runningsprite15 = B01110;
static int runningsprite16 = B00110;
static int runningsprite17 = B00110;
static int runningsprite18 = B00110;
static int runningsprite01 = B00000;
static int runningsprite02 = B00000;
static int runningsprite03 = B00000;
static int runningsprite04 = B00000;
static int runningsprite05 = B00000;
static int runningsprite06 = B00000;
static int runningsprite07 = B00000;
static int runningsprite08 = B00000;
static int terrainleft = B00011;
static int terrain = B11111;
static int terrainright = B11000;
static int emptyterrain = B00000;
bool onGround = true; //to make sure the animations go smoothly, so the guy doesn't show the running animation while he's jumping
bool startjump = false; //for buton, making sure  jump starts when button pressed
bool onTerrain = false; //for more control of character, while on top of the terrain.
bool jumping = false; //to be able to control when to start certain animations
bool startfall = false;
bool falling = false;
int jumpingposition = 0; //for jumping animation
int fallingposition = 0; //for falling animation
int scrollPos = 0;
  byte leftTerrainbyte[8] = {
    terrainleft, terrainleft, terrainleft, terrainleft, terrainleft, terrainleft, terrainleft, terrainleft, 
  };
  byte Terrainbyte[8] = {
    terrain, terrain, terrain, terrain, terrain, terrain, terrain, terrain, 
  };
  byte rightTerrainbyte[8] {
    terrainright, terrainright, terrainright, terrainright, terrainright, terrainright, terrainright, terrainright, 
  };
  byte emptyTerrainbyte[8] {
    emptyterrain, emptyterrain, emptyterrain, emptyterrain, emptyterrain, emptyterrain, emptyterrain, emptyterrain,
  };
void setup() {
  lcd.begin(16, 2); //sets parameters for lcd
  pinMode(buttonPin, INPUT); //for pusbutton
  digitalWrite(buttonPin, HIGH); //for pushbutton
  lcd.createChar(3, leftTerrainbyte);
  lcd.createChar(4, Terrainbyte);
  lcd.createChar(5, rightTerrainbyte);
  lcd.setCursor(5, 0);
  lcd.write(byte(3));
  lcd.setCursor(6, 0);
  lcd.write(byte(4));
  lcd.setCursor(7, 0);
  lcd.write(byte(5));
  lcd.setCursor(0, 1);
  lcd.write(" ");
} 
void updateCharacter() {
    byte running1[8] = {
    runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
    }; //showing byte, to show character for bottom row
    byte running2[8] = {
    runningsprite01, runningsprite02, runningsprite03, runningsprite04, runningsprite05, runningsprite06, runningsprite07, runningsprite08, 
    }; //byte for top row
    lcd.createChar(1, running1);
    lcd.createChar(2, running2);
    lcd.setCursor(charPos, 1);
    lcd.write(byte(1));
    lcd.setCursor(charPos, 0);
    lcd.write(byte(2));
    lcd.setCursor(0, 1);
    lcd.print(" ");
}
void loop() {
  
  buttonState = digitalRead(buttonPin); // for pushbutton
  byte running1[8] = {
  runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
  }; //showing byte, to show character for bottom row
  byte running2[8] = {
  runningsprite01, runningsprite02, runningsprite03, runningsprite04, runningsprite05, runningsprite06, runningsprite07, runningsprite08, 
  }; //byte for top row
  if (scrollPos == 22) {
    lcd.setCursor(0, 0);
    lcd.write("                    ");
    lcd.setCursor(0, 1);
    lcd.write("                    ");
  }
  if (scrollPos == 2) {
    lcd.setCursor(20, 0);
    lcd.write("                    ");
    lcd.setCursor(20, 1);
    lcd.write("                    ");
  }
  scrollPos++;
  lcd.scrollDisplayLeft();
  charPos++;
  lcd.setCursor(charPos - 1, 0);
  lcd.write(" ");
  lcd.setCursor(charPos - 1, 1);
  lcd.write(" ");
//  lcd.setCursor(5, 1);
//  lcd.write(byte(3));
//  lcd.setCursor(6, 1);
//  lcd.write(byte(4));
//  lcd.setCursor(7, 1);
//  lcd.write(byte(5));
  lcd.setCursor(charPos, 1); //initially showing character
  lcd.write(byte(1));
  lcd.setCursor(charPos, 0);
  lcd.write(byte(2));
//  for (int ScrollCounter = 0; ScrollCounter < 40; ScrollCounter++) {
//    lcd.scrollDisplayLeft();
//    charPos++;
//    if (ScrollCounter == charPos) {
//      lcd.setCursor(ScrollCounter, 1);
//      lcd.write(" ");
//      lcd.setCursor(ScrollCounter, 0);
//      lcd.write(" ");
//    }
//  }
  if (buttonState == LOW) {
    startjump = true;
  } //detecting when the button is pressed
  if (startjump == true) {
    onGround = false;
    jumpingposition = 1;
    delayMicroseconds(speed);
    startjump = false;
    jumping = true;
  }
  if (jumpingposition == 3 && onGround == false && jumping == true && falling == false) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B01100;
    runningsprite04 = B01100;
    runningsprite05 = B00001;
    runningsprite06 = B01110;
    runningsprite07 = B11100;
    runningsprite08 = B01110;
    runningsprite11 = B11010;
    runningsprite12 = B00000;
    runningsprite13 = B00000;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    jumpingposition = 4;
  }
  if (jumpingposition == 4 && onGround == false && jumping == true && falling == false) {
    runningsprite01 = B00110;
    runningsprite02 = B00110;
    runningsprite03 = B10001;
    runningsprite04 = B01111;
    runningsprite05 = B00110;
    runningsprite06 = B01001;
    runningsprite07 = B01001;
    runningsprite08 = B00000;
    runningsprite11 = B00000;
    runningsprite12 = B00000;
    runningsprite13 = B00000;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed);
    jumpingposition = 0;
    fallingposition = 1; // TEMPORARY
    jumping = false;
    falling = true; //TEMPORARY
  }
  if (jumpingposition == 1 && jumping == true && onGround == false && falling == false) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B01100;
    runningsprite08 = B01100;
    runningsprite11 = B00001;
    runningsprite12 = B01110;
    runningsprite13 = B11100;
    runningsprite14 = B01110;
    runningsprite15 = B01010;
    runningsprite16 = B10000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    jumpingposition = 2;
  } //supposed to draw guy in first jumping animation, I have some indicators an
  if (jumpingposition == 2 && onGround == false && jumping == true && falling == false) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00110;
    runningsprite06 = B00110;
    runningsprite07 = B00001;
    runningsprite08 = B01111;
    runningsprite11 = B10110;
    runningsprite12 = B00111;
    runningsprite13 = B11001;
    runningsprite14 = B00001;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    jumpingposition = 3;
  }//second jumping animation, with indicator
//  if (onTerrain == false && onGround == false && jumping == false) {
//    startfall = ++;
//  }
//  if (startfall == 1) {
//    fallingposition = 1;
//    delayMicroseconds(speed);
//    falling = true;
//  }
  if (onTerrain == false && onGround == false && fallingposition == 3 && falling == true) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B00110;
    runningsprite08 = B00110;
    runningsprite11 = B10001;
    runningsprite12 = B01111;
    runningsprite13 = B00110;
    runningsprite14 = B01001;
    runningsprite15 = B01001;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    fallingposition = 4;
  }
  if (onTerrain == false && onGround == false && fallingposition == 4 && falling == true) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B00000;
    runningsprite08 = B00000;
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B10001;
    runningsprite14 = B01111;
    runningsprite15 = B00110;
    runningsprite16 = B01001;
    runningsprite17 = B01001;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    runningposition = 1;
    onGround = true;
    falling = false;
    fallingposition = 0;
  }
  if (onTerrain == false && onGround == false && fallingposition == 1 && falling == true) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00110;
    runningsprite04 = B00110;
    runningsprite05 = B10001;
    runningsprite06 = B01111;
    runningsprite07 = B00110;
    runningsprite08 = B01001;
    runningsprite11 = B01001;
    runningsprite12 = B00000;
    runningsprite13 = B00000;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    fallingposition = 2;
  }
  if (onTerrain == false && onGround == false && fallingposition == 2 && falling == true) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00110;
    runningsprite06 = B00110;
    runningsprite07 = B10001;
    runningsprite08 = B01111;
    runningsprite11 = B00110;
    runningsprite12 = B01001;
    runningsprite13 = B01001;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    updateCharacter();
    delay(speed/2);
    fallingposition = 3;
  }
  if (charPos == 41) {
    charPos = 1;
  }
  if (runningposition == 1 && onTerrain == true && onGround == false) {
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B00000;
    runningsprite14 = B00110;
    runningsprite15 = B01110;
    runningsprite16 = B00110;
    runningsprite17 = B00110;
    runningsprite18 = B00110;
    byte running1[8] = {
    runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
    }; //showing byte, to show character when on top of the obstacle.
    lcd.createChar(1, running1);
    lcd.setCursor(charPos, 0);
    lcd.write(byte(1));
//    delay(speed);
    runningposition = 2;
  }
  else if (runningposition == 2 && onTerrain == true && onGround == false) {
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B00001;
    runningsprite14 = B01111;
    runningsprite15 = B10110;
    runningsprite16 = B00111;
    runningsprite17 = B11001;
    runningsprite18 = B00001;
    byte running1[8] = {
    runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
    }; //showing byte, to show character when on top of the obstacle.
    lcd.createChar(1, running1);
    lcd.setCursor(charPos, 0);
    lcd.write(byte(1));
//    delay(speed);
    runningposition = 1;
  }
  if (runningposition == 1 && onGround == true && onTerrain == false) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B00000;
    runningsprite08 = B00000;
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B00000;
    runningsprite14 = B00110;
    runningsprite15 = B01110;
    runningsprite16 = B00110;
    runningsprite17 = B00110;
    runningsprite18 = B00110;
    updateCharacter();
//    delay(speed);
    runningposition = 2;
  }//first running animaiton, transition to second one
  else if (runningposition == 2 && onGround == true && onTerrain == false) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B00000;
    runningsprite08 = B00000;
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B00001;
    runningsprite14 = B01111;
    runningsprite15 = B10110;
    runningsprite16 = B00111;
    runningsprite17 = B11001;
    runningsprite18 = B00001;
    updateCharacter();
//    delay(speed);
    runningposition = 1;
  }//second running animation, transition back to first animation
  if(falling == false && jumping == false) {
    delay(speed*1.5);
  }
  if (charPos == 39) {
    lcd.setCursor(charPos-37, 0);
    lcd.write("Stage ");
    lcd.print(score+2);
    lcd.setCursor(charPos-1, 1);
    lcd.write("  ");
    charPos = 40;
    updateCharacter();
    score++;
  }
  if (charPos >= 40) {
    updateCharacter();
  }
  if (charPos == 40) {
    lcd.setCursor(39, 0);
    lcd.write(" ");
    lcd.scrollDisplayLeft();
    charPos = 0;
  }
}
