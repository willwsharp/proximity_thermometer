#include "SR04.h"
#define TRIG_PIN 4
#define ECHO_PIN 3
SR04 sensor = SR04(ECHO_PIN,TRIG_PIN);

long getDistance()
{
  long distance = sensor.Distance();
  // filter out bad values
  if (distance <= 400) {
    return distance;
  } else
  {
    return 0;
  }
}
