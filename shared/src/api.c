#include "api.h"


int obtener_numero_mensaje(char* mensaje_tipo){

    if(strcmp(mensaje_tipo, "guardar_pedido") == 0){
        
        return guardar_pedido;

    } else if(strcmp(mensaje_tipo, "consultar_restaurantes") == 0){
        
        return consultar_restaurantes;

    } else if(strcmp(mensaje_tipo, "seleccionar_restaurante") == 0){
        
        return seleccionar_restaurante;

    } else if(strcmp(mensaje_tipo, "obtener_restaurante") == 0){
        
        return obtener_restaurante;

    } else if(strcmp(mensaje_tipo, "consultar_platos") == 0){
        
        return consultar_platos;

    } else if(strcmp(mensaje_tipo, "crear_pedido") == 0){
        
        return crear_pedido;

    } else if(strcmp(mensaje_tipo, "anadir_plato") == 0){
        
        return anadir_plato;

    } else if(strcmp(mensaje_tipo, "guardar_plato") == 0){
        
        return guardar_plato;

    } else if(strcmp(mensaje_tipo, "confirmar_pedido") == 0){
        
        return confirmar_pedido;

    } else if(strcmp(mensaje_tipo, "plato_listo") == 0){
        
        return plato_listo;

    } else if(strcmp(mensaje_tipo, "consultar_pedido") == 0){
        
        return consultar_pedido;

    } else if(strcmp(mensaje_tipo, "obtener_pedido") == 0){
        
        return obtener_pedido;

    } else if(strcmp(mensaje_tipo, "finalizar_pedido") == 0){
        
        return finalizar_pedido;

    } else if(strcmp(mensaje_tipo, "terminar_pedido") == 0){
        
        return terminar_pedido;

    } else if(strcmp(mensaje_tipo, "obtener_receta") == 0){
        
        return obtener_receta;

    } 
    return -1;
};



char* enviar_mensaje_guardar_pedido(t_modulo* modulo, char* restaurante, char* id_pedido){

    if(restaurante == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }

    char* tipo_mensaje = string_itoa(guardar_pedido);

    char* guardad_pedido_mensajes[3] = {tipo_mensaje, restaurante, id_pedido};
    int socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, guardad_pedido_mensajes, 3);

    t_mensajes* respuesta = receive_simple_messages(socket);

    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    }
     printf("\n");

    liberar_conexion(socket);

    return respuesta->mensajes[0];
}


char** enviar_mensaje_consultar_restaurantes(t_modulo* modulo){
    
    char* tipo_mensaje = string_itoa(consultar_restaurantes);
    char* get_restaurantes[1] = {tipo_mensaje};
    int socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, get_restaurantes, 1);

    t_mensajes* respuesta = receive_simple_messages(socket);

    char** respuesta_restaurantes = malloc(sizeof(char*) * *respuesta->size);

    for (int i= 0; i < *respuesta->size; i++){
        printf("%s ", respuesta->mensajes[i]);
        respuesta_restaurantes [i] = respuesta->mensajes[i];
    }
    printf("\n");

    liberar_conexion(socket);

    return respuesta_restaurantes;

}

char* enviar_mensaje_seleccionar_restaurante(t_modulo* modulo, char* id_cliente, char* nombre_restaurante){

    if(nombre_restaurante == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(seleccionar_restaurante);

    //TODO: Definir como se elige el ID del cliente
    char* seleccionar_restaurantes[3] = {tipo_mensaje, id_cliente, nombre_restaurante};
    int socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, seleccionar_restaurantes, 3);

    t_mensajes* respuesta = receive_simple_messages(socket);

    for (int i= 0; i < *respuesta->size; i++){
        printf(" %s ", respuesta->mensajes[i]);
    }
    printf("\n");

    char* respuesta_seleccion_restaurante = respuesta->mensajes[0];

    liberar_conexion(socket);

    return respuesta_seleccion_restaurante;
}

char* enviar_mensaje_crear_pedido(t_modulo* modulo){

    char* tipo_mensaje = string_itoa(crear_pedido);
    char* crear_pedido_mensajes[1] = {tipo_mensaje};
    int socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, crear_pedido_mensajes, 1);

    t_mensajes* respuesta = receive_simple_messages(socket);

    char* id_pedido = respuesta->mensajes[0];
    printf("%s\n", id_pedido);

    liberar_conexion(socket);

    return id_pedido;
}

