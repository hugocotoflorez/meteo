#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meteo.h"




void fill_station_name(station_t *station)
{
    snprintf(station->name, STAT_NAME_L, STAT_NAME_F, station->longitude*STAT_NAME_I, station->latitude*STAT_NAME_I);
}


weatherdata_t* get_weatherdata(FILE* file, int* l)
{
    if (file==NULL)
    {
        perror("FILE ERROR");
        exit(1);
    }
    fseek(file, 0, 0);
    
    int data_n = 0;
    while (!feof(file)) 
        if(fgetc(file) == '\n') 
            ++data_n;
    *l = --data_n;


    fseek(file, 0, 0);

    weatherdata_t *data_vector = (weatherdata_t*) malloc(data_n * sizeof(weatherdata_t));
    
    if (data_vector==NULL)
    {
        perror("MEMORY ALLOCATION ERROR");
        exit(1);
    }

    while (fgetc(file) != '\n');

    int i = 0;
    while (fscanf(file, "\"%d/%d/%d\",\"%*f\",\"%*f\",\"%*d\",\"%lf\",\"%lf\",\"%lf\",\"%lf\",\"%lf\",\"%lf\",\n", 
            &data_vector[i].data.mm, 
            &data_vector[i].data.dd, 
            &data_vector[i].data.yy, 
            &data_vector[i].maxt, 
            &data_vector[i].mint, 
            &data_vector[i].prec, 
            &data_vector[i].wind, 
            &data_vector[i].rhum, 
            &data_vector[i].solar) == 9)
    {
      ++i;
    }
    fseek(file, 0, 0);
    return data_vector;
}


station_t get_station(FILE* file)
{
    if (file==NULL)
    {
        perror("FILE ERROR");
        exit(1);
    }

    station_t station; 

    while (fgetc(file) != '\n');

    fscanf(file, "\"%*d/%*d/%*d\",\"%lf\",\"%lf\",\"%d\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\"%*f\",\n", 
        &station.latitude, 
        &station.longitude, 
        &station.elevation);

    fseek(file, 0, 0);
    fill_station_name(&station);

    return station;
}


/*
Crear unha función capaz de ler un arquivo .csv cos datos meteorolóxicos recollidos nunha determinada estación, xerar unha estructura tipo WeatherStation, e devolver o punteiro correspondente. Esta función debe invocar outras fucións (pasándolle  o nome ou o punteiro  a un arquivo .csv) para obter o vector de estruturas tipo WeatherData, e unha estructura Station cos datos identificativos da estación. Para iso odedes usar fucións implementadas previamente, ou modificacións delas.
*/
weatherstation_t* get_weatherstation_fromfile(FILE* file) 
{
    if (file == NULL) 
    {
        perror("FILE ERROR");
        exit(1);
    }

    int l;
    weatherstation_t* weatherstation_data = (weatherstation_t*)malloc(sizeof(weatherstation_t));
    
    if (weatherstation_data == NULL)
    {
        perror("MEMORY ALLOCATION ERROR");
        exit(1);
    }

    weatherstation_data->weatherdata_arr = get_weatherdata(file, &l);
    weatherstation_data->data_len = l;
    weatherstation_data->station = get_station(file);

    return weatherstation_data;
}


/*
Crear unha función que a partires dunha lista de nomes de arquivos cree un vector de estruturas tipo WeatherStation, para almacenar os datos da rede de estacións na zona de interese. Esta función debe facer uso da anterior para cargar os datos de cada unha das estacións da rede.
*/
weatherstation_t* get_weatherstation_fromfilenames(char *file_arr[FILENAME_L], size_t length)
{
    FILE* f;
    weatherstation_t* weatherstation_arr = (weatherstation_t*)malloc(sizeof(weatherstation_t)*length);
    
    if (weatherstation_arr==NULL)
    {
        perror("MEMORY ALLOCATION ERROR");
        exit(1);
    }

    for (int i = 0; i < length; i++)
    {
        f = fopen(file_arr[i], "rt");
        if (f==NULL) 
        {
            printf("File %s not found", file_arr[i]);
            continue;
        } 
        weatherstation_arr[i] = *get_weatherstation_fromfile(f);
    }

    return weatherstation_arr;
}

/*
Crear unha función que dadas dúas datas e os datos tomados nunha rede de estacións meteorolóxica, nos devolva os valores de temperatura máxima e mínima rexistrados nese período e a estación onde ser rexistrou cada un deles. Pensade no xeito máis axeitado para devolver todos eses datos.
*/
temppeaks_t get_temperature_peaks(weatherstation_t* weatherstation_arr, size_t length, data_t data1, data_t data2)
{
    int dist = calcular_distancia(data1, data2) +1;
    int initial_dist = data_compare(data1, data2)? 
            calcular_distancia((data_t){1,1,2000}, data1) :
            calcular_distancia((data_t){1,1,2000}, data2) ;

    temppeaks_t temppeaks;
    temppeaks.maxt_data.value = -100; //valor menor que cualquier otro
    temppeaks.mint_data.value = 100;  //valor mayor que cualquier otro

    

    for(int i = 0; i < length; i++)
    for(int j = initial_dist; j < initial_dist + dist; j++)
    {
        if (weatherstation_arr[i].weatherdata_arr[j].maxt > temppeaks.maxt_data.value)
        {
            temppeaks.maxt_data.value = weatherstation_arr[i].weatherdata_arr[j].maxt;
            temppeaks.maxt_data.station = weatherstation_arr[i].station;
            temppeaks.maxt_data.data = weatherstation_arr[i].weatherdata_arr[j].data;
        }
        if (weatherstation_arr[i].weatherdata_arr[j].mint < temppeaks.mint_data.value)
        {
            temppeaks.mint_data.value = weatherstation_arr[i].weatherdata_arr[j].mint;
            temppeaks.mint_data.station = weatherstation_arr[i].station;
            temppeaks.mint_data.data = weatherstation_arr[i].weatherdata_arr[j].data;
        }
    }

    return temppeaks;
}

/*
Crear unha función que dada unha data e os datos tomados nunha rede de estacións meteorolóxica, nos evolva os valores medios de temperaturas máximas e mínimas nesa área xeográfica.
*/
mediumtemppeaks_t get_temperature_mediumpeaks(weatherstation_t* weatherstation_arr, size_t length, data_t data)
{
    double maxt_sum = 0, 
           mint_sum = 0;
    int dist = calcular_distancia((data_t){1,1,2000}, data);

    for (int i = 0; i < length; i++)
    {
        maxt_sum += weatherstation_arr[i].weatherdata_arr[dist].maxt;
        mint_sum += weatherstation_arr[i].weatherdata_arr[dist].mint;
    }

    return (mediumtemppeaks_t){maxt_sum/length, mint_sum/length};
}


void free_weatherdata(weatherdata_t* weatherdata)
{
    free(weatherdata);
}


void free_weatherstation(weatherstation_t* weatherstation)
{
    free_weatherdata(weatherstation->weatherdata_arr);
    free(weatherstation);
}


void free_weatherstation_arr(weatherstation_t* weatherstation_arr, size_t length)
{
    for(int i = 0; i < length; i++)
        free_weatherdata(weatherstation_arr[i].weatherdata_arr);
    free(weatherstation_arr);
}



