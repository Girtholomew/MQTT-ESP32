# MQTT-ESP32
This repo should help you host an MQTT server on your laptop and connect an esp32 to the MQTT server, publish and subscribe to topics, etc.

# Using Mosquitto either as a Server or a Client

install mosquitto in your system.
Then for the localhost setup, we need to create a configuration file. create a file and add `.conf` as the extension.
inside the .conf file, paste the following lines:
```listener 1883 127.0.0.1```
```allow_anonymous true```
After you've pasted the above lines, you can start the mosquitto service by this command:
```sudo systemctl status mosquitto```
and then you can either publish or subscribe to topics. 
In order to publish, you can use the following command:
```mosquitto_pub -h Your_Laptop's_IP -t topic_name -m "enter message here"```
that's the steps you need to follow in order to publish a message through mosquitto.