r_obtener_restaurante* enviar_mensaje_obtener_restaurante(t_modulo* modulo, char* restaurante){

    if(restaurante == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(obtener_restaurante);
    char* obtener_restaurante[2] ={tipo_mensaje,restaurante};
    int socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, obtener_restaurante, 2);

    t_mensajes* respuesta = receive_simple_messages(socket);

    r_obtener_restaurante* respuesta_obtener_restaurante = malloc (sizeof(r_obtener_restaurante));

    respuesta_obtener_restaurante->afinidades = obtener_array_mensajes(respuesta->mensajes[0]);;
    respuesta_obtener_restaurante->pos_x = respuesta->mensajes[1];
    respuesta_obtener_restaurante->pos_y = respuesta->mensajes[2];
    respuesta_obtener_restaurante->recetas = obtener_receta_precios(respuesta->mensajes[3]) ;
    respuesta_obtener_restaurante->cantidad_hornos = respuesta->mensajes[4];
    respuesta_obtener_restaurante->cantidad_pedidos = respuesta->mensajes[5];


    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    }
     printf("\n");

    liberar_conexion(socket);

    return respuesta_obtener_restaurante;

}

char** obtener_array_mensajes(char* array_mensaje){

    char** array_string = string_split(array_mensaje, ",");

    return array_string;

}

receta_precio** obtener_receta_precios(char* array_mensajes){

    char** array_string = string_split(array_mensajes, "|");

    receta_precio** receta_precio_final = malloc ( sizeof(receta_precio) * sizeof(receta_precio) );

    for(int i = 0; array_string[i]!=NULL; i++){
        char** receta_precio_individual = string_split(array_string[i], ",");

        receta_precio_final[i]->receta = receta_precio_individual[0];
        receta_precio_final[i]->precio = receta_precio_individual[1];

    }

    return receta_precio_final;
}


char** enviar_mensaje_consultar_platos(t_modulo* modulo, char* restaurante){

    if(restaurante == NULL){
        printf("Faltan parametros \n");
        return NULL;;
    }
  
    char* tipo_mensaje = string_itoa(consultar_platos);
    int socket ;

    if(!strcmp((modulo->nombre),"sindicato")){
        char* consulta_platos[2] ={tipo_mensaje,restaurante};
        socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, consulta_platos, 2);
    }else{
        socket = send_message_and_return_socket(modulo->ip, modulo->puerto, tipo_mensaje);
    }

    t_mensajes* respuesta = receive_simple_messages(socket);

    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    }
    printf("\n");
    
    liberar_conexion(socket);

    return obtener_array_mensajes(respuesta->mensajes[0]);
}

char* enviar_mensaje_anadir_plato(t_modulo* modulo, char* plato, char* id_pedido){

    if(plato == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }

    char* tipo_mensaje = string_itoa(anadir_plato);
    int socket;

    char* anadir_plato[3] ={tipo_mensaje,plato, id_pedido};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, anadir_plato, 3);
    
    t_mensajes* respuesta = receive_simple_messages(socket);

    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    }
    printf("\n");
    
    liberar_conexion(socket);

    return respuesta->mensajes[0];
};

char* enviar_mensaje_guardar_plato(t_modulo* modulo, char* restaurante, char* id_pedido, char* comida, char* cantidad){

    if(restaurante == NULL || id_pedido == NULL || comida == NULL || cantidad == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }

    char* tipo_mensaje = string_itoa(guardar_plato);
    int socket;

    char* guardar_plato[5] ={tipo_mensaje,restaurante, id_pedido, comida, cantidad};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, guardar_plato, 5);
    
   t_mensajes* respuesta = receive_simple_messages(socket);

   printf("%s \n", respuesta->mensajes[0]);


    liberar_conexion(socket);

    return respuesta->mensajes[0];
};

char* enviar_mensaje_confirmar_pedido(t_modulo* modulo,char* id_pedido, char* restaurante){
   
    if(restaurante == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(confirmar_pedido);
    int socket;

    char* confirmar_pedido[3] ={tipo_mensaje, id_pedido, restaurante};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, confirmar_pedido, 3);
    
   t_mensajes* respuesta = receive_simple_messages(socket);

    printf("%s \n", respuesta->mensajes[0]);

    liberar_conexion(socket);

    return respuesta->mensajes[0];

};

char* enviar_mensaje_plato_listo(t_modulo* modulo, char* restaurante, char* id_pedido, char* comida){

    if(restaurante == NULL || id_pedido == NULL || comida == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(plato_listo);
    int socket;

    char* plato_listo[4] ={tipo_mensaje, restaurante, id_pedido, comida};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, plato_listo, 4);
    
   t_mensajes* respuesta = receive_simple_messages(socket);

    printf("%s \n", respuesta->mensajes[0]);

    liberar_conexion(socket);

    return respuesta->mensajes[0];
};

