#ifndef SINDICATO_FS_H
#define SINDICATO_FS_H

#include <sys/stat.h>
#include <dirent.h>
#include "sindicato_config.h"

// VARIABLES Y ESTRUCTURAS
typedef struct {
    char* block_size;
    char* blocks;
    char* magic_number;
} t_sindicato_metadata;

t_sindicato_metadata* sindicato_metadata;

// FUNCIONES
void get_or_create_fs();
int get_or_create_metadata();
int get_or_create_montaje_point();
void crear_metadata_default();
void leer_metadata_afip();
void crear_bitmap();

#endif
