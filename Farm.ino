#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "home-ac0a7.firebaseio.com"
#define FIREBASE_AUTH "I5ZtvRD4VdoKxjyBgV24UQPieity0ZzxO1GMdMdE"

// Config connect WiFi
#define WIFI_SSID "Sciweek-IT"
#define WIFI_PASSWORD "123456789"


int LightP = D1;
int WaterP = D2;

void setup() {

  Serial.begin(9600);

  pinMode(LightP, OUTPUT);
  pinMode(WaterP, OUTPUT);

  digitalWrite(LightP, LOW);
  digitalWrite(WaterP, LOW);


  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  String Light = Firebase.getString("LightFarm");
  String Water = Firebase.getString("WaterFarm");


  if (Light == "ON") {
    digitalWrite(LightP, HIGH);
  } else if (Light == "OFF") {
    digitalWrite(LightP, LOW);

  }
  if (Water == "ON") {
    digitalWrite(WaterP, HIGH);
  } else if (Water == "OFF") {
    digitalWrite(WaterP, LOW);

  }

}
