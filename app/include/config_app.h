#ifndef CONFIG_APP_H
#define CONFIG_APP_H

#include <commons/config.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shared_utils.h"
#include <string.h>

typedef struct {
    char* ip_comanda;
    char* puerto_comanda;
    char* puerto_escucha;
    int grado_multiprocesamiento;
    char* algoritmo_planificacion;
    double alpha;
    int estimacion_inicial;
    char** repartidores;
    char** frecuencia_descanso;
    char** tiempo_descanso;
    char* ruta_log;
    int platos_default;
    int posicion_rest_default_x;
    int posicion_rest_default_y;
} t_app_config;

t_app_config* app_config;
t_log* logger;

t_app_config* app_config_loader(char* path_config_file);
void app_config_parser(t_config* config, t_app_config* app_config);
void app_destroy(t_app_config* app_config);

#endif