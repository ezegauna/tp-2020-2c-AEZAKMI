#include "config_handle.h"

t_restaurante* buscar_restaurante_lista(char* nombre_restaurante){

    for (IteratorList iter = beginlist(lista_restaurantes); iter != NULL; iter = nextlist(iter)){
        t_restaurante* restaurante = (t_restaurante*) iter->data;

        if (strcmp(restaurante->nombre_restaurante, nombre_restaurante) == 0){
            return restaurante;
        }

    }

    return NULL;

}

t_cliente* buscar_cliente_lista(char* id_cliente){

    for (IteratorList iter = beginlist(lista_clientes); iter != NULL; iter = nextlist(iter)){
        t_cliente* cliente = (t_cliente*) iter->data;

        if (strcmp(cliente->id_cliente, id_cliente) == 0){
            return cliente;
        }

    }

    return NULL;

}

void enviar_final_pedido(char* restaurante, int id_pedido){

    enviar_mensaje_finalizar_pedido(&modulo_comanda, string_itoa(id_pedido), restaurante);

}

t_pcb* crear_pcb(char* restaurante, int id_pedido, char* id_cliente){
    t_pcb* pcb = malloc(sizeof(t_pcb));
    pcb->restaurante = restaurante;
    pcb->id_pedido = id_pedido;
    pcb->cliente = id_cliente;
    pushbacklist(&pcb_new, pcb);
    sem_post(sem_pcb_new);
    return pcb;
}