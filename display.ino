#include <math.h>

int latch = 9;  //74HC595  pin 9 STCP
int clock = 10; //74HC595  pin 10 SHCP
int data = 8;   //74HC595  pin 8 DS

#define NUM_OF_DIGITS (4)
#define DELAY_FACTOR (100)

const int digitPins[NUM_OF_DIGITS] = {12, 13, 11, 7};

unsigned char numTable[] =
{
  0x3f, // 0
  0x06, // 1
  0x5b, // 2
  0x4f, // 3
  0x66, // 4
  0x6d, // 5
  0x7d, // 6
  0x07, // 7
  0x7f, // 8
  0x6f, // 9
  0x77, // A
  0x7c, // B
  0x39, // C
  0x5e, // D
  0x79, // E
  0x71, // F
};

int scanPosition = 0;
int digitData[NUM_OF_DIGITS] = {};

void setupDisplay()
{
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  
  // set related pins as output pins
  for (int i = 0; i < NUM_OF_DIGITS; i++)
  {
    pinMode(digitPins[i], OUTPUT);
  }
}

void displayNumber(int digitCount, int *num_arr)
{
  unsigned char digitPattern;
  resetDisplay();
  for (int i = 0; i < digitCount; i++)
  {
    int digit = NUM_OF_DIGITS - 1 - i;
    int numberToDisplay = num_arr[i];
    digitPattern = numTable[numberToDisplay];
    digitalWrite(latch, LOW);
    shiftOut(data, clock, MSBFIRST, digitPattern);
    digitalWrite(latch, HIGH);
    digitalWrite(digitPins[digit], LOW);
    delay(4);
    digitalWrite(digitPins[digit], HIGH);
  }
}

void display(int num)
{
  const int digitBase = 10;
  int digitCount = log10(num) + 1;
  // get every values in each position of those 4 digits based on digitBase
  // digitBase should be <= 16
  // for example, if digitBase = 2, binary values will be shown. If digitBase = 16, hexidecimal values will be shown
  for (int i = 0; i < NUM_OF_DIGITS; i++)
  {
    digitData[i] = num % digitBase;
    num /= digitBase;
  }
  unsigned long startTime = millis();

  while (millis() - startTime < 3000ul)
  {
    displayNumber(digitCount, digitData);
  }
}

void resetDisplay() {
  for (int i = 0; i < NUM_OF_DIGITS; i++)
  {
     /**
     * To turn off a digit, we need to turn its pin's signal HIGH.
     * This is because we control each digit's common cathode
     * pin, which connects to GND.  By turning the signal high
     * for a given digit, the circuit for that digit can't complete
     * and thus won't display any LEDs, hence it's 'off'.
     */
    digitalWrite(digitPins[i], HIGH);
  }
}
