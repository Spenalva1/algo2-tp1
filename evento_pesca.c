#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FORMATO_POKEMON_LECTURA "%100[^;];%i;%i;%100[^\n]\n"
#define FORMATO_POKEMON_ESCRITURA "%s;%i;%i;%s\n"
#define CANT_A_LEER 4
#define SIN_ERROR 0
#define ERROR -1

/*
* cuenta cuandos pokemones del arrecife recibido cumplen con la condicion seleccionar_pokemon.
* devuelve TRUE si la cantidad que cumple es mayor o igual a cant_seleccion
* devuelve FALSE en caso contrario
*/
bool hay_pokemones_suficientes (arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
  int encontrados = 0;
  bool suficientes = false;
  int i = 0;

  while(i < arrecife->cantidad_pokemon && !suficientes){
    if((*seleccionar_pokemon)((arrecife->pokemon)+i)){
      encontrados++;
      if(encontrados >= cant_seleccion)
        suficientes = true;
    }
    i++;
  }
  return suficientes;
}

/*
* agrega el pokemon recibido por parametro en la direccion recibida en el puntero arrecife
* retorna SIN_ERROR en caso de exito y ERROR en caso contrario.
*/
int agregar_pokemon_a_arrecife(arrecife_t* arrecife, pokemon_t pokemon){
  pokemon_t* nuevo_vector_pokemon;
  (arrecife->cantidad_pokemon)++;
  nuevo_vector_pokemon = realloc(arrecife->pokemon, sizeof(pokemon_t) * (size_t)arrecife->cantidad_pokemon);
  
  if(nuevo_vector_pokemon == NULL){
    (arrecife->cantidad_pokemon)--;
    return ERROR;
  }
  arrecife->pokemon = nuevo_vector_pokemon;
  *(arrecife->pokemon + arrecife->cantidad_pokemon - 1) = pokemon;
  return SIN_ERROR;
}

/*
* agrega el pokemon recibido por parametro en la direccion recibida en el puntero acuario
* retorna SIN_ERROR en caso de exito y ERROR en caso contrario.
*/
int agregar_pokemon_a_acuario(acuario_t* acuario, pokemon_t pokemon){
  (acuario->cantidad_pokemon)++;
  pokemon_t* nuevo_vector_pokemon = realloc(acuario->pokemon, sizeof(pokemon_t) * (size_t)acuario->cantidad_pokemon);
  if(nuevo_vector_pokemon == NULL){
    (acuario->cantidad_pokemon)--;
    return ERROR;
  }
  acuario->pokemon = nuevo_vector_pokemon;
  *(acuario->pokemon + acuario->cantidad_pokemon - 1) = pokemon;
  return SIN_ERROR;
}

/*
* quita el pokemon de la pocision i del vector de pokemon_t ubicado la direccion recibida en el puntero arrecife
* i debe ser mayor que el valor entero ubicado en arrecife->cantidad_pokemon
* retorna SIN_ERROR en caso de exito y ERROR en caso contrario.
*/
int sacar_pokemon_de_arrecife(arrecife_t* arrecife, int i){
  pokemon_t pokemon_aux = *(arrecife->pokemon + arrecife->cantidad_pokemon - 1);
  (arrecife->cantidad_pokemon)--;
  if(arrecife->cantidad_pokemon == 0)
    return SIN_ERROR;
  pokemon_t* nuevo_vector_pokemon = realloc(arrecife->pokemon, sizeof(pokemon_t) * (size_t)arrecife->cantidad_pokemon);
  if(nuevo_vector_pokemon == NULL){
    (arrecife->cantidad_pokemon)++;
    return ERROR;
  }
  arrecife->pokemon = nuevo_vector_pokemon;
  if(i < arrecife->cantidad_pokemon)
    arrecife->pokemon[i] = pokemon_aux;
  return SIN_ERROR;
}

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

  arrecife->cantidad_pokemon = 0;
  arrecife->pokemon = NULL;
  pokemon_t pokemon_leido;

  bool error = false;
  int leidos = fscanf(archivo_arrecife, FORMATO_POKEMON_LECTURA, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);

  while (leidos == CANT_A_LEER && !error){

    if(agregar_pokemon_a_arrecife(arrecife, pokemon_leido) == ERROR)
      error = true;
    
    leidos = fscanf(archivo_arrecife, FORMATO_POKEMON_LECTURA, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
  }

  fclose(archivo_arrecife);

  if(error || arrecife->cantidad_pokemon == 0){
    printf("Hubo un error en la lectura de pokemones.\n");
    free(arrecife);
    return NULL;
  }

  return arrecife;
}

acuario_t* crear_acuario(){
  acuario_t* acuario = malloc(sizeof(acuario_t));
  acuario->cantidad_pokemon = 0;
  acuario->pokemon = NULL;
  return acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
  if (cant_seleccion <= 0)
    return SIN_ERROR;

  if(!hay_pokemones_suficientes(arrecife, seleccionar_pokemon, cant_seleccion))
    return ERROR;

  int encontrados = 0;
  int i = 0;
  bool error = false;
  while(i < arrecife->cantidad_pokemon && !error && encontrados < cant_seleccion){
    if((*seleccionar_pokemon)((arrecife->pokemon)+i)){
      
      encontrados++;

      if(agregar_pokemon_a_acuario(acuario, arrecife->pokemon[i]) == ERROR)
        error = true;

      if(sacar_pokemon_de_arrecife(arrecife, i) == ERROR)
        error = true;

    }else{
      i++;
    }
  }

  if(error)
    return ERROR;

  return SIN_ERROR;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
  printf("------------------------------------------------------------------------------------------\n");
  printf("Pokemones restantes en el arrecife (%d):\n", arrecife->cantidad_pokemon);
  for(int i = 0; i < arrecife->cantidad_pokemon; i++){
    (*mostrar_pokemon)((arrecife->pokemon)+i);
  }
  printf("\n------------------------------------------------------------------------------------------\n");
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
  FILE* acuario_archivo = fopen(nombre_archivo, "w");
  if(!acuario_archivo){
    printf("No se pudo crear %s!\n", nombre_archivo);
    return ERROR;
  }
  for(int i = 0; i < acuario->cantidad_pokemon; i++){
    fprintf(acuario_archivo, FORMATO_POKEMON_ESCRITURA, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
  }
  fclose(acuario_archivo);
  return SIN_ERROR;
}

void liberar_arrecife(arrecife_t* arrecife){
  free((*arrecife).pokemon);
  free(arrecife);
}

void liberar_acuario(acuario_t* acuario){
  if(acuario->cantidad_pokemon > 0)
    free((*acuario).pokemon);
  free(acuario);
}



