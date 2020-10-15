#include "evento_pesca.h"

#include <stdio.h> // CAPAZ SOBRA
#include <stdlib.h> // CAPAZ SOBRA
#include <string.h> // CAPAZ SOBRA

#define MAGIKARP "Magikarp"
#define VIOLETA "violeta"
#define RUTA_ACUARIO "acuario.txt"
#define ERROR -1
#define PESO_DIVISOR 75
#define VELOCIDAD_DIVISOR 60

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


int main(int argc, char *argv[]){

    arrecife_t* arrecife = crear_arrecife(argv[argc-1]);
    if(arrecife == NULL){
        return ERROR;
    }

    acuario_t* acuario = crear_acuario();
    if(acuario == NULL){
        liberar_arrecife(arrecife);
        return ERROR;
    }

    if(trasladar_pokemon(arrecife, acuario, &es_magikarp, 5) == ERROR){
        printf("No se realizó el traslado 1\n");
    }
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_veloz, 50) == ERROR){
        printf("No se realizó el traslado 2\n");
    }
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_pesado, 1) == ERROR){
        printf("No se realizó el traslado 3\n");
    }
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_violeta, 5) == ERROR){
        printf("No se realizó el traslado 4\n");
    }
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &nombre_empieza_con_S, 2) == ERROR){
        printf("No se realizó el traslado 5\n");
    }
    censar_arrecife(arrecife, &mostrar_pokemon);

    guardar_datos_acuario(acuario, RUTA_ACUARIO);

    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
}
