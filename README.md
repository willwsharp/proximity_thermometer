# proximity_thermometer
Arduino prototype for a proximity thermometer.

Here are the sensors and parts I used to build this prototype.

x1 Arduino Uno R3

x1 breadboard

x1 Ultrasonic Ranging Module HC-SR04

x1 Temperature and Humidity Sensor DHT11

x1 4-digit 7-segment display

x1 Shift Register 74HC595

x4 220 Ohm resistors

x6 M-F Dupont wires

x25(ish) M-M wires


The basic premise is the Ranging module constantly measures the distance of things in front of it, when it detects something within 20 cm, it will read in the temperature from the DHT11 and display it on the 4-digit 7-segment display.

## HC595 shift register
This reduces the amount of Arduino pins needed to drive the display. To explain how that's possible lets go over some data about the display first.

The 4-digit 7-segment display has 8 inputs that control which segments (including decimal point) to display. Each segment (and decimal point) is controlled by a specific input. Since each input can only be on or off, we can say our display needs 8 bits of data to display a given character.  Here's a table detailing which bits need to be on/off to display a number.

|    Pattern    |     Number   |
| ------------- | -------------|
|   0011 1111   |       0      |
|   0000 0110   |       1      |
|   0101 1011   |       2      |
|   0100 1111   |       3      |
|   0110 0110   |       4      |
|   0110 1101   |       5      |
|   0111 1101   |       6      |
|   0000 0111   |       7      |
|   0111 1111   |       8      |
|   0110 1111   |       9      |
|   0111 0111   |       A      |
|   0111 1100   |       B      |
|   0011 1001   |       C      |
|   0101 1110   |       D      |
|   0111 1001   |       E      |
|   0111 0001   |       F      |

To supply the display with these 8 bits of data, we need to use 8 pins from our Arduino, which is a lot.

This is where the HC595 comes into play.

The HC595 is an 8-bit shift register with serial-in and parallel-out.  These two facts are essential to us.  It has the exact number of bits we need and it allows us to input data serially or one bit at a time, and have all those bits be accessible in parallel or at the same time.  The HC595 basically buffers our input and then when we're done writing our bit pattern, it'll output the whole pattern at once to its 8 outputs, which will drive the display.

## Displaying multiple numbers

Technically, our 4-digit 7-segment display is really just 4 single-digit 7-segment displays put together. These displays share the 8 inputs, so our bit pattern is applied across all 4 digits at the same time.  However, each digit also has a Common Cathode pin (could also be Common Anode depending on the display) which controls which digit to display. We can hook each of these Common Cathode pins to our Arduino, allowing us to control which digit is displayed. This means we can turn on one digit, display a number on it, turn it off, and then repeat the process for a different digit and number. If we do this really fast for an extended amount of time, we can trick the brain into thinking that the display is showing the combination of these numbers instead of one digit at a time. This is called Persistence of Vision.
