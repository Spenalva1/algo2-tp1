#include "evento_pesca.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAGIKARP "Magikarp"
#define VIOLETA "violeta"
#define RUTA_ACUARIO "acuario.txt"
#define ERROR -1
#define SIN_ERROR 0
#define PESO_DIVISOR 75
#define VELOCIDAD_DIVISOR 60
#define MAX_RUTA 100
#define TXT ".txt"

/* 
*   Devuelve TRUE si el valor recibido contiene la ruta de un archivo .txt
*   En caso contrario imprime en pantalla que el archivo no cumple la condicion y retorna FALSE
*/
bool es_txt_valido(char ruta[MAX_RUTA]){
    if(strcmp(ruta+strlen(ruta)-4, TXT)==0){
        if(strlen(ruta) > 4){
            return true;
        }else{
            printf("Debe ingresar al menos un caracter además de la terminación '.txt'.\n");
        }
    }else{
        printf("Debe ingresar un nombre de archivo terminado en '.txt'.\n");
    }
    return false;
}

/*
*   devuelve TRUE si la especie del pokemon recibido es igual a MAGIKARP
*   en caso contrario devuelve FALSE
*/
bool es_magikarp(pokemon_t* pokemon){
    return strcmp(pokemon->especie, MAGIKARP) == 0;
}

/*
*   devuelve TRUE si el color del pokemon recibido es igual a VIOLETA
*   en caso contrario devuelve FALSE
*/
bool es_violeta(pokemon_t* pokemon){
    return strcmp(pokemon->color, VIOLETA) == 0;
}

/*
*   devuelve TRUE si el peso del pokemon recibido es mayor o igual a PESO_DIVISOR
*   en caso contrario devuelve FALSE
*/
bool es_pesado(pokemon_t* pokemon){
    return pokemon->peso >= PESO_DIVISOR;
}

/*
*   devuelve TRUE si la velocidad del pokemon recibido es mayor o igual a VELOCIDAD_DIVISOR
*   en caso contrario devuelve FALSE
*/
bool es_veloz(pokemon_t* pokemon){
    return pokemon->velocidad >= VELOCIDAD_DIVISOR;
}

/*
*   devuelve TRUE si la inicial de la especia del pokemon recibido es igual a S
*   en caso contrario devuelve FALSE
*/
bool nombre_empieza_con_S(pokemon_t* pokemon){
    return pokemon->especie[0] == 'S';
}

/*
*   imprime todos los datos del pokemon recibido en pantalla
*/
void mostrar_pokemon(pokemon_t* pokemon){
    printf("\tEspecie: %s - Velocidad: %d - Peso: %d - Color: %s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

/*
*   imprime el nombre del pokemon recibido en pantalla
*/
void mostrar_nombre_pokemon(pokemon_t* pokemon){
    printf("\t- %s\n", pokemon->especie);
}

/*
*   Detalla en pantalla el resultado del traslado el cual sera un mensaje de exito si resultado es igual a SIN_ERROR y sera de fallo si resultado es igual a ERROR.
*   numero_de_traslado representa el numero de traslado de pokemones realizado para indicarlo en pantalla
*/
void mostrar_resultado_de_traslado(int resultado, int numero_de_traslado){
    if(resultado == ERROR){
        printf("No se pudo realizar el traslado %d\n", numero_de_traslado);
    }else if (resultado == SIN_ERROR){
        printf("Traslado %d realizado con exito!\n", numero_de_traslado);
    }
}


int main(int argc, char *argv[]){

    if(!es_txt_valido(argv[argc-1]))
        return ERROR;

    arrecife_t* arrecife = crear_arrecife(argv[argc-1]);
    if(arrecife == NULL){
        return ERROR;
    }

    acuario_t* acuario = crear_acuario();
    if(acuario == NULL){
        liberar_arrecife(arrecife);
        return ERROR;
    }

    mostrar_resultado_de_traslado(trasladar_pokemon(arrecife, acuario, &es_magikarp, 0), 1);
    censar_arrecife(arrecife, &mostrar_pokemon);

    mostrar_resultado_de_traslado(trasladar_pokemon(arrecife, acuario, &es_veloz, 1), 2);
    censar_arrecife(arrecife, &mostrar_pokemon);

    mostrar_resultado_de_traslado(trasladar_pokemon(arrecife, acuario, &es_pesado, 1), 3);
    censar_arrecife(arrecife, &mostrar_pokemon);

    mostrar_resultado_de_traslado(trasladar_pokemon(arrecife, acuario, &es_violeta, 5), 4);
    censar_arrecife(arrecife, &mostrar_pokemon);

    mostrar_resultado_de_traslado(trasladar_pokemon(arrecife, acuario, &nombre_empieza_con_S, 2), 5);
    censar_arrecife(arrecife, &mostrar_pokemon);

    guardar_datos_acuario(acuario, RUTA_ACUARIO);

    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
    return SIN_ERROR;
}
