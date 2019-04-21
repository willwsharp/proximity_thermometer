//www.elegoo.com
//2018.10.25


/*
 * Initialize the serial port.
 */
void setup( )
{
  Serial.begin(9600);
  setupDisplay();
  // reset display to clean data from last session
  resetDisplay();
}

/*
 * Main program loop.
 */
void loop( )
{
  long distance = getDistance();
  if (distance < 20 && distance > 0)
  {
    int temp = getTemperature(true);
    display(temp); 
  }
}
