// Inclusión ficheros

#include <Arduino.h>
#include "headers/Conexion.h"
#include "headers/Controlador.h"
#include "headers/Encoder.h"
#include "headers/Interruptor.h"
#include "headers/Motor.h"
#include "headers/OLED.h"
#include "headers/Termocupla.h"

// Variables globales

float tempExtr, velExt, velTrit;
int controlVelExt, controlVelTrit, controlTemp;

// Instanciación de clases

Conexion conexion;

Termocupla temp1(18,5,19);
Termocupla temp2(18,6,19);
Termocupla temp3(18,7,19);

Controlador velocidadTrit(1);
Controlador velocidadExtr(1);
Controlador temperaturaExtr(0);

Encoder encoderExtrusor(12,13);
Encoder encoderTriturador(13,14);

Interruptor botonEmergencia(2);
Interruptor finCarrera1(3);
Interruptor finCarrera2(4);

Motor motorExtrusor(6, 7, 8, 9, 1);
Motor motorTriturador(10, 11, 8, 12, 2);
Motor motorVentilador(13,14,8,15,3);
Motor motorDispensador(16,17,8,19,4);
Motor niquelinas(20,21,8,22,5);

Oled pantalla;

Termocupla termocupla1(20,21,22);
Termocupla termocupla2(20,21,23);
Termocupla termocupla3(20,21,24);

// Callbacks tareas periodicas

static TimerHandle_t temperaturas = NULL;
static TimerHandle_t controladores = NULL;
static TimerHandle_t oledVisualizacion = NULL;
static TimerHandle_t reportarDatos = NULL;

void readTemperatures(TimerHandle_t xTimer)
{
  float termo1 = termocupla1.readTempC();
  float termo2 = termocupla2.readTempC();
  float termo3 = termocupla3.readTempC();
  tempExtr = (termo1 + termo2 + termo3)/3;
}

void recalcularControladores()
{
  controlVelTrit = velocidadTrit.recalcular(velTrit);
  controlVelExt = velocidadExtr.recalcular(velExt);
  controlTemp = temperaturaExtr.recalcular(tempExtr);
}

void visualizacionOled()
{
  pantalla.paginaMonitor();
}

void reportar()
{
  conexion.report();
}

// Callbacks Interrupciones

void interupcionSeguridad()
{
  if (botonEmergencia.status())
  {
    motorExtrusor.off();
    motorTriturador.off();
    motorVentilador.off();
    motorDispensador.off();
    while(true){}
  }
}

void adquirirVelocidadExtr()
{
  encoderExtrusor.ISREnc();
  if (encoderExtrusor.contador > 100)
  {
    velExt = encoderExtrusor.getVelocidad();
  }
}

void adquirirVelocidadTrit()
{
  encoderTriturador.ISREnc();
  if (encoderTriturador.contador > 100)
  {
    velTrit = encoderTriturador.getVelocidad();
  }
}

// Callbacks Tareas prioritarias 

void motExtControl( void *pvParameters )
{
 for( ;; )
 {
   motorExtrusor.cw();
   motorExtrusor.setValue(controlVelExt);
 }
}


void motTritControl( void *pvParameters )
{
 for( ;; )
 {
   motorTriturador.cw();
   motorTriturador.setValue(controlVelTrit);
 }
}

void motDosControl( void *pvParameters )
{
 for( ;; )
 {
   motorDispensador.setValue(120);
   if(finCarrera1.status())
   {
     motorDispensador.ccw();
   }
   if(finCarrera2.status())
   {
     motorDispensador.cw();
   }
 }
}

void niquelinasControl( void *pvParameters )
{
 for( ;; )
 {
    niquelinas.setValue(controlTemp);
 }
}

// Tareas iniciales

void setup() 
{
  // Iniciar comunicación serial
  Serial.begin(115200);
  // Recopilación de credenciales conecxion con MQTT y configuracion de parametros
  bool respuesta = conexion.autoConnect();
  while (!respuesta){}
  
  // Inicializacion tareas periodicas

  temperaturas = xTimerCreate( "Temperaturas",              //Nombre Tarea
                                5000/portTICK_PERIOD_MS,    //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                readTemperatures);          //Función a ser llamada

  controladores = xTimerCreate( "Controladores",            //Nombre Tarea
                                5000/portTICK_PERIOD_MS,    //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                recalcularControladores);   //Función a ser llamada
                            
  oledVisualizacion = xTimerCreate( "Visualizacion",        //Nombre Tarea
                                5000/portTICK_PERIOD_MS,    //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                visualizacionOled);         //Función a ser llamada

  reportarDatos = xTimerCreate( "Envio de datos",           //Nombre Tarea
                                5000/portTICK_PERIOD_MS,    //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                reportar);                  //Función a ser llamada

   
  if(temperaturas == NULL || controladores == NULL || oledVisualizacion == NULL || reportarDatos == NULL)
  {
    Serial.println("No se pudo iniciar tareas, reiniciando");
    ESP.restart();
  }
  else
  {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("Iniciando tareas periodicas");
    xTimerStart(temperaturas, portMAX_DELAY);
    xTimerStart(controladores, portMAX_DELAY);
    xTimerStart(oledVisualizacion, portMAX_DELAY);
    xTimerStart(reportarDatos, portMAX_DELAY);
  }

  // Inicializacion tareas prioritarias
  xTaskCreate(niquelinasControl, "Control Niqueinas", 2100, NULL, 4, NULL);
  xTaskCreate(motExtControl, "Control motor Extrusor", 1024, NULL, 3, NULL);
  xTaskCreate(motTritControl, "Control motor triturador", 1024, NULL, 2, NULL);
  xTaskCreate(motDosControl, "Control dispensador", 1024, NULL, 2, NULL);

  // Inicializacion tareas de interrupcion

  attachInterrupt(encoderTriturador.chAPin, adquirirVelocidadTrit, CHANGE);
  attachInterrupt(encoderTriturador.chBPin, adquirirVelocidadTrit, CHANGE);

  attachInterrupt(encoderExtrusor.chAPin, adquirirVelocidadExtr, CHANGE);
  attachInterrupt(encoderExtrusor.chBPin, adquirirVelocidadExtr, CHANGE);

  attachInterrupt(botonEmergencia.pinInterruptor, interupcionSeguridad, RISING);

  vTaskDelete(NULL);
}

void loop() 
{
}