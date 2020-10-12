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

bool es_magikarp(pokemon_t* pokemon){
    return strcmp(pokemon->especie, MAGIKARP) == 0;
}

bool es_violeta(pokemon_t* pokemon){
    return strcmp(pokemon->color, VIOLETA) == 0;
}

bool es_pesado(pokemon_t* pokemon){
    return pokemon->peso >= PESO_DIVISOR;
}

bool es_veloz(pokemon_t* pokemon){
    return pokemon->velocidad >= VELOCIDAD_DIVISOR;
}

bool nombre_empieza_con_S(pokemon_t* pokemon){
    return pokemon->especie[0] == 'S';
}

void mostrar_pokemon(pokemon_t* pokemon){
    printf("\tEspecie: %s - Velocidad: %d - Peso: %d - Color: %s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

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
        return ERROR;
    }

    if(trasladar_pokemon(arrecife, acuario, &es_magikarp, 1) == ERROR)
        return ERROR;
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_veloz, 1) == ERROR)
        return ERROR;
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_pesado, 1) == ERROR)
        return ERROR;
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &es_violeta, 1) == ERROR)
        return ERROR;
    censar_arrecife(arrecife, &mostrar_pokemon);

    if(trasladar_pokemon(arrecife, acuario, &nombre_empieza_con_S, 2) == ERROR)
        return ERROR;
    censar_arrecife(arrecife, &mostrar_pokemon);

    guardar_datos_acuario(acuario, RUTA_ACUARIO);
    
    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
}







    // printf("\t%s - %s\n", pokemon->especie, MAGIKARP);

    // printf("DIRECCION: %p\n", (void *)arrecife);
// for(int i = 0; i < arrecife->cantidad_pokemon; i++){
//         printf("pokemon %d: %s %d %d %s\n", i, arrecife->pokemon[i].especie, arrecife->pokemon[i].peso, arrecife->pokemon[i].velocidad, arrecife->pokemon[i].color);
// }