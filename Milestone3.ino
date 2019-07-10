#include <LiquidCrystal.h>
static int runningposition = 1; // for running animation
const int buttonPin = 2; // connecting pushbutton
int buttonState = 0; // variable for detecting if the pushbutton is pressed
int startingspeed = 400; // starting speed(ms).  
int charPos = 1;
int scrollhelp = 2;
int score = 0;
int scoredigits = 1;
int charHeight = 1;
int speed = 400; // variable for how fast the terrain moves, constantly decreasing, making game faster
int blockonelength = random(6);
int blockoneheight = 1;
int blockonespacing = random(2);
int blocktwolength = random(6);
int blocktwospacing = random(2);
int blockthreelength = random(6);
int blockthreespacing = random(2);
int blockfourlength = random(6);
int blocktwoheight = random(2);
int blockthreeheight = random(2);
int blockfourheight = random(2);
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
bool onLower = true;
bool onUpper = false;
bool startfall = false;
bool falling = false;
bool alive = false;
bool collided = false;

int jumpingposition = 0; //for jumping animation
int fallingposition = 0; //for falling animation
  byte leftTerrainbyte[8] = {
    B00011, B00011, B00011, B00011, B00011, B00011, B00011, B00011,
  };
  byte Terrainbyte[8] = {
    B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111, 
  };
  byte rightTerrainbyte[8] {
    B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000,
  };