r_consultar_pedido* enviar_mensaje_consultar_pedido(t_modulo* modulo, char* id_pedido){

    if(id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }

    char* tipo_mensaje = string_itoa(consultar_pedido);
    int socket;

    char* consultar_pedido[2] ={tipo_mensaje, id_pedido};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, consultar_pedido, 2);
    
    t_mensajes* respuesta = receive_simple_messages(socket);

    r_consultar_pedido* respuesta_consulta_pedido = malloc(sizeof(r_consultar_pedido));

    respuesta_consulta_pedido->restaurante = respuesta->mensajes[0];
    respuesta_consulta_pedido->estado = respuesta->mensajes[1];
    respuesta_consulta_pedido->info_comidas = obtener_informacion_comidas(respuesta->mensajes[2]);


    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    } printf("\n");

    liberar_conexion(socket);

    return NULL;

};


informacion_comidas** obtener_informacion_comidas(char* array_mensajes){

    char** array_string = string_split(array_mensajes, "|");

    informacion_comidas** informacion_comidas_final = malloc ( sizeof(informacion_comidas) * sizeof(informacion_comidas) );

    for(int i = 0; array_string[i]!=NULL; i++){
        char** info_comidas_individual = string_split(array_string[i], ",");

        informacion_comidas_final[i]->comida = info_comidas_individual[0];
        informacion_comidas_final[i]->cantidad_total = info_comidas_individual[1];
        informacion_comidas_final[i]->cantidad_lista = info_comidas_individual[2];

    }

    return informacion_comidas_final;

};

r_obtener_pedido* enviar_mensaje_obtener_pedido(t_modulo* modulo, char* id_pedido,char* restaurante){

    if(restaurante == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(obtener_pedido);
    int socket;

    char* obtener_pedido[3] ={tipo_mensaje, id_pedido, restaurante};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, obtener_pedido, 3);

    t_mensajes* respuesta = receive_simple_messages(socket);

    for (int i= 0; i < *respuesta->size; i++){
       printf("%s ", respuesta->mensajes[i]);
    } printf("\n");

    r_obtener_pedido* respuesta_obtener_pedido = malloc(sizeof(r_obtener_pedido));

    respuesta_obtener_pedido->estado = respuesta->mensajes[0];
    respuesta_obtener_pedido->info_comidas = obtener_informacion_comidas(respuesta->mensajes[1]);

    liberar_conexion(socket);

    return respuesta_obtener_pedido;
}


char* enviar_mensaje_finalizar_pedido(t_modulo* modulo, char* id_pedido,char* restaurante){

    if(restaurante == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(finalizar_pedido);
    int socket;

    char* finalizar_pedido[3] ={tipo_mensaje, id_pedido, restaurante};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, finalizar_pedido, 3);

    t_mensajes* respuesta = receive_simple_messages(socket);

    printf("%s \n" ,respuesta->mensajes[0]);

    liberar_conexion(socket);
    
    return respuesta->mensajes[0];
}

char* enviar_mensaje_terminar_pedido(t_modulo* modulo, char* id_pedido,char* restaurante){

    if(restaurante == NULL || id_pedido == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }
    
    char* tipo_mensaje = string_itoa(terminar_pedido);
    int socket;

    char* terminar_pedido[3] ={tipo_mensaje, id_pedido, restaurante};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, terminar_pedido, 3);
    
    t_mensajes* respuesta = receive_simple_messages(socket);

    printf("%s \n" , respuesta->mensajes[0]);

    liberar_conexion(socket);
    
    return respuesta->mensajes[0];
    
}

char* enviar_mensaje_obtener_receta(t_modulo* modulo, char* nombre_plato){

    if(nombre_plato == NULL){
        printf("Faltan parametros \n");
        return NULL;
    }

    char* tipo_mensaje = string_itoa(obtener_receta);
    int socket;

    char* obtener_receta[2] ={tipo_mensaje, nombre_plato};
    socket = send_messages_and_return_socket(modulo->ip, modulo->puerto, obtener_receta, 2);
    
    t_mensajes* respuesta = receive_simple_messages(socket);

    printf("%s \n" , respuesta->mensajes[0]);

    liberar_conexion(socket);
    
    return respuesta->mensajes[0];
}



