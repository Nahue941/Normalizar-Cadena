#include "normalizar.h"

///Clase_2020-05-15_normalizar ANormalizar.txt Normalizado.txt
int main(int argc, char* argv[])
{
//    FILE*aNormalizarA = fopen(argv[ARG_ARCH_ENT], "r");
//    if (!aNormalizarA){
//        puts("Error al abrir el archivo de entrada");
//        return ERROR_ARCH;
//    }
//    FILE*normalizadoA = fopen(argv[ARG_ARCH_SAL], "w");
//    if (!normalizadoA){
//        puts("Error al abrir el archivo de salida");
//        return ERROR_ARCH;
//    }
//
//    char linea[TAM_LINEA];
//    char lineaNorm[TAM_LINEA];///bufer
//
//    while (fgets(linea, TAM_LINEA, aNormalizarA)){
//        normalizar(linea, lineaNorm);
//        fputs(lineaNorm, normalizadoA);
//        fputc('\n', normalizadoA);
//    }
//
//    fclose(aNormalizarA);
//    fclose(normalizadoA);
    char cad1[]={"      pAiVA$&*&$#@|gordIlLo0$&*  .,...   naHUEl ||||   / aLEjO"}, cad2[TAM_LINEA];
    printf("La cadena a normalizar: %s\n",cad1);
    normalizarApYN(cad1,cad2,'|',2);
    printf("La cadena normalizada: %s\n",cad2);
    return 0;
}


