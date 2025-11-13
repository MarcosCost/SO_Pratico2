/// Config - A simple ADT to Parse and store server.config values
///
/// Marcos Costa 125882
/// José Mendes  114429
/// 2025

#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_LOC "server.conf"
#define MAX_VALUE_LENGHT 100
#define MAX_LINE_LENGHT 130

typedef int mb;
typedef int secs;

//Defenir estrutura que armazena as configuraçoes
struct config
{
    int port;
    char document_root[MAX_VALUE_LENGHT];
    int num_workers;
    int thread_per_worker;
    int max_queue;
    char log_file[MAX_VALUE_LENGHT];
    mb cache_size;
    secs timeout;
};
typedef struct config Config;


//Returns -1 if the config structure isnt properly initialized
int getConfigs(Config *config);

//Returns an Config structure, all set up
Config* initConfigs();

//List Configs:
void print_config(const Config *config);

///Getters
//Parameter: adress & of config obj
int get_port(Config* config);  
char* get_document_root(Config* config);
int get_num_workers(Config* config);
int get_thread_per_worker(Config* config);
int get_max_queue(Config* config);
char* get_log_file(Config* config);
mb get_cache_size(Config* config);
secs get_timeout(Config* config);

#endif