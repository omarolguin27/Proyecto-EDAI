#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "pedido.h"

void CrearPedido(Pedido* p) {
    printf("Nombre del cliente: ");
    fgets(p->nombreCliente, MAX_STR, stdin);
    strtok(p->nombreCliente, "\n");

    printf("Primer tiempo (entrada): ");
    fgets(p->primerTiempo, MAX_STR, stdin);
    strtok(p->primerTiempo, "\n");

    printf("Segundo tiempo (plato fuerte): ");
    fgets(p->segundoTiempo, MAX_STR, stdin);
    strtok(p->segundoTiempo, "\n");

    printf("Acompañamiento: ");
    fgets(p->acompanamiento, MAX_STR, stdin);
    strtok(p->acompanamiento, "\n");
}

void MostrarPedido(const Pedido* p) {
    printf("\n--- Pedido ---\n");
    printf("Cliente: %s\n", p->nombreCliente);
    printf("Entrada: %s\n", p->primerTiempo);
    printf("Plato fuerte: %s\n", p->segundoTiempo);
    printf("Acompañamiento: %s\n", p->acompanamiento);
}

void MostrarTodos(Queue* cola) {
    if (Queue_IsEmpty(cola)) {
        printf("No hay pedidos en cola.\n");
        return;
    }

    printf("\n== Lista de pedidos en cola ==\n");
    for (size_t i = 0; i < cola->len; i++) {
        size_t idx = (cola->front + i) % cola->capacity;
        MostrarPedido(&cola->queue[idx]);
    }
}

int main() {
    const size_t capacidadInicial = 10;
    Queue* cola = Queue_New(capacidadInicial);

    int opcion;
    do {
        do {
            printf("\n1. Agregar pedido\n2. Atender pedido\n3. Ver pedidos en cola\n4. Ver primer pedido\n0. Salir\nOpción: ");
            if (scanf("%d", &opcion) != 1) {
                printf("Error: Debes ingresar un número válido.\n");
                while (getchar() != '\n');
                opcion = -1;
            } else if (opcion < 0 || opcion > 4) {
                printf("Error: Opción inválida. Inténtalo de nuevo.\n");
                opcion = -1;
            } else {
                getchar();
            }
        } while (opcion == -1);

        switch(opcion) {
            case 1: {
                Pedido nuevo;
                CrearPedido(&nuevo);
                Queue_Enqueue(cola, nuevo);
                break;
            }
            case 2: {
                if (!Queue_IsEmpty(cola)) {
                    Pedido atendido = Queue_Dequeue(cola);
                    printf("\nPedido atendido:\n");
                    MostrarPedido(&atendido);
                } else {
                    printf("No hay pedidos en cola.\n");
                }
                break;
            }
            case 3: {
                MostrarTodos(cola);
                break;
            }
            case 4: {
                if (!Queue_IsEmpty(cola)) {
                    Pedido primero = Queue_Front(cola);
                    printf("\nPrimer pedido en la cola:\n");
                    MostrarPedido(&primero);
                } else {
                    printf("No hay pedidos en cola.\n");
                }
                break;
            }
            case 0:
                break;
        }

    } while(opcion != 0);

    Queue_Delete(&cola);
    return 0;
}
