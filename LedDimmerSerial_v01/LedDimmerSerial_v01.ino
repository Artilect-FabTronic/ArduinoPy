/*
  LedDimmerSerial v01
  Reads an analog input on pin 0 (A0), prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

const char REV[] = { "00" }; // TODO: Increment REV number each time the code was modified!

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

const int ledPin = 9;      // the pin that the LED is attached to

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // reserve 100 bytes for the inputString:
  inputString.reserve(100);
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int brightness = map(sensorValue, 0, 1023, 0, 255);

  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print(',');
  Serial.println(brightness);

  // set the brightness of the LED:
  analogWrite(ledPin, brightness);

  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  delay(1);        // delay in between reads for stability
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // check if received 'V'
    if ('V' == inChar) {
      Serial.println( "=== LedDimmerSerial ===");
      Serial.print( "Firmware Ver: 01, Rev: ");
      Serial.println( REV );
    }
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

