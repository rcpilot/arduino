//www.elegoo.com
//2016.12.8

// Define Pins
#define RED 6
#define GREEN 5
#define BLUE 3

#define delayTime 50    // fading time between colors
#define blinkTime 500  // blink time
#define brightness 0.2
#define blink true

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);
}

// define variables
int redValue;
int greenValue;
int blueValue;

bool display = true;
int blinkTimer = 0;

int firstRGB[3] = {0, 0, 0};
int secondRGB[3] = {0, 0, 0};

// main loop
void loop() {
  for (int i = 0; i < 3; i++) {
    firstRGB[i] = secondRGB[i];
  }
  
  secondRGB[0] = random(255);
  secondRGB[1] = random(255);
  secondRGB[3] = random(255);
  Serial.println((String) firstRGB[0] + ", " + secondRGB[0]);

  fadeColor(firstRGB, secondRGB);
}

void fadeColor(int rgbFrom[3], int rgbTo[3]) {
  int redDiff = rgbTo[0] - rgbFrom[0];
  int greenDiff = rgbTo[1] - rgbFrom[1];
  int blueDiff = rgbTo[2] - rgbFrom[2];

  for (int i = 0; i < 255; i += 1) {
    float step = (float) i / 255;
    int redValue = (int) (step * redDiff) + rgbFrom[0];
    int greenValue = (int) (step * greenDiff) + rgbFrom[1];
    int blueValue = (int) (step * blueDiff) + rgbFrom[2];
    analogWrite(RED, redValue * brightness);
    analogWrite(GREEN, greenValue * brightness);
    analogWrite(BLUE, blueValue * brightness);

    delay(delayTime);
  }
}

void oldLoop() {

  redValue = 255;  // choose a value between 1 and 255 to change the color.
  greenValue = 0;
  blueValue = 0;

  // this is unnecessary as we've either turned on RED in SETUP
  // or in the previous loop ... regardless, this turns RED off
  // analogWrite(RED, 0);
  // delay(1000);

  for (int i = 0; i < 255; i += 1)  // fades out redValue bring greenValue full when i=255
  {
    redValue -= 1;
    greenValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(RED, 255 - redValue);
    // analogWrite(GREEN, 255 - greenValue);
    if (display || !blink) {
      analogWrite(RED, redValue * brightness);
      analogWrite(GREEN, greenValue * brightness);
    } else {
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
    }

    delay(delayTime);

    blinkTimer += delayTime;
    if (blinkTimer > blinkTime) {
      display = !display;
      blinkTimer = 0;
    }
  }

  redValue = 0;
  greenValue = 255;
  blueValue = 0;

  for (int i = 0; i < 255; i += 1)  // fades out greenValue bring blue full when i=255
  {
    greenValue -= 1;
    blueValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(GREEN, 255 - greenValue);
    // analogWrite(BLUE, 255 - blueValue);
    if (display || !blink) {
      analogWrite(GREEN, greenValue * brightness);
      analogWrite(BLUE, blueValue * brightness);
    } else {
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
    }

    delay(delayTime);

    blinkTimer += delayTime;
    if (blinkTimer > blinkTime) {
      blinkTimer = 0;
      display = !display;
    }
  }

  redValue = 0;
  greenValue = 0;
  blueValue = 255;

  for (int i = 0; i < 255; i += 1)  // fades out blue bring redValue full when i=255
  {
    // The following code has been rearranged to match the other two similar sections
    blueValue -= 1;
    redValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(BLUE, 255 - blueValue);
    // analogWrite(RED, 255 - redValue);
    if (display || !blink) {
      analogWrite(BLUE, blueValue * brightness);
      analogWrite(RED, redValue * brightness);
    } else {
      analogWrite(BLUE, 0);
      analogWrite(RED, 0);
    }

    delay(delayTime);

    blinkTimer += delayTime;
    if (blinkTimer > blinkTime) {
      blinkTimer = 0;
      display = !display;
    }
  }
}
