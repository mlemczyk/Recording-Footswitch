#include <Keyboard.h>
#include <Bounce2.h>

//A = pin 9
//B = pin 7
//C = pin 5
//D = pin 3

const int INTERVAL_MS = 25;

Bounce buttonA = Bounce(); 
Bounce buttonB = Bounce(); 
Bounce buttonC = Bounce(); 
Bounce buttonD = Bounce(); 

void setup() {  
  pinMode(9, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  buttonA.attach(9);
  buttonA.interval(INTERVAL_MS);
  buttonB.attach(7);
  buttonB.interval(INTERVAL_MS);
  buttonC.attach(5);
  buttonC.interval(INTERVAL_MS);
  buttonD.attach(3);
  buttonD.interval(INTERVAL_MS);

  // Initialize control over the keyboard
  Keyboard.begin();
}

void loop() {

  if ((buttonA.update()) && (buttonA.read() == LOW)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F12);
    delay(50); // Small delay to guarantee Windows registers the full combination
    Keyboard.release(KEY_F12);
    Keyboard.releaseAll();
  }
  if ((buttonB.update()) && (buttonB.read() == LOW)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F11);
    delay(50); // Small delay to guarantee Windows registers the full combination
    Keyboard.release(KEY_F11);
    Keyboard.releaseAll();
  }
  if ((buttonC.update()) && (buttonC.read() == LOW)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F10);
    delay(50); // Small delay to guarantee Windows registers the full combination
    Keyboard.release(KEY_F10);
    Keyboard.releaseAll();
  }
  if ((buttonD.update()) && (buttonD.read() == LOW)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F9);
    delay(50); // Small delay to guarantee Windows registers the full combination
    Keyboard.release(KEY_F9);
    Keyboard.releaseAll();
  }

}

