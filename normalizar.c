#include "normalizar.h"

char* normalizar(const char* aNormalizar, char* normalizada)
{
    SecuenciaPal secOrig, secDest;

    crearSecuencia(&secOrig, (char*)aNormalizar);
    crearSecuencia(&secDest, normalizada);

    Palabra palabra, palabraDest;

    leerPalabra(&secOrig, &palabra);
    while(!finSecuencia(&secOrig)){
        escribirPalabra(&secDest, &palabra, &palabraDest);
        formatearPalabra(&palabraDest);///Ver formatear pre/pos ','
        escribirCaracter(&secDest, ' ');
        leerPalabra(&secOrig, &palabra);
    }

    moverCursor(&secDest, -1);///Limite
    escribirCaracter(&secDest, '\0');///Limite

    return normalizada;

}

void crearSecuencia(SecuenciaPal* sec,char* cad)
{
    sec->cursor = cad;
    sec->finSecuencia = FALSE;
    sec->inicio = cad;
    sec->cvpc=0;
}

Palabra* leerPalabra(SecuenciaPal* sec,Palabra* palabra)
{
    while(*sec->cursor && !esLetra(*sec->cursor))
        sec->cursor++;

    if(!*sec->cursor){
        sec->finSecuencia = TRUE;
        return NULL;
    }

    palabra->iniPal = sec->cursor;

    while(*sec->cursor && esLetra(*sec->cursor))
        sec->cursor++;

    palabra->finPal = sec->cursor - 1;

    return palabra;
}

Palabra* escribirPalabra(SecuenciaPal* sec, Palabra* palabra, Palabra* palabraDest)
{
    palabraDest->iniPal = sec->cursor;
    for (char* act = palabra->iniPal; act<= palabra->finPal; act++, sec->cursor++)
        *sec->cursor = *act;

    palabraDest->finPal = sec->cursor -1;

    return palabraDest;
}

void formatearPalabra(Palabra* palabra)
{
    *palabra->iniPal = aMayus(*palabra->iniPal);

    for (char* act = palabra->iniPal + 1; act<=palabra->finPal; act++)
        *act = aMinus(*act);
}

int finSecuencia(const SecuenciaPal* sec)
{
    return sec->finSecuencia;
}

void escribirCaracter(SecuenciaPal* sec, char car)
{
    *sec->cursor = car;
    if ((sec->cursor + 1) - (sec->inicio) < TAM_LINEA)
        sec->cursor++;
}

int moverCursor(SecuenciaPal* sec, int offset)///Para ver, revisar de no pasarse del largo de cadena.
{
    if ((sec->cursor) - (sec->inicio) > TAM_LINEA)
        return ERROR_TAM_BUF;
    sec->cursor += offset;
    return TODO_OK;
}

char aMayus(char car)
{
    return (car>='A' && car<='Z')?car:car-('a'-'A');
}

char aMinus(char car)
{
    return (car>='a' && car<='z')?car:car+('a'-'A');
}

int esLetra(char car)
{
    return (car >= 'a' && car<='z') || (car >= 'A' && car<='Z');
}



//////////////////////////////////////////////////////////////////////////////

char* normalizarApYN(const char* aNormalizar, char* normalizada, char carSeparador, int cantPalPorDefecto)
{
    SecuenciaPal secO, secD;
    crearSecuencia(&secO, (char*)aNormalizar);
    crearSecuencia(&secD, normalizada);

    Palabra palO, palD;
    crearPalabra(&palO);//Necesario para inicializar en 0 esa variable.
    crearPalabra(&palD);

    secD.cvpc = buscarCaracter(&secO, carSeparador);//Mejorar esto con el caracter separador incluido en la estructura
    secD.caracterSeparador = &carSeparador;

    leerPalabraApYN(&secO, &palO);
    while(!finSecuencia(&secO)){
        escribirPalabraApYN(&secD, &palO, &palD);
        secD.cvpc==0?formatearPalApYNPalabra(&palD, cantPalPorDefecto, &secD):formatearPalApYNCaracteres(&palD, secD.cvpc, &secD);
        escribirCaracter(&secD, ' ');//Agregar ', '
        leerPalabraApYN(&secO, &palO);
    }

    moverCursor(&secD, -1);///Limite
    escribirCaracter(&secD, '\0');///Limite

    return normalizada;
}

Palabra* leerPalabraApYN(SecuenciaPal* sec,Palabra* pal)//Contar la cantidad de caracteres de palabras por si no encuentro
{
    while(*sec->cursor && !esLetra(*sec->cursor))
        sec->cursor++;

    if(!*sec->cursor){
        sec->finSecuencia = TRUE;
        return NULL;
    }

    pal->iniPal = sec->cursor;

    while(*sec->cursor && esLetra(*sec->cursor)){
        sec->cursor++;
        pal->contCar++;//Incrementa cuando hay letra||caracteres validos
    }

    pal->finPal = sec->cursor - 1;
    pal->numPal++;
    return pal;
}

Palabra* escribirPalabraApYN(SecuenciaPal* sec, Palabra* palO, Palabra* palD)
{
    palD->iniPal = sec->cursor;
    for (char* act = palO->iniPal; act<= palO->finPal; act++, sec->cursor++){
        *sec->cursor = *act;
        palD->contCar++;
    }

    palD->finPal = sec->cursor -1;
    palD->numPal++;

    return palD;
}

void formatearPalApYNPalabra(Palabra* pal, int cantPal, SecuenciaPal* sec)
{
    if (cantPal >= pal->numPal){//APELLIDO
        char* act = pal->iniPal;
        for (; act<=pal->finPal; act++)
            *act = aMayus(*act);
        if (cantPal == pal->numPal){
            *act = *sec->caracterSeparador;
            sec->cursor++;
        }
    }
    else{//Nombre
        *pal->iniPal = aMayus(*pal->iniPal);

        for (char* act = pal->iniPal + 1; act<=pal->finPal; act++)
            *act = aMinus(*act);
    }

}

void formatearPalApYNCaracteres(Palabra* pal, int numCar, SecuenciaPal* sec)
{
    if (numCar >= pal->contCar){//APELLIDO
        char* act = pal->iniPal;
        for (; act<=pal->finPal; act++)
            *act = aMayus(*act);
        if (numCar == pal->contCar){
            *act = *sec->caracterSeparador;
            sec->cursor++;
        }
    }
    else{//Nombre
        *pal->iniPal = aMayus(*pal->iniPal);

        for (char* act = pal->iniPal + 1; act<=pal->finPal; act++)
            *act = aMinus(*act);
    }
}

int buscarCaracter(SecuenciaPal* sec,char car)//PROBAR HACER CARACTER CONST
{
    int cont=0;

    while(!finSecuencia(sec))
        cont += cantCarVal(sec, car);
    if(!*sec->cursor)
        cont=0;

    sec->cursor = sec->inicio;
    sec->finSecuencia=FALSE;

    return cont;
}

int cantCarVal(SecuenciaPal* sec, char car)
{
    int cont=0;
    while (!esLetra(*sec->cursor) && *sec->cursor != car && *sec->cursor)
        sec->cursor++;
    if (*sec->cursor == car){
        sec->finSecuencia=TRUE;
        return cont;
    }
    while (esLetra(*sec->cursor) && *sec->cursor){
        sec->cursor++;
        cont++;
    }
    if(!*sec->cursor)
        sec->finSecuencia = TRUE;


    return cont;
}

void crearPalabra (Palabra* pal)
{
    pal->contCar=0;
    pal->numPal=0;
}

