// Casey's Traffic Light

int latchPin    = 8;   
int clockPin    = 12;
int dataPin     = 11;
int buttonInput = 2;
int RED         = 134;
int YELLOW      = 68;
int GREEN       = 34;
boolean trainPresent = false;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  trainRedCarGreen();
}

void loop() {
  int buttonState = digitalRead(buttonInput);
  if (buttonState == HIGH && trainPresent == false) { 
    trainApproaches();
    trainPresent = true;
    delay(10000);
  } else if (buttonState == HIGH && trainPresent == true) {
    trainPassedThru();
    trainPresent = false;
    delay(10000);
  }
}

void trainApproaches() {
  trainRedCarYellow();
  delay(5000);
  trainRedCarRed();
  delay(5000);
  trainGreenCarRed();
}

void trainPassedThru() {
  trainYellowCarRed();
  delay(10000);
  trainRedCarRed();
  delay(2000);
  trainRedCarGreen();
}

void trainRedCarGreen() {
  latchLo();
  shiftOut(GREEN);
  shiftOut(RED);
  latchHi();
}

void trainRedCarYellow() {
  latchLo();
  shiftOut(YELLOW);
  shiftOut(RED);
  latchHi();
}

void trainRedCarRed() {
  latchLo();
  shiftOut(RED);
  shiftOut(RED);
  latchHi();
}

void trainGreenCarRed() {
  latchLo();
  shiftOut(RED);
  shiftOut(GREEN);
  latchHi();
}

void trainYellowCarRed() {
  latchLo();
  shiftOut(RED);
  shiftOut(YELLOW);
  latchHi();
}

void latchLo() {
  digitalWrite(latchPin, LOW);
}

void latchHi() {
  digitalWrite(latchPin, HIGH);
}

void shiftOut(byte dataOut) {
  boolean pinState;
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  
  for (int i=0; i<=7; i++) {
    digitalWrite(clockPin, LOW);
    
    if (dataOut & (1<<i)) {
      pinState = HIGH;
    } else {
      pinState = LOW;
    }
        
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(clockPin, LOW);
}
