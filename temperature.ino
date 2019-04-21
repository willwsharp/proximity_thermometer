#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 6;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

float getTemperature(bool toFahrenheight)
{
  float temperature;
  float humidity;
  bool tempTaken = false;
  while (!tempTaken)
  {
    tempTaken = dht_sensor.measure(&temperature, &humidity);
    if (toFahrenheight)
    {
      temperature = temperature * 9/5 + 32;
    }
  }
  return int(temperature);
}
