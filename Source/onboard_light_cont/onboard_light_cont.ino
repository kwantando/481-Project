void setup() {
  // initialize serial communication:
  Serial.begin(9600); 
   // initialize the LED pins:
      for (int thisPin = 2; thisPin < 9; thisPin++) {
        pinMode(thisPin, OUTPUT);
      } 
}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.  
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For 
    // example 'a' = 97, 'b' = 98, and so forth:

    switch (inByte) {
    case 'a'ar:    
      digitalWrite(2, LOW);
      break;
    case 'b':    
      digitalWrite(4, HIGH);
      break;
    case 'c':    
      digitalWrite(6, HIGH);
      break;
    case 'd':    
      digitalWrite(3, HIGH);
      break;
    case 'e':    
      digitalWrite(5, HIGH);
      break;
    case 'f':
      digitalWrite(9, HIGH);
      break;
    case 'A':
      digitalWrite(2, LOW);
      break;
    case 'B':
      digitalWrite(4, LOW);
      break;
    case 'C':
      digitalWrite(6, LOW);
      break;
    case 'D':
      digitalWrite(3, LOW);
      break;
    case 'E':
      digitalWrite(5, LOW);
      break;
    case 'F':
      digitalWrite(9, LOW);
      break;
    default:
      // turn all the LEDs off:
      for (int thisPin = 2; thisPin < 7; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
    } 
  }
}
