

#include <ESP8266WiFi.h>

WiFiClient client;


int X;
int Y;
int flag=0 ;
int relay_pin = 8;
int moist_pin = A0;
int moist_value=30 ;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input=7;


const char* ssid     = "LifeatSriShakthi bridge";
const char* password = "12332133";


String stats = "off";

const int Port = 80;
const char* host = "fertigation.000webhostapp.com";



void datasend(){
  if (!client.connect(host, Port)) {
    Serial.println("connection failed");
    return;
  }
else{
String url = "fertigation.000webhostapp.com/api/include/insert.php";
  url += "?temp=";
  url += moist_value;
  url += "&status=";
  url += stats;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}
void connectwifi()
{
  Serial.begin(115200);
   WiFi.begin(ssid, password);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
 

   connectwifi();

    delay(500);    
   Serial.println("Reading From the Sensor ...");
   delay(2000);
   pinMode(relay_pin,OUTPUT);

   
   
}

void loop()
{  
/* X = pulseIn(input, HIGH);
Y = pulseIn(input, LOW);


moist_value= analogRead(moist_pin);

moist_value = map(moist_value,700,0,0,100);*/
Serial.print("Mositure : ");

Serial.println(moist_value);

Serial.println("%");

delay(1000);

/*if(flag==0){
  

if(moist_value<=30)

{

digitalWrite(relay_pin,LOW);

}

else

{

digitalWrite(relay_pin,HIGH);

}
}*/

/*else {
  
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.println("VOL. :0.00");
Serial.println("TOTAL:");
Serial.print( TOTAL);
Serial.print(" L");
}
else
{
TOTAL = TOTAL + LS;
Serial.println(FREQUENCY);
Serial.println("VOL.: ");
Serial.print(WATER);
Serial.print(" L/M");
Serial.println("TOTAL:");
Serial.print( TOTAL);
Serial.print(" L");
}

if(TOTAL<=4)

{

digitalWrite(relay_pin,HIGH);
stats = "on";
}

else

{

digitalWrite(relay_pin,LOW);
stats = "off";
}

}
}*/

datasend();
}

}