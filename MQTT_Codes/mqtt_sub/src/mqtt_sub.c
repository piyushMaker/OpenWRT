#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<mosquitto.h>

// Server connection parameters
#define MQTT_HOSTNAME "broker.mqttdashboard.com"
#define MQTT_PORT 1883
#define MQTT_USERNAME "NULL"
#define MQTT_PASSWORD "NULL"
#define MQTT_TOPIC "test"

/*
 * Start here
 */
int main (int argc, char **argv)
  {
  struct mosquitto *mosq = NULL;

  // Initialize the Mosquitto library
  mosquitto_lib_init();

  // Create a new Mosquitto runtime instance with a random client ID,
  //  and no application-specific callback data.  
  mosq = mosquitto_new (NULL, true, NULL);
  if (!mosq)
    {
    fprintf (stderr, "Can't initialize Mosquitto library\n");
    exit (-1);
    }

 mosquitto_username_pw_set (mosq, MQTT_USERNAME, MQTT_PASSWORD);

  // Establish a connection to the MQTT server. Do not use a keep-alive ping
  int ret = mosquitto_connect (mosq, MQTT_HOSTNAME, MQTT_PORT, 0);
  if (ret)
    {
    fprintf (stderr, "Can't connect to Mosquitto server\n");
    exit (-1);
    }

void my_message_callback(struct mosquitto *mosq, void *obj,
    const struct mosquitto_message *message)
  {
  // Note: nothing in the Mosquitto docs or examples suggests that we
  //  must free this message structure after processing it,
  //  (nor that we can assume that it is null-terminated.)
  printf ("Got message: %s\n", (char *)message->payload);
  }

  //...

  mosquitto_subscribe (mosq, NULL, MQTT_TOPIC, 0);

  // Specify the function to call when a new message is received
  mosquitto_message_callback_set (mosq, my_message_callback);

  // Wait for new messages
  mosquitto_loop_forever (mosq, -1, 1);

  // We need a short delay here, to prevent the Mosquitto library being
  //  torn down by the operating system before all the network operations
  //  are finished.
 // sleep (1);

  // Tidy up
 // mosquitto_disconnect (mosq);
 // mosquitto_destroy (mosq);
 // mosquitto_lib_cleanup();

  return 0;
  }
