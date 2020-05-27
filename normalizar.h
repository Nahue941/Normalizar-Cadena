#ifndef NORMALIZAR_H_INCLUDED
#define NORMALIZAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define ARG_ARCH_ENT 1
#define ARG_ARCH_SAL 2

#define TAM_LINEA 501

#define TODO_OK 0
#define ERROR_ARCH 2
#define ERROR_TAM_BUF 3

#define TRUE 1
#define FALSE 0

typedef struct{
    char* cursor;
    int finSecuencia;//boolean var
    char* inicio;
    int cvpc;//cantidad caracteres validos previos al caracter separador
}SecuenciaPal;

typedef struct{
    char* iniPal;
    char* finPal;
    int contCar;//Contador de caracteres escritos. Debe iniciarse en 0
    int numPal;//numero de palabra. Contador a iniciar en 0
}Palabra;

char* normalizar(const char* aNormalizar, char* normalizada);
void crearSecuencia(SecuenciaPal* sec,char* cad);
Palabra* leerPalabra(SecuenciaPal* sec,Palabra* palabra);
Palabra* escribirPalabra(SecuenciaPal* sec, Palabra* palabra, Palabra* palabraDest);
void formatearPalabra(Palabra* palabra);
int finSecuencia(const SecuenciaPal* sec);
void escribirCaracter(SecuenciaPal* sec, char car);
int moverCursor(SecuenciaPal* sec, int offset);

char aMayus(char car);
char aMinus(char car);
int esLetra(char car);

char* normalizarApYN(const char* aNormalizar, char* normalizada, char carSeparador, int cantPalPorDefecto);
int buscarCaracter(SecuenciaPal* sec,char car);
void formatearPalabraApYN(Palabra* pal, int posCar);
void crearPalabra (Palabra* pal);
int cantCarVal(SecuenciaPal* sec, char car);//cantidad de caracteres validos
Palabra* leerPalabraApYN(SecuenciaPal* sec,Palabra* pal);
Palabra* escribirPalabraApYN(SecuenciaPal* sec, Palabra* palO, Palabra* palD);//Palabra Origen||Palabra Destino
void formatearPalApYNPalabra(Palabra* pal, int cantPal);
void formatearPalApYNCaracteres(Palabra* pal, int numCar);
#endif // NORMALIZAR_H_INCLUDED
