#include <Servo.h>
#include <TimeLib.h>
#include <math.h>
#include <EEPROM.h>

#define pi 3.14159265358979323846

Servo altitudeServo;
Servo azimuthServo;

// Definir pines para los servos
const int ALTITUDE_SERVO_PIN = 9;
const int AZIMUTH_SERVO_PIN = 10;

// Variables globales
float lat, Long;
int a, m, d1, d;

// Direcciones EEPROM para latitud y longitud
const int EEPROM_LAT = 0;
const int EEPROM_LONG = 4;

// Declaraciones de funciones
int calcularDiaDelAnio(int year, int month, int day);
float calcularDeclinacionSolar(int d);
float calcularEcuacionTiempo(int d);
float calcularTiempoSolarVerdadero(float hour, float Long, float eot);
float calcularAlturaSolar(float ds, float lat, float tsv);
float calcularAzimut(float ds, float lat, float alt_sol, float tsv);
void guardarCoordenadas(float lat, float Long);
void cargarCoordenadas();
bool solicitarNuevasCoordenadas();

void setup() {
  Serial.begin(9600);
  
  // Configurar los servos
  altitudeServo.attach(ALTITUDE_SERVO_PIN);
  azimuthServo.attach(AZIMUTH_SERVO_PIN);
  
  // Configurar la fecha y hora inicial (ajusta esto a la fecha y hora actuales)
  setTime(12, 0, 0, 15, 7, 2024);
  
  // Cargar coordenadas guardadas o solicitar nuevas
  cargarCoordenadas();
  if (solicitarNuevasCoordenadas()) {
    Serial.println("Ingrese la latitud:");
    while (!Serial.available()) {}
    lat = Serial.parseFloat();
    
    Serial.println("Ingrese la longitud:");
    while (!Serial.available()) {}
    Long = Serial.parseFloat();
    
    guardarCoordenadas(lat, Long);
  }
  
  Serial.print("Usando Latitud: ");
  Serial.print(lat);
  Serial.print(", Longitud: ");
  Serial.println(Long);
}

void loop() {
  // El resto del código loop() permanece igual
  // ...
}

// Implementaciones de las funciones existentes
// ...

// Nuevas funciones para manejar coordenadas

void guardarCoordenadas(float lat, float Long) {
  EEPROM.put(EEPROM_LAT, lat);
  EEPROM.put(EEPROM_LONG, Long);
}

void cargarCoordenadas() {
  EEPROM.get(EEPROM_LAT, lat);
  EEPROM.get(EEPROM_LONG, Long);
}

bool solicitarNuevasCoordenadas() {
  Serial.println("¿Desea ingresar nuevas coordenadas? (S/N)");
  while (!Serial.available()) {}
  char respuesta = Serial.read();
  Serial.println(respuesta);
  return (respuesta == 'S' || respuesta == 's');
}