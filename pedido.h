#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_STR 100

typedef struct {
    char nombreCliente[MAX_STR];
    char primerTiempo[MAX_STR];
    char segundoTiempo[MAX_STR];
    char acompanamiento[MAX_STR];  // Campo renombrado
} Pedido;

#endif
