#include <ESP8266WiFi.h>
#include <RCSwitch.h>

const char* ssid = "Schmidt";
const char* passwd = "84966060666259704104";

int transm = 2; //GPIO2 = D4
int ledPin = 5;
WiFiServer server(80);
RCSwitch mySwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //WIFI Verbindung
  IPAddress ip(192, 168, 178, 36);
  IPAddress gateway(192, 168, 178, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  WiFi.hostname("Markus-NodeMCU");
  WiFi.begin(ssid, passwd);

  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  //Server starten
  server.begin();
  Serial.println("Server started");
  Serial.print("IP: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());
  Serial.println("");

  //RC-Transmitter
  mySwitch.enableTransmit(2);
  mySwitch.setPulseLength(290);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(!client) {
    return;
  }

  Serial.println("new client");
  while(!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  char* cmd = "";
  char state;
  if(request.indexOf("/light=a") != -1) {
    cmd = "0F0F11F01000";
    state = 'A';
  }
  else if(request.indexOf("/light=b") != -1) {
    cmd = "0F0F11F00100";
    state = 'B';
  }
  else if(request.indexOf("/light=c") != -1) {
    cmd = "0F0F11F00010";
    state = 'C';
  }
  else if(request.indexOf("/light=d") != -1) {
    cmd = "0F0F11F00001";
    state = 'D';
  }

  if(cmd != "") {
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    mySwitch.sendTriState(cmd); 
  }
  
  writeHtmlWithStatus(client, state);
}

void writeHtmlWithStatus(WiFiClient client, char state)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<a href=\"/light=a\"><button>A</button></a>");
  client.println("<a href=\"/light=b\"><button>B</button></a>");
  client.println("<a href=\"/light=c\"><button>C</button></a>");
  client.println("<a href=\"/light=d\"><button>D</button></a>");
  client.println("</html>");

  // memory leak fix?
  client.flush();
  client.stop();
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

