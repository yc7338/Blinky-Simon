const int PLAY_LIMIT = 3;
int colors[PLAY_LIMIT];
int inputColors[PLAY_LIMIT];
int colorCount = 0;
int inputCount = 0;
bool gameStart = false;
bool displayLights = false;
bool win = false;

bool redPressed = false;
bool orangePressed = false;
bool yellowPressed = false;
bool greenPressed = false;

int redPin = 2;
int orangePin = 3;
int yellowPin = 4;
int greenPin = 5;

int redButton = 6;
int orangeButton = 7;
int yellowButton = 8;
int greenButton = 9;
int startButton = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(redPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(redButton, INPUT);
  pinMode(orangeButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(startButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //val = analogRead(knockSensor);
  //Serial.println(val);
  //if (val >= THRESHOLD){
  //  Serial.println("Knock");
  //}

  if (gameStart) {
    if (colorCount == 0) {
      colors[0] = random(2, 6);
      colorCount = 1;
      inputCount = 0;
    }
    if (!displayLights) {
      offAllLED();
      for (int i = 0; i < colorCount; i++) {
        digitalWrite(colors[i], HIGH);
        delay(500);
        digitalWrite(colors[i], LOW);
        delay(300);
      }
      displayLights = true;
    }
    else {
      checkButtons();
      if (inputCount == colorCount) {
        bool correct = true;

        for (int i = 0; i < colorCount; i++) {
          if (inputColors[i] != colors[i]) {
            correct = false;
          }
          Serial.println("correctness");
        }

        inputCount = 0;

        if (correct) {
          Serial.print("correct");
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, HIGH);
          }
          delay(100);
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, LOW);
          }
          delay(100);
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, HIGH);
          }
          delay(100);
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, LOW);
          }
          delay(100);
          if (colorCount < PLAY_LIMIT) {
            colors[colorCount] = random(2, 6);
            colorCount++;
            displayLights = false;
          }
          else
          {
            win = true;
            gameStart = false;
          }
        }
        else {
          Serial.print("wrong");
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, HIGH);
          }
          delay(1000);
          for (int i = 2; i < 6; i++) {
            digitalWrite(i, LOW);
          }
          delay(500);
          displayLights = false;
        }
      }
    }
  }
  else if (win) {
    showWinning();
  }
  else
  {
    checkGameStart();
  }
}

void checkGameStart() {
  offAllLED();
  for (int i = 2; i < 6; i++) {
    if (digitalRead(startButton) == HIGH) {
      gameStart = true;
      onAllLED();
      delay (1000);
      offAllLED();
      delay(500);
      return;
    }
    digitalWrite(i, HIGH);
    delay(300);

    if (digitalRead(startButton) == HIGH) {
      gameStart = true;
      onAllLED();
      delay(1000);
      offAllLED();
      delay(500);
      return;
    }
    digitalWrite(i, LOW);
  }
}

void checkButtons() {
  if (digitalRead(redButton) == HIGH) {
    redPressed = true;
    digitalWrite(redPin, HIGH);
  }
  else {
    digitalWrite(redPin, LOW);
    if (redPressed == true) {
      inputColors[inputCount] = redPin;
      inputCount++;
      Serial.println("RED");
      redPressed = false;
      return;
    }
    redPressed = false;
  }

  if (digitalRead(orangeButton) == HIGH)
  {
    orangePressed = true;
    digitalWrite(orangePin, HIGH);
  }
  else {
    digitalWrite(orangePin, LOW);
    if (orangePressed == true) {
      inputColors[inputCount] = orangePin;
      inputCount++;
      Serial.println("ORANGE");
      orangePressed = false;
      return;
    }
    orangePressed = false;
  }

  if (digitalRead(yellowButton) == HIGH)
  {
    yellowPressed = true;
    digitalWrite(yellowPin, HIGH);
  }
  else {
    digitalWrite(yellowPin, LOW);
    if (yellowPressed == true) {
      inputColors[inputCount] = yellowPin;
      inputCount++;
      Serial.println("YELLOW");
      yellowPressed = false;
      return;
    }
    yellowPressed = false;
  }

  if (digitalRead(greenButton) == HIGH)
  {
    greenPressed = true;
    digitalWrite(greenPin, HIGH);
  }
  else {
    digitalWrite(greenPin, LOW);
    if (greenPressed == true) {
      inputColors[inputCount] = greenPin;
      inputCount++;
      Serial.println("GREEN");
      greenPressed = false;

      return;
    }
    greenPressed = false;
  }
}

void showWinning()
{
  offAllLED();
  for (int i = 2; i < 6; i++) {
    if (digitalRead(startButton) == HIGH) {
      gameStart = true;
      displayLights = false;
      inputCount = 0;
      colorCount = 0;
      onAllLED();
      delay(1000);
      offAllLED();
      delay(500);
      return;
    }
    digitalWrite(i, HIGH);
    delay(100);

    if (digitalRead(startButton) == HIGH) {
      gameStart = true;
      displayLights = false;
      inputCount = 0;
      colorCount = 0;
      onAllLED();
      delay(1000);
      offAllLED();
      delay(500);
      return;
    }
    digitalWrite(i, LOW);
  }
}

void offAllLED() {
  digitalWrite(redPin, LOW);
  digitalWrite(orangePin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

void onAllLED() {
  digitalWrite(redPin, HIGH);
  digitalWrite(orangePin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
}
