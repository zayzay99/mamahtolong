#include <Keypad.h>
#include <Servo.h>

// Define the servo motor pin
const int servoPin = 9;

// Create servo object
Servo lockServo;

// Define the keypad
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7};     // Connect to the column pinouts of the keypad

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Set your PIN here
const String correctPIN = "1234";
String inputPIN = "";

bool isLocked = true;

void setup(){
  lockServo.attach(servoPin);
  Serial.begin(9600);
  lock();  // Start locked
  Serial.println("Smart Lock System Ready");
  Serial.println("Enter PIN followed by # to unlock");
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    if (key == '#'){
      // Check the input PIN
      if (inputPIN == correctPIN){
        Serial.println("PIN correct. Unlocking...");
        unlock();
      } else {
        Serial.println("Incorrect PIN!");
        lock();
      }
      inputPIN = ""; // clear input after entry
    }
    else if (key == '*'){
      // Clear input
      inputPIN = "";
      Serial.println("Input cleared");
    }
    else {
      // Append pressed key to input
      inputPIN += key;
      Serial.print("*"); // show masked input
    }
  }
}

// Function to lock the door
void lock(){
  lockServo.write(0);  // Assuming 0 is locked position
  isLocked = true;
  Serial.println("Locked");
}

// Function to unlock the door
void unlock(){
  lockServo.write(90); // Assuming 90 is unlocked position
  isLocked = false;
  Serial.println("Unlocked");
}
</content>
</create_file>
