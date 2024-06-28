
#include <Servo.h>
#include <IRremote.h>

// Servo
Servo myservo;

// IR
#define IR_PIN 11

// Digit values
int num[3] = {0, 0, 0}; // Array to hold the three digits

// Current digit position
int currentDigit = 0;

// Final angle
int Fangle;

void setup() {
  Serial.begin(9600);
  
  // Initialize IR receiver on pin 11
  IrReceiver.begin(IR_PIN);
 
  // Attach servo to pin 9
  myservo.attach(9);  
}

void loop() {
  if (IrReceiver.decode()) {
    int x = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    // Check for 'Enter' key
    if (x == 8) { // 'Enter' key hex value
      Fangle = num[0] * 100 + num[1] * 10 + num[2];
      myservo.write(Fangle);
      Serial.print("Angle set to: ");
      Serial.println(Fangle);
      resetValues();
    }
    
    // Check for 'Reset' key
    if (x == 14) { // 'Reset' key hex value
      myservo.write(0);
      Serial.println("RESET");
      resetValues();
    }

    // Process digit input
    if (currentDigit < 3) {
      setDigit(num[currentDigit], x);
      currentDigit++;
    }
  }
}

// Function to set digit values
void setDigit(int &digit, int x) {
  switch (x) {
    case 12: digit = 0; break;
    case 16: digit = 1; break;
    case 17: digit = 2; break;
    case 18: digit = 3; break;
    case 20: digit = 4; break;
    case 21: digit = 5; break;
    case 22: digit = 6; break;
    case 24: digit = 7; break;
    case 25: digit = 8; break;
    case 26: digit = 9; break;   
    default: currentDigit--; // Ignore invalid digits and stay at the current position
  }
}

// Reset values
void resetValues() {
  num[0] = 0;
  num[1] = 0;
  num[2] = 0;
  currentDigit = 0;
}
