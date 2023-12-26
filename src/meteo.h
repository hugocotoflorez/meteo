#ifndef _METEO_H
#define _METEO_H 1


#include <stdio.h>


#define month_len       {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
#define STAT_NAME_L     20                  // Station name length
#define STAT_NAME_F     "STAT%3.0f%2.0f"    // Station name format
#define STAT_NAME_I     10                  // Station name field increment (for lo & la)
#define FILENAME_L      32                  // Filename length with extension


/*
typedef struct __data
{
    int dd, mm, yy;
} data_t;
*/
typedef struct __data
{
    int dd, mm, yy;
} data_t;


/*
typedef struct __station
{
    char name[STAT_NAME_L];
    double longitude, latitude;
    int elevation;
} station_t;
*/
typedef struct __station
{
    char name[STAT_NAME_L];
    double longitude, latitude;
    int elevation;
} station_t;


/*
typedef struct __weatherdata
{
    data_t data;
    double max_t, min_t, prec, wind, rhum, solar;
} weatherdata_t;
*/
typedef struct __weatherdata
{
    data_t data;
    double maxt, mint, prec, wind, rhum, solar;
} weatherdata_t;

/*
Definir unha nova estrutura de datos  WheatherStation con dúas partes: unha correspondente aos datos meteorolóxicos e ás datas de recollida (vector de estuturas tipo WeatherData), e a outra para os datos da estación de recollida (estrutura tipo Station).

typedef struct __weatherstation
{
    station_t station;
    weatherdata_t *weatherdata_arr;
    int data_len;
} weatherstation_t;
*/
typedef struct __weatherstation
{
    station_t station;
    weatherdata_t *weatherdata_arr;
    int data_len;
} weatherstation_t;


/*
typedef struct __contextualdata
{
    double value;
    station_t station;
} contextualdata_t;
*/
typedef struct __contextualdata
{
    double value;
    station_t station;
    data_t data;
} contextualdata_t;


/*
typedef struct __temppeaks
{
    contextualdata_t maxt_data,
                     mint_data;
} temppeaks_t;
*/
typedef struct __temppeaks
{
    contextualdata_t maxt_data,
                     mint_data;
} temppeaks_t;


/*
temppeaks_t
{
    double max_t, min_t;
} temppeaks_t;
*/
typedef struct __mediumtemppeaks
{
    double maxt, mint;
} mediumtemppeaks_t;


/*
 * Esta función lee un archivo CSV con datos meteorológicos de una estación,
 * genera una estructura WeatherStation y devuelve un puntero a la misma.
 * Invoca otras funciones para obtener el vector de estructuras WeatherData y
 * la estructura Station correspondientes al archivo CSV.
 *
 * PRE: El parámetro 'file' debe ser un puntero válido a un archivo CSV abierto para lectura.
 * POS: Devuelve un puntero a una estructura WeatherStation que contiene la información meteorológica
 *      y de la estación del archivo CSV.
 */
extern weatherstation_t* get_weatherstation_fromfile(FILE* file);


/*
 * Esta función, a partir de una lista de nombres de archivos, crea un vector
 * de estructuras WeatherStation para almacenar los datos de la red de estaciones en la zona de interés.
 * Utiliza la función anterior para cargar los datos de cada una de las estaciones de la red.
 *
 * PRE: El parámetro 'filename' debe ser un array de cadenas de caracteres que representan los nombres de archivos válidos.
 *      El parámetro 'length' indica la longitud del array.
 * POS: Devuelve un puntero a un array de estructuras WeatherStation que almacena los datos de la red de estaciones.
 */
extern weatherstation_t* get_weatherstation_fromfilenames(char *filename[FILENAME_L], size_t length);


/*
 * Esta función, dados dos fechas y los datos de una red de estaciones meteorológicas,
 * devuelve los valores de temperatura máxima y mínima registrados en ese período
 * y la estación donde se registraron. Utiliza estructuras temppeaks_t para almacenar los resultados.
 *
 * PRE: Los parámetros 'weatherstation_arr' y 'length' deben representar un array válido de estructuras WeatherStation y su longitud, respectivamente.
 *      'data1' y 'data2' son las fechas de inicio y fin del período de interés.
 * POS: Devuelve una estructura temppeaks_t con la información de temperatura máxima y mínima junto con las estaciones correspondientes.
 */
extern temppeaks_t get_temperature_peaks(weatherstation_t* weatherstation_arr, size_t length, data_t data1, data_t data2);


/*
 * Esta función, dada una fecha y los datos de una red de estaciones meteorológicas,
 * devuelve los valores medios de temperaturas máximas y mínimas en esa área geográfica.
 *
 * PRE: Los parámetros 'weatherstation_arr' y 'length' deben representar un array válido de estructuras WeatherStation y su longitud, respectivamente.
 *      'data' es la fecha de interés.
 * POS: Devuelve una estructura mediumtemppeaks_t con los valores medios de temperaturas máximas y mínimas.
 */
extern mediumtemppeaks_t get_temperature_mediumpeaks(weatherstation_t* weatherstation_arr, size_t length, data_t data);


/*
 * Esta función compara dos estructuras de fecha data_t y devuelve 1 si la primera fecha
 * es mayor o igual que la segunda, y 0 en caso contrario.
 *
 * PRE: Los parámetros 'd1' y 'd2' deben ser estructuras data_t válidas.
 * POS: Devuelve 1 si 'd1 >= d2', 0 en caso contrario.
 */
extern int data_compare(data_t d1, data_t d2);


/*
 * Esta función calcula la distancia entre dos fechas y devuelve un valor entero.
 *
 * PRE: Los parámetros 'd1' y 'd2' deben ser estructuras data_t válidas.
 * POS: Devuelve un valor entero que representa la distancia entre las fechas.
 */
extern int calcular_distancia(data_t d1, data_t d2);

/**
 * Funcion para liberar memoria
*/
extern void free_weatherdata(weatherdata_t* weatherdata);
/**
 * Funcion para liberar memoria
*/
extern void free_weatherstation(weatherstation_t* weatherstation);
/**
 * Funcion para liberar memoria
*/
extern void free_weatherstation_arr(weatherstation_t* weatherstation_arr, size_t length);


#endif //meteo.h


