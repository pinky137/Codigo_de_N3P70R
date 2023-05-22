#include <Wire.h>  // Librería para la comunicación I2C
#include <Adafruit_RGBLCDShield.h>  // Librería para la pantalla LCD
#include <Adafruit_MotorShield.h>  // Librería para el controlador de motores
#include <tcs3200.h>  // Librería para el sensor de color TCS3200
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <AFMotor.h>

const int trigPin = 12;
const int echoPin = 13;

long duration;
int distance;

#define S0 2
#define S1 4
#define S2 8
#define S3 10
#define salidaSensor 7

#define TRIGGER_PIN 12  // Pin del sensor ultrasónico HC-SRO4 para el trigger
#define ECHO_PIN 13
//
// Cableado de TCS3200 a Arduino
//
 
// Para guardar las frecuencias de los fotodiodos
int frecuenciaRojo = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int colorRojo;
int colorVerde;
int colorAzul;
int a4;
int a3;
bool sentinela = true;


void setup() {
  // Definiendo las Salidas
  
  // Definiendo salidaSensor como entrad
  
   // Iniciar la comunicacion serie 
  Serial.begin(9600);
  	//Set initial speed of the motor & stop
}

int speed(int b)
{
  return map(b, 0, 100, 0, 255);
}

void loop() {

    AF_DCMotor m1(1);//define motor 1 as m1
    AF_DCMotor m2(2);//define motor 2 as m2
    AF_DCMotor m3(3);//define motor 3 as m3
    AF_DCMotor m4(4);//define motor 4 as m4

    m1.setSpeed(0);//motor 1 is turned off to turn on change 0, to 255
    m2.setSpeed(0);//motor 2 is turned off  
    m3.setSpeed(0);//motor 3 is turned off 
    m4.setSpeed(0); //motor 4 is turned off 

    m3.run(BACKWARD);
    m3.setSpeed(speed(100));
    m4.run(FORWARD);
    m4.setSpeed(speed(100));
    delay(5000);
  

    m3.run(BACKWARD);
    m3.setSpeed(speed(0));
    a3 = 0;
    m4.run(FORWARD);
    m4.setSpeed(speed(0));
    a4 = 0;
    delay(2000);

    if (a3 == 0 && a4 == 0){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);    // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microsecond
    // Prints the distance on the Serial Monitor

      duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
      distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print ("\n");
      delay(2000);

      if (distance < 8){
        pinMode(salidaSensor, INPUT);
  
      // Definiendo la escala de frecuencia a 20%
        digitalWrite(S0,HIGH);
        delayMicroseconds(5000); 
        digitalWrite(S1,LOW);
        delayMicroseconds(5000); 

        pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPin, INPUT); // Sets the echoPin as an Input
        pinMode(S0, OUTPUT);
        pinMode(S1, OUTPUT);
        pinMode(S2, OUTPUT);
        pinMode(S3, OUTPUT);

        digitalWrite(S2,LOW);
        delayMicroseconds(5000); 
        digitalWrite(S3,LOW);
        delayMicroseconds(5000); 
      // Leyendo la frecuencia de salida del sensor
        frecuenciaRojo = pulseIn(salidaSensor, LOW);
 
  // Mapeando el valor de la frecuencia del ROJO (RED = R) de 0 a 255
  // Usted debe colocar los valores que registro. Este es un ejemplo: 
  // colorRojo = map(frecuenciaRojo, 70, 120, 255,0);
        colorRojo = map(frecuenciaRojo, 200, 1200, 255,0);
  
  // Mostrando por serie el valor para el rojo (R = Red)
        Serial.print("R = ");
        Serial.print(colorRojo);
  
  // Definiendo la lectura de los fotodiodos con filtro verde
        digitalWrite(S2,HIGH);
        delayMicroseconds(5000); 
        digitalWrite(S3,HIGH);
        delayMicroseconds(5000); 
  
  // Leyendo la frecuencia de salida del sensor
        frecuenciaVerde = pulseIn(salidaSensor, LOW);
 
  // Mapeando el valor de la frecuencia del VERDE (GREEN = G) de 0 a 255
  // Usted debe colocar los valores que registro. Este es un ejemplo: 
  // colorVerde = map(frecuenciaVerde, 100, 199, 255,0);
        colorVerde = map(frecuenciaVerde, 340, 1300, 255,0);
 
  // Mostrando por serie el valor para el verde (G = Green)
        Serial.print("G = ");
        Serial.print(colorVerde);
 
  // Definiendo la lectura de los fotodiodos con filtro azul
        digitalWrite(S2,LOW);
        digitalWrite(S3,HIGH);
  
  // Leyendo la frecuencia de salida del sensor
        frecuenciaAzul = pulseIn(salidaSensor, LOW);
 
  // Mapeando el valor de la frecuencia del AZUL (AZUL = B) de 0 a 255
  // Usted debe colocar los valores que registro. Este es un ejemplo: 
  // colorAzul = map(frecuenciaAzul, 38, 84, 255, 0);
        colorAzul = map(frecuenciaAzul, 360, 1500, 255, 0);
  
  // Mostrando por serie el valor para el azul (B = Blue)
        Serial.print("B = ");
        Serial.print(colorAzul);
 
  // Comprobar cual es el color detectado y mostrarlo
  // con un mensaje en el monitor serie
        if(colorRojo > colorVerde && colorRojo > colorAzul){
          Serial.println(" - Detectado ROJO");
          m1.setSpeed(0);//motor 1 is turned off to turn on change 0, to 255
          m2.setSpeed(0);//motor 2 is turned off  
          m3.setSpeed(0);//motor 3 is turned off 
          m4.setSpeed(0); //motor 4 is turned off 

          m1.run(BACKWARD);
          m1.setSpeed(speed(0));
          m4.run(FORWARD);
          m4.setSpeed(speed(0));
          delay(4000);

          m1.run(BACKWARD);
          m1.setSpeed(speed(0));
          a3 = 0;
          m4.run(FORWARD);
          m4.setSpeed(speed(0));
          a4 = 0;
          delay(4000);
  }
        if(colorVerde > colorRojo && colorVerde > colorAzul){
          Serial.println(" - Detectado VERDE");
  }
        if(colorAzul > colorRojo && colorAzul > colorVerde){
          Serial.println(" - Detectado AZUL");      
}
        AF_DCMotor m1(1);//define motor 1 as m1
        AF_DCMotor m2(2);//define motor 2 as m2
        AF_DCMotor m3(3);//define motor 3 as m3
        AF_DCMotor m4(4);//define motor 4 as m4

        m1.setSpeed(0);//motor 1 is turned off to turn on change 0, to 255
        m2.setSpeed(0);//motor 2 is turned off  
        m3.setSpeed(0);//motor 3 is turned off 
        m4.setSpeed(0); //motor 4 is turned off 

        m1.run(BACKWARD);
        m1.setSpeed(speed(100));
        m4.run(FORWARD);
        m4.setSpeed(speed(100));
        delay(4000);

        m1.run(BACKWARD);
        m1.setSpeed(speed(0));
        a3 = 0;
        m4.run(FORWARD);
        m4.setSpeed(speed(0));
        a4 = 0;
        delay(4000);

} 
}
}
