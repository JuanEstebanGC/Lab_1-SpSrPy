/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

//Puertos
UnbufferedSerial datos(USBRX,USBTX);
AnalogIn potLimSup(A5);
AnalogIn potLimInf(A4);
AnalogIn potSig1(A3);
AnalogIn potSig2(A2);
InterruptIn btnLimitSup (D2);
InterruptIn btnLimitInf (D3);
InterruptIn btnEnvioSigP1 (D4);
InterruptIn btnEnvioSigP2 (D5);
DigitalOut ledSup(D7);
DigitalOut ledInf(D8);

Semaphore enviolimSup;
Semaphore enviolimInf;
Semaphore envioPot1;
Semaphore envioPot2;

//Hilos
Thread LimSup(osPriorityNormal, OS_STACK_SIZE, nullptr, nullptr);
Thread LimInf(osPriorityNormal, OS_STACK_SIZE, nullptr, nullptr);
Thread Pot1(osPriorityNormal, OS_STACK_SIZE, nullptr, nullptr);
Thread Pot2(osPriorityNormal, OS_STACK_SIZE, nullptr, nullptr);

//Funciones
void func_LimSup(void);
void func_LimInf(void);
void func_Pot1(void);
void func_Pot2(void);
void func_irq_LimSup(void);
void func_irq_LimInf(void);
void func_irq_Pot1(void);
void func_irq_Pot2(void);

//Variable Global
static char men[20];

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        btnLimitSup.rise(func_irq_LimSup);
        btnLimitInf.rise(func_irq_LimInf);
        btnEnvioSigP1.rise(func_irq_Pot1);
        btnEnvioSigP2.rise(func_irq_Pot2);

        //Nota a realizar: Hacer ADC para los potenciometros

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

//Activación de los semaforos
void func_irq_LimSup(){
    enviolimSup.release();
}
void func_irq_LimInf(){
    enviolimInf.release();
}
void func_irq_Pot1(){
    envioPot1.release();
}
void func_irq_Pot2(){
    envioPot2.release();
}

//Envio de señal

//Nota a realizar: Enviar los datos de los potenciometros por el puerto serial

void func_LimSup(){
    //const char men_tarea_Irq[20] = "Btn On \n";
    while(true){
        enviolimSup.acquire();
        /*sprintf(men,men_tarea_Irq);
        datos.write(men, 8);*/
    }
}

void func_LimInf(){
    //const char men_tarea_Irq[20] = "Btn On \n";
    while(true){
        enviolimInf.acquire();
        /*sprintf(men,men_tarea_Irq);
        datos.write(men, 8);*/
    }
}

void func_Pot1(){
    //const char men_tarea_Irq[20] = "Btn On \n";
    while(true){
        envioPot1.acquire();
        /*sprintf(men,men_tarea_Irq);
        datos.write(men, 8);*/
    }
}

void func_Pot2(){
    //const char men_tarea_Irq[20] = "Btn On \n";
    while(true){
        envioPot2.acquire();
        /*sprintf(men,men_tarea_Irq);
        datos.write(men, 8);*/
    }
}