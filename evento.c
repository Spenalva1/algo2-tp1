#include "evento_pesca.h"

#include <stdlib.h> // CAPAZ SOBRA

int main(int argc, char *argv[]){
    arrecife_t* arrecife = crear_arrecife(argv[argc-1]);
    acuario_t* acuario = crear_acuario();

    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
}







//  printf("DIRECCION: %p", (void *)arrecife);

