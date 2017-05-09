// display test: write some data to the lcd

/* Connections:
 R/S : Pin 3
 R/W : not connected
 E   : Pin 4
 DB4 : Pin 6
 DB5 : Pin 7
 DB6 : Pin 8
 DB7 : Pin 9
*/

// include LCD functions:
#include <LiquidCrystal.h> 

// define the LCD screen
LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

// global variables
int analogValue;
int defValue;
String buttonNr;
float diff;
int redLed = 10;
int yellowLed = 11;
int greenLed = 12;

void setup()
{
  // LCD has 4 lines with 20 chars
  lcd.begin(20, 4); 
  lcd.print("system ready");
  //save default value of analog
  defValue = analogRead(A0);
  //set Led Pinmodes
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}


void loop()
{
   // enable the LED
  digitalWrite(redLed, HIGH);
  while (true) {
    if (updateDisplay() == "S1"){
      break;
    }
    delay(100);
  }
  digitalWrite(yellowLed, HIGH);
  for (int x=0; x < 11; x++) {
    updateDisplay();
    delay(100);
  }
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  for (int x=0; x < 31; x++) {
    updateDisplay();
    delay(100);
  }
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  for (int x=0; x < 11; x++) {
    updateDisplay();
    delay(100);
  }

}

String updateDisplay() {
  analogValue = analogRead(A0);
  // clear analog Value
  lcd.setCursor(13, 0);
  lcd.print("      ");
  
  lcd.setCursor(0, 0);
  lcd.print("Analog 0: ");
  lcd.print(analogValue);
  lcd.setCursor(0, 1);
  lcd.print("button : ");
  
  diff = 0;
  diff = analogValue - defValue;
  if (diff < -900) {
    buttonNr = "S1";
  } else if (diff > -850 && diff < -680) {
    buttonNr = "S2";
  } else if (diff > -650 && diff < -450) {
    buttonNr = "S3";
  } else if (diff > -440 && diff < -270) {
    buttonNr = "S4";
  } else if (diff >  -260 && diff < -100) {
    buttonNr = "S5";
  } else {
    buttonNr = "--";
    }

  lcd.print(buttonNr);
  return buttonNr;
}

/* Usefull LCD functions:
set the current write position of the lcd to specific line and row:
  lcd.setCursor(row, line);  

write onto lcd, starting at current position:
  lcd.print("abc");

clear the lcd (this writes " " into all positions and is therefore slow):
If only specific areas should be cleared use a mix of setCursor and print(" ") instead
  lcd.clear();
*/
