# ESP8266 + DHT sensor based data logger #

## Background ##
Getting fed up with the feeling that the temperature around here is ever changing, I created this little sketch to log the temperature and humidity to my InfluxDB server. Using a Grafana instance to display the data.

Having a Wemos D1 and a AM2301 roaming around the bench, this was used to create this data logger.

## The Result ##

![Example Grafana Dashboard](/grafana-example.png?raw=true)

## Setup ##

### InfluxDB ###

For an excelent guide to get InfluxDB up and running on your server, see https://docs.influxdata.com/influxdb/v1.3/introduction/installation/.

**Note:** I am running InfluxDB behind a reverse proxy, you will need to adjust the port number in the sketch.

### Grafana ###

Likewise for Grafana there is a excellent setup guide: http://docs.grafana.org/installation/

Afterwards upload the `grafana-dashboad.json` file to get your temperature dashboard started.

### The Sketch ###

Enter your WiFi, InfluxDB and DHT sensor type/pin as constants in the sketch, upload and you should be ready to go!

## Dependencies ##

* https://github.com/octvcdrc/ESP8266Influxdb.git (**branch:** patch-host-headers-closing-connections)
* https://github.com/adafruit/DHT-sensor-library
