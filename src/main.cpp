#include <Arduino.h>
long a = 1;
long b = 2;
long fibo(){
    long r = a + b;
    a = b;
    b = r;
    Serial.println(r);
}

volatile long rASM = 0;
long fiboASM(){

    asm("LDI Z, 0"); // On met le registre R18 à 0, la variable r
    asm("ADYW Z, X");
    asm("ADYW Z, Y"); // On ajoute a et b à r
    asm("MOV X, Y"); // On copie la valeur de b sur a
    asm("MOV Y, Z"); // On copie la valeur de r sur b
    asm("sts (rASM), Z");

}

void setup()
{
    Serial.begin(9600);
    long start = micros();
    int compt = 0;
    int compt2 =0;
    int limit = 11;

    asm("LDI XL, 1");
    asm("LDI YL, 2");

    while(compt < limit){
        fiboASM();
        compt++;
    }

    long endASM = micros();
    Serial.println("---");

    while(compt2 < limit){
        fibo();
        compt2++;

    }
    long endN = micros();
    Serial.print("ASM time :");Serial.println(endASM - start);
    Serial.print("C time : ");Serial.println(endN-endASM);
}




