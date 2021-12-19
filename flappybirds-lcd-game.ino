#include <Wire.h>
#include <LiquidCrystal_I2C.h>  

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define buttonPin  8

byte pipe[8] = {
  0b11111,
  0b11111,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

byte bird[8] = {
  0b00000,
  0b00110,
  0b10111,
  0b11110,
  0b11110,
  0b01100,
  0b00000,
  0b00000
};

byte hit[8] = {
  0b00000,
  0b11011,
  0b01110,
  0b00100,
  0b00100,
  0b01110,
  0b11011,
  0b00000
};

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

int pipes[16];
int birdY = 2;
int birdX = 7;
int score = 0;
int speedlvl = 400;

int life = 5; // number of lives

void setup() {
  lcd.backlight();  
  Serial.begin (9600);
  
  randomSeed(analogRead(0));
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  int i = 0;
  for (i = 0; i<16; i++) {
    pipes[i] = 0;
  }
 
  lcd.begin();

  lcd.createChar(0, pipe);
  lcd.createChar(1, bird);
  lcd.createChar(2, hit);
  lcd.createChar(3, heart);
}

void birdfly() {
  int buttonValue = digitalRead(buttonPin);
  int charId = 0;
  
  if (buttonValue == LOW) {
    birdY = 0;
    charId = 1;
  } else {
    birdY = 1;
    charId = 1;
    if (pipes[birdX] == 1) {
      charId = 2;
      life--;
      score--;
    }
  }
  
  lcd.setCursor(birdX, birdY);
  lcd.write((byte)charId);
}


void movePipes() {
  int dist = random(0, 2);
  // move the pipes along screen
  int i;
  for (i=1; i<16; i++) {
    pipes[i-1] = pipes[i];
  }
  
  if (dist == 1 && (pipes[16] == 2 || pipes[13] == 1)) {
      pipes[15] = 0;
  } else {
     pipes[15] = random(0, 2);
  }
    
  for (i = 0; i<16; i++) {
    if (pipes[i] != 0) {
      lcd.setCursor(i, 1);
      lcd.write((byte)0);
    }
  }

}


void showLives() {
  int i;
  for (i=0; i<life; i++) {
    lcd.setCursor(i, 0);
    lcd.write((byte)3);
  }
}

void showScore() {
  lcd.setCursor(13,0);
  lcd.print(score);
}

void loop() {
  lcd.clear();
  
  if (life > 0) {
    movePipes();
    birdfly();
    showLives();
    showScore();
    score++;
    speedlvl--;    
  } else {
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(3, 1);
    lcd.print("Score: ");
    lcd.print(score);
  }

  delay(speedlvl); // speed of pipes will decrease and move faster the more points you have

}
