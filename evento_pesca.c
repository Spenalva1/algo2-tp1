#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FORMATO_POKEMON "%[^;];%i;%i;%[^\n]\n"

arrecife_t* crear_arrecife(const char* ruta_archivo){
  FILE* archivo_arrecife = fopen(ruta_archivo, "r");
  if(!archivo_arrecife){
    printf("No se pudo abrir %s!\n", ruta_archivo);
    return NULL;
  }


  arrecife_t* arrecife = malloc(sizeof(arrecife_t));
  if(arrecife == NULL){
    fclose(archivo_arrecife);
    return NULL;
  }

  (*arrecife).cantidad_pokemon = 0;
  (*arrecife).pokemon = NULL;
  pokemon_t pokemon_leido;

  bool error = false;
  int leidos = fscanf(archivo_arrecife, "%[^;];%i;%i;%[^\n]\n", pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);

  while (leidos == 4 && !error){
    ((*arrecife).cantidad_pokemon)++;
    pokemon_t* nuevo_pokemon_ptr = realloc((*arrecife).pokemon, sizeof(pokemon_t) * (*arrecife).cantidad_pokemon);
    (*arrecife).pokemon = nuevo_pokemon_ptr;
    
    if(arrecife->pokemon == NULL)
      error = true;

    *(arrecife->pokemon + arrecife->cantidad_pokemon - 1) = pokemon_leido;
    
    leidos = fscanf(archivo_arrecife, "%[^;];%i;%i;%[^\n]\n", pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
  }


  fclose(archivo_arrecife);
  if(error){
    return NULL;
  }
  return arrecife;
}

acuario_t* crear_acuario(){
  return malloc(sizeof(acuario_t));
}

void liberar_arrecife(arrecife_t* arrecife){
    free((*arrecife).pokemon);
    free(arrecife);
}

void liberar_acuario(acuario_t* acuario){
    free((*acuario).pokemon);
    free(acuario);
}



