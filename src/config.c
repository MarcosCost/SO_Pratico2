/// Config - A simple ADT to Parse and store server.config values
///
/// Marcos Costa 125882
/// José Mendes  114429
/// 2025

#include "config.h"

int getConfigs(Config* config){

    FILE *file = fopen(FILE_LOC, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGHT];
    int line_count = 0;

    while (fgets(line, sizeof(line), file) != NULL && line_count < 8) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        
        // Find the '=' character
        char *value = strchr(line, '=');
        if (value == NULL) {
            continue; // Skip lines without '='
        }
        value++; // Move past the '=' character

        // Assign to struct based on line number
        switch(line_count) {
            case 0: config->port = atoi(value); break;
            case 1: 
                strncpy(config->document_root, value, MAX_VALUE_LENGHT - 1);
                config->document_root[MAX_VALUE_LENGHT - 1] = '\0';
                break;
            case 2: config->num_workers = atoi(value); break;
            case 3: config->thread_per_worker = atoi(value); break;
            case 4: config->max_queue = atoi(value); break;
            case 5:
                strncpy(config->log_file, value, MAX_VALUE_LENGHT - 1);
                config->log_file[MAX_VALUE_LENGHT - 1] = '\0';
                break;
            case 6: config->cache_size = atoi(value); break;
            case 7: config->timeout = atoi(value); break;
        }
        
        line_count++;
    }

    fclose(file);
    return 1;
}

Config* initConfigs(){
    static Config config;   //static makes it so there is a single shared instance of config

    //Inicialize config to 0s to avoid garbage data
    memset(&config, 0, sizeof(Config));

    getConfigs(&config);
    return &config;
}

void print_config(const Config *config) {
    printf("=== Server Configuration ===\n");
    printf("Port: %d\n", config->port);
    printf("Document Root: %s\n", config->document_root);
    printf("Number of Workers: %d\n", config->num_workers);
    printf("Threads per Worker: %d\n", config->thread_per_worker);
    printf("Max Queue Size: %d\n", config->max_queue);
    printf("Log File: %s\n", config->log_file);
    printf("Cache Size: %d MB\n", config->cache_size);
    printf("Timeout: %d seconds\n", config->timeout);
    printf("============================\n");
}

//Getters
int get_port(Config* config)               { return config->port; }
char* get_document_root(Config* config)    { return config->document_root; }
int get_num_workers(Config* config)        { return config->num_workers; }
int get_thread_per_worker(Config* config)  { return config->thread_per_worker; }
int get_max_queue(Config* config)          { return config->max_queue; }
char* get_log_file(Config* config)         { return config->log_file; }
mb get_cache_size(Config* config)          { return config->cache_size; }
secs get_timeout(Config* config)           { return config->timeout; }

int main(void){
    Config* cfg = initConfigs();
    print_config(cfg);
}