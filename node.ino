#include <ESP8266WiFi.h>
#define SECRET_SSID "PROTOTYPE"    // replace MySSID with your WiFi network name
#define SECRET_PASS "1234512345"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 2488966     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "AWWP8QGSIQ50N2U7"   // replace XYZ with your channel write API Key
#include "ThingSpeak.h"  // always include thingspeak header file after other header files and custom macros

String data;
String val1, val2, val3;
int a, b, c;

char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password
int keyIndex = 0;           // your network key Index number (needed only for WEP)
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;
// Initialize our values
String myStatus = "";

void setup() {
  Serial.begin(9600);  // Initialize serial
}

void loop() {

  // Connect or reconnect to WiFi a23b45c56d66e45f83g
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  if (Serial.available() > 0) {
    data = Serial.readString();
    Serial.println(data);
    a = data.indexOf("a");
    b = data.indexOf("b");
    a = a + 1;
    val1 = data.substring(a, b);
    Serial.println(val1);
    ThingSpeak.setField(1, val1);

    b = data.indexOf("b");
    c = data.indexOf("c");
    b = b + 1;
    val2 = data.substring(b, c);
    Serial.println(val2);
    ThingSpeak.setField(2, val2);

    c = data.indexOf("c");
    a = data.indexOf("d");
    c = c + 1;
    val3 = data.substring(c, a);
    Serial.println(val3);
    ThingSpeak.setField(3, val3);
    delay(1000);

    a = data.indexOf("d");
    b = data.indexOf("e");
    a = a + 1;
    val1 = data.substring(a, b);
    Serial.println(val1);
    ThingSpeak.setField(4, val1);

    b = data.indexOf("e");
    c = data.indexOf("f");
    b = b + 1;
    val2 = data.substring(b, c);
    Serial.println(val2);
    ThingSpeak.setField(5, val2);

    c = data.indexOf("f");
    a = data.indexOf("g");
    c = c + 1;
    val3 = data.substring(c, a);
    Serial.println(val3);
    ThingSpeak.setField(6, val3);

//    a = data.indexOf("g");
//    b = data.indexOf("h");
//    a = a + 1;
//    val1 = data.substring(a, b);
//    Serial.println(val1);
//    ThingSpeak.setField(7, val1);
//    delay(1000);
  }
  // figure out the status message
  // set the status
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000);  // Wait 20 seconds to update the channel again
}