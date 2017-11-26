#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <RCSwitch.h>

const char* ssid = "Schmidt";
const char* password = "84966060666259704104";

char* topic = "licht/decke";
char* server = "win.laggson.de";
char state;

int ledPin = 5; //GPIO5 = D1
int transmitPin = 2; //GPIO2 = D4

void callback(char* topic, byte* payload, unsigned int length)
{
  char* message = (char*) payload;
  message[length] = '\0';
  
  handleInput(message);
}

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  delay(10);

  initWifi();
  initMqtt();

  mySwitch.enableTransmit(transmitPin);
  mySwitch.setPulseLength(290);
}

void initWifi()
{

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void initMqtt()
{
  // Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  clientName += "-";
  clientName += String(micros() & 0xff, 16);

  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);

  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);

    if (client.publish(topic, "hello from ESP8266")) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }

    if (client.subscribe(topic))
    {
      Serial.println("Subscribe ok");
    }
    else {
      Serial.println("Subscribe failed");
    }
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void handleInput(char* payload)
{
  Serial.println("Nachricht erhalten");
  char command = payload[0];
  Serial.println(command);
  Serial.println();

  switchState(command);
}

void switchState(char input)
{
  char* cmd;
  if (input == 'a') {
    cmd = "0F0F11F01000";
  }
  else if (input == 'b') {
    cmd = "0F0F11F00100";
  }
  else if (input == 'c') {
    cmd = "0F0F11F00010";
  }
  else if (input == 'd') {
    cmd = "0F0F11F00001";
  }

  if (cmd != "") {
    blink();
    mySwitch.sendTriState(cmd);
//    state = toupper(input);
  }
}

void blink()
{
  digitalWrite(ledPin, HIGH);
  delay(10);
  digitalWrite(ledPin, LOW);
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

void loop() {
  client.loop();
}