void updateCharacter() {
    if(onLower == true) {
    byte running1[8] = {
    runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
    }; //showing byte, to show character for bottom row
    lcd.createChar(1, running1);
    lcd.setCursor(charPos, 1);
    lcd.write(byte(1));
    }
    if(onUpper == true) {
    byte running2[8] = {
    runningsprite01, runningsprite02, runningsprite03, runningsprite04, runningsprite05, runningsprite06, runningsprite07, runningsprite08, 
    }; //byte for top row
    lcd.createChar(2, running2);
    lcd.setCursor(charPos, 0);
    lcd.write(byte(2));
    }
}
void generateTerrain() {
  blockonelength = random(6);
  blockonespacing = random(2);
  blocktwolength = random(6);
  blocktwoheight = random(2);
  blocktwospacing = random(2);
  blockthreelength = random(6);
  blockthreeheight = random(2);
  blockthreespacing = random(2);
  blockfourlength = random(6);
  blockfourheight = random(2);
  lcd.setCursor(14, blockoneheight);
  lcd.write(byte(3));
  for (int i = 0; i < blockonelength; i++) {
    lcd.write(byte(4));
  }
  lcd.write(byte(5));
  lcd.setCursor((20+blockonelength+blockonespacing), blocktwoheight);
  lcd.write(byte(3));
  for (int i = 0; i < blocktwolength; i++) {
    lcd.write(byte(4));
  }
  lcd.write(byte(5));
  if ((26+blockonelength+blocktwolength+blockthreelength) > 38) {
    blockthreelength = 2;   // might have to change up this value and for the if statement.
  }
  lcd.setCursor((26+blockonelength+blockonespacing+blocktwolength+blocktwospacing), blockthreeheight);
  lcd.write(byte(3));
  for (int i = 0; i < blockthreelength; i++) {
    lcd.write(byte(4));
  }
  lcd.write(byte(5));
  if ((32 + blockonelength+blockonespacing+blocktwolength+blocktwospacing+blockthreelength+blockthreespacing+blockfourlength) < 38) {
    lcd.setCursor(32+blockonelength+blockonespacing+blocktwolength+blocktwospacing+blockthreelength+blockthreespacing, blockfourheight);
    lcd.write(byte(3));
    for (int i = 0; i < blockfourlength; i++) {
      lcd.write(byte(4));
    }
    lcd.write(byte(5));
  } else {
    blockfourheight = 10;
  }
}
void detectCollision() {
  if (14<= charPos && charPos <= (16+blockonelength) && onLower == false && blockoneheight == 1 ||
  (20+blockonelength+blockonespacing) <= charPos && charPos <= (22+blockonelength+blockonespacing+blocktwolength) && (onLower == false && blocktwoheight == 1) ||
  (26+blockonelength+blockonespacing+blocktwospacing+blocktwolength) <= charPos && charPos <= (28+blockonelength+blockonespacing+blocktwolength+blocktwospacing+blockthreelength) && (onLower == false && blockthreeheight == 1) ||
  (32+blockonelength+blockonespacing+blocktwospacing+blockthreespacing+blocktwolength+blockthreelength) <= charPos && charPos <= (34+blockonelength+blockonespacing+blocktwolength+blocktwospacing+blockthreelength+blockthreespacing+blockfourlength) && (onLower == false && blockfourheight == 1)) {
    onTerrain = true;
    } else if(jumpingposition == 4) {
      falling = true; fallingposition = 1;
    }
    else if ((onLower == false) && ((charPos == 17+blockonelength) || (charPos == 23+blockonelength+blockonespacing+blocktwolength) ||
    (charPos == 29+blockonelength+blockonespacing+blocktwospacing+blocktwolength+blockthreelength) || (charPos == 35+blockonelength+blockonespacing+blocktwospacing+blockthreespacing+blocktwolength+blockthreelength+blockfourlength || charPos == 0))) {
      falling = true;
      fallingposition = 2;
      onTerrain = false;
      onGround = false;
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
      onLower = true;
      updateCharacter();
    }
  else if (14 <= charPos && charPos <= (16+blockonelength) && ((onLower == true && blockoneheight == 1) || (onUpper == true && blockoneheight == 0)) || 
  (20+blockonelength+blockonespacing) <= charPos && charPos <= (22+blockonelength+blockonespacing+blocktwolength) && ((onLower == true && blocktwoheight == 1) || (onUpper == true && blocktwoheight == 0)) || 
  (26+blockonelength+blockonespacing+blocktwospacing+blocktwolength) <= charPos && charPos <= (28+blockonelength+blockonespacing+blocktwospacing+blocktwolength+blockthreelength) && ((onLower == true && blockthreeheight == 1) || (onUpper == true && blockthreeheight == 0)) ||
  (32+blockonelength+blockonespacing+blocktwospacing+blockthreespacing+blocktwolength+blockthreelength) <= charPos && charPos <= (34+blockonelength+blockonespacing+blocktwospacing+blockthreespacing+blocktwolength+blockthreelength+blockfourlength) 
  && ((onLower == true && blockfourheight == 1) || (onUpper == true && blockfourheight == 0)) ) {
    collided = true;
    alive = false;
  }
}
void setup() {
//  alive = false;
//  collided = true;
  lcd.begin(16, 2); //sets parameters for lcd
  pinMode(buttonPin, INPUT); //for pusbutton
  digitalWrite(buttonPin, HIGH); //for pushbutton
  randomSeed(analogRead(0));
  lcd.createChar(3, leftTerrainbyte);
  lcd.createChar(4, Terrainbyte);
  lcd.createChar(5, rightTerrainbyte);
  Serial.begin(1200);
  lcd.setCursor(2, 0);
  lcd.write("Press button");
  lcd.setCursor(4, 1);
  lcd.write("to start");
} 
void loop() {
  buttonState = digitalRead(buttonPin); // for pushbutton
  byte running1[8] = {
  runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
  }; //showing byte, to show character for bottom row
  byte running2[8] = {
  runningsprite01, runningsprite02, runningsprite03, runningsprite04, runningsprite05, runningsprite06, runningsprite07, runningsprite08, 
  }; //byte for top row
  if (alive == true) {
  lcd.scrollDisplayLeft();
  charPos++;
  lcd.setCursor(charPos - 1, 0);
  lcd.write(" ");
  lcd.setCursor(charPos - 1, 1);
  lcd.write(" ");
  lcd.setCursor(charPos, 1); //initially showing character
  lcd.write(byte(1));
  lcd.setCursor(charPos, 0);
  lcd.write(byte(2));
  if (buttonState == LOW && onGround == true) {
    startjump = true;
  } //detecting when the button is pressed
  if (startjump == true) {
    onGround = false;
    jumpingposition = 1;
    delayMicroseconds(1);
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
    onUpper = true;
    onLower = true;
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
    onUpper = true;
    onLower = false;
    detectCollision();
    delay(speed*(1/2));
    jumpingposition = 0;
    jumping = false;
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
    onUpper = true;
    onLower = true;
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
    onUpper = true;
    onLower = true;
    updateCharacter();
    delay(speed/2);
    jumpingposition = 3;
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
    onUpper = true;
    onLower = true;
    updateCharacter();
    delay(speed/4);
    fallingposition = 2;
  }
  if (onTerrain == false && onGround == false && fallingposition == 2 && falling == true) {
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00110;
    runningsprite06 = B00110;
    runningsprite07 = B00001;
    runningsprite08 = B01111;
    runningsprite11 = B10110;
    runningsprite12 = B01001;
    runningsprite13 = B01001;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    onUpper = true;
    onLower = true;
    updateCharacter();
    delay(speed/4);
    fallingposition = 3;
  }
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
    onUpper = true;
    onLower = true;
    updateCharacter();
    delay(speed/4);
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
    onUpper = false;
    onLower = true;
    delay(speed/4);
    runningposition = 1;
    onGround = true;
    falling = false;
    fallingposition = 0;
  }
  if (runningposition == 1 && onTerrain == true && onGround == false) {
    runningsprite01 = B00110;
    runningsprite02 = B00110;
    runningsprite03 = B00000;
    runningsprite04 = B00110;
    runningsprite05 = B01110;
    runningsprite06 = B00110;
    runningsprite07 = B00110;
    runningsprite08 = B00110;
    runningsprite11 = B00000;
    runningsprite12 = B00000;
    runningsprite13 = B00000;
    runningsprite14 = B00000;
    runningsprite15 = B00000;
    runningsprite16 = B00000;
    runningsprite17 = B00000;
    runningsprite18 = B00000;
    runningposition = 2;
    onUpper = true;
    onLower = false;
    updateCharacter();
    detectCollision();
    delay(speed);
  }
  else if (runningposition == 2 && onTerrain == true && onGround == false) {
    runningsprite01 = B00110;
    runningsprite02 = B00110;
    runningsprite03 = B00001;
    runningsprite04 = B01111;
    runningsprite05 = B10110;
    runningsprite06 = B00111;
    runningsprite07 = B11001;
    runningsprite08 = B00001;
    runningposition = 1;
    onUpper = true;
    onLower = false;
    updateCharacter();
    detectCollision();
    delay(speed);
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
    onUpper = false;
    onLower = true;
    updateCharacter();
    runningposition = 2;
    delay(speed);
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
    onUpper = false;
    onLower = true;
    updateCharacter();
    runningposition = 1;
    delay(speed);
  }//second running animation, transition back to first animation
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
    updateCharacter();
    generateTerrain();
  }
  if (score >= 10) {
    scoredigits = 2;
  }
  if (score >= 100) {
    scoredigits = 3;
  }
  speed = startingspeed - 2*score;
  if (speed <= 100) {
    speed = 100;
  }
  detectCollision();
  Serial.println(speed);
  }
if (alive == false) {
  if (collided == true) {
    collided = false;
    alive = false;
    delay(2000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write("You passed");
    lcd.setCursor(3, 1);
    lcd.print(score);
    lcd.write(" stages");
    for (int i = 0; i <=10; i++) {
      delay(1000);
    }
    buttonState = digitalRead(buttonPin);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.write("Press button");
    lcd.setCursor(4, 1);
    lcd.write("to start");
    delay(500);
  }
  if (buttonState == LOW) {
//    delay(50);
    alive = true;
    charPos = 1;
    speed = 250;
    runningposition = 1;
    score = 0;
    scoredigits = 1;
    charHeight = 1;
    blockonelength = random(6);
    blockoneheight = 1;
    blocktwolength = random(6);
    blocktwoheight = random(2);
    blockthreelength = random(6);
    blockthreeheight = random(2);
    blockfourheight = random(2);
    blockfourlength = random(6);
    onGround = true;
    startjump = false;
    onTerrain = false;
    jumping = false;
    onLower = true;
    onUpper = true;
    startfall = false;
    falling = false;
    jumpingposition = 0;
    fallingposition = 0;
    delayMicroseconds(20);
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.write("Stage 1");
    generateTerrain();
    runningsprite11 = B00110;
    runningsprite12 = B00110;
    runningsprite13 = B00000;
    runningsprite14 = B00110;
    runningsprite15 = B01110;
    runningsprite16 = B00110;
    runningsprite17 = B00110;
    runningsprite18 = B00110;
    runningsprite01 = B00000;
    runningsprite02 = B00000;
    runningsprite03 = B00000;
    runningsprite04 = B00000;
    runningsprite05 = B00000;
    runningsprite06 = B00000;
    runningsprite07 = B00000;
    runningsprite08 = B00000;
    byte running1[8] = {
    runningsprite11, runningsprite12, runningsprite13, runningsprite14, runningsprite15, runningsprite16, runningsprite17, runningsprite18,
    }; //showing byte, to show character for bottom row
    byte running2[8] = {
    runningsprite01, runningsprite02, runningsprite03, runningsprite04, runningsprite05, runningsprite06, runningsprite07, runningsprite08, 
    }; //byte for top row
    updateCharacter();
    onUpper = false;
  }
  }
}
