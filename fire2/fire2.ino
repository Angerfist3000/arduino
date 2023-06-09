#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
//incluir nuevos
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <stdio.h>

//-----------------Se definen los valores fundamentles del proyecto----------------- 
//Host del proyecto
#define FIREBASE_HOST ""
//Secret de la BD
#define FIREBASE_AUTH ""

//Nombre de mi red Wifi
#define WIFI_SSID ""
//password de mi red WiFi
#define WIFI_PASSWORD ""

//------ULTRASONICO 1--------//
//Pin digital GPIO4 - D2 del ESP8266 para el Trigger del sensor SENSOR ULTRASÓNICO
const int Trigger1 = 4; 
//Pin digital GPIO2 - D4 del ESP8266 para el Echo del sensor SENSOR UNTRASÓNICO
const int Echo1 = 2;
//definimos el valor del pin para el led verde
int ledPinVer1 = 5; 
//definimos el valor del pin para el led rojo
int ledPinRojo1 = 7; 


void setup() {
  Serial.begin(115200);

  //------ULTRASONICO 1--------
  //Se inicia el disparador
  pinMode(Trigger1,OUTPUT);
  //Iniciando el Echo
  pinMode(Echo1, INPUT);
  //Enviamos la señal al disparador
  digitalWrite(Trigger1, LOW);
  //declaramos el pin rojo como salida
  pinMode(ledPinRojo1,OUTPUT);
  //Declaramos el pin verde como salida
  pinMode(ledPinVer1,OUTPUT);

  

  //--------CODIGO PARA CONECTAR AL WIFI----------//
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500);
  } 
  Serial.println();
  //Al activarse la conección se envia un mensaje 
  Serial.print("Conectado:");
  //Se visualiza la dirección IP asignada al módulo ESP8266
  Serial.println(WiFi.localIP());
  Serial.println();
  //Se inicia la conección al HOST y a la BD
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}

void loop() {
  //---------ULTRASONICO 1----------
  //Declarando variable para el tiempo
  long t1;
  //Declaramos una variable para la distancia
  long d1;
  
  digitalWrite(Trigger1, HIGH);
  delayMicroseconds(10);//El tiempo de espera en que enviara el mensaje
  digitalWrite(Trigger1,LOW);

  t1=pulseIn(Echo1, HIGH);
  d1=t1/59;

  if (d1<=10)
  {
  Serial.print("Objeto Detectado: ");
  Serial.print(d1);
  Serial.print("cm");
  Serial.println();
  Firebase.setString("SENSOR1/Objeto Detectado","Vehiculo1");
  if(Firebase.failed())
  {
    Serial.print("Setendo/estado sensor Fallido:");
    Serial.println(Firebase.error());
  }
  digitalWrite(ledPinRojo1,HIGH);
  digitalWrite(ledPinVer1,LOW);
  delay(500);
  }
  else
  {
  Serial.print("En espera...");
  Serial.println();
  digitalWrite(ledPinVer1,HIGH);
  digitalWrite(ledPinRojo1,LOW);
  delay(500);
  }

  
}
