#include "../src/meteo.h"
#include <stdio.h>

/*
Crear unha función capaz de ler un arquivo .csv cos datos meteorolóxicos recollidos nunha determinada estación, xerar unha estructura tipo WeatherStation, e devolver o punteiro correspondente. Esta función debe invocar outras fucións (pasándolle  o nome ou o punteiro  a un arquivo .csv) para obter o vector de estruturas tipo WeatherData, e unha estructura Station cos datos identificativos da estación. Para iso odedes usar fucións implementadas previamente, ou modificacións delas.


Comprobe que la primera fecha, la ultima y fechas arbitrarias por el medio estuviesen en la posicion que les corresponde, ademas comprobe que los datos meteorologicos de la primera y la ultima se correspondiesen. Tambien comprobe que el array mide exactamente lo que se necesita.

SALIDA:

Station: "STAT420-75", day:  1 -  1 - 2000, maxt: 8.8000, solar 9.2693
Station: "STAT420-75", day: 31 - 12 - 2000, maxt: 9.6970, solar 0.4833
Station: "STAT420-75", day: 31 - 12 - 2001, maxt: 8.5800, solar 0.8660
Station: "STAT420-75", day: 31 - 12 - 2002, maxt: 8.1390, solar 0.6947
Station: "STAT420-75", day:  1 -  1 - 2004, maxt: 9.9340, solar 0.7201
Station: "STAT420-75", day: 31 - 12 - 2004, maxt: 9.6530, solar 4.3468
Station: "STAT420-75", day: 31 - 12 - 2005, maxt: 7.7070, solar 0.8584
Station: "STAT420-75", day: 31 - 12 - 2006, maxt: 9.0370, solar 1.1753
Station: "STAT420-75", day:  1 -  1 - 2008, maxt: 8.0870, solar 7.8975
Station: "STAT420-75", day: 31 - 12 - 2008, maxt: 7.8890, solar 1.6696
Station: "STAT420-75", day: 31 - 12 - 2009, maxt: 5.8580, solar 1.0559
Station: "STAT420-75", day: 31 - 12 - 2010, maxt: 8.8130, solar 4.9508
Station: "STAT420-75", day:  0 -  0 -    0, maxt: 0.0000, solar 0.0000
*/
void test1()
{
    FILE* f = fopen("../data/weatherdata-420-75.csv", "rt");
    weatherstation_t* wstest = get_weatherstation_fromfile(f);


    printf("Station: \"%s\", day: %2d - %2d - %4d, maxt: %4.4f, solar %4.4f\n",
            wstest->station.name, 
            wstest->weatherdata_arr[0].data.dd, 
            wstest->weatherdata_arr[0].data.mm, 
            wstest->weatherdata_arr[0].data.yy,
            wstest->weatherdata_arr[0].maxt,
            wstest->weatherdata_arr[0].solar);

    fclose(f);


    for(float i = 365.25; i < wstest->data_len; i+=365.25)
    {
        printf("Station: \"%s\", day: %2d - %2d - %4d, maxt: %4.4f, solar %4.4f\n", 
            wstest->station.name, 
            wstest->weatherdata_arr[(int)i].data.dd, 
            wstest->weatherdata_arr[(int)i].data.mm, 
            wstest->weatherdata_arr[(int)i].data.yy,
            wstest->weatherdata_arr[(int)i].maxt,
            wstest->weatherdata_arr[(int)i].solar);
    }


    printf("Station: \"%s\", day: %2d - %2d - %4d, maxt: %4.4f, solar %4.4f\n",
            wstest->station.name, 
            wstest->weatherdata_arr[wstest->data_len].data.dd, 
            wstest->weatherdata_arr[wstest->data_len].data.mm, 
            wstest->weatherdata_arr[wstest->data_len].data.yy,
            wstest->weatherdata_arr[wstest->data_len].maxt,
            wstest->weatherdata_arr[wstest->data_len].solar);

    free_weatherstation(wstest);
}


/*
Crear unha función que a partires dunha lista de nomes de arquivos cree un vector de estruturas tipo WeatherStation, para almacenar os datos da rede de estacións na zona de interese. Esta función debe facer uso da anterior para cargar os datos de cada unha das estacións da rede.

Asumiendo que la funcion anterior funciona, compruebo que las estaciones se guarden correctamente donde corresponde, ya que el array de tipo weatherdata se obtiene con la funcion anterior por lo que no necesita volver a comprobarse

SALIDA: 

Station: "STAT420-72", ubi: 41.9948, -7.1875,  715
Station: "STAT420-75", ubi: 41.9948, -7.5000,  643
Station: "STAT420-78", ubi: 41.9948, -7.8125,  936
Station: "STAT420-81", ubi: 41.9948, -8.1250, 1105
Station: "STAT420-84", ubi: 41.9948, -8.4375,  531
*/
void test2()
{
    int files_l = 5;
    char* filenames[FILENAME_L] = {
        "../data/weatherdata-420-72.csv",
        "../data/weatherdata-420-75.csv",
        "../data/weatherdata-420-78.csv",
        "../data/weatherdata-420-81.csv",
        "../data/weatherdata-420-84.csv"
    };

    weatherstation_t* datatest = get_weatherstation_fromfilenames(filenames, files_l);

    for(int i = 0; i < files_l; i++)
    {
        printf("Station: \"%s\", ubi: %.4f, %.4f, %4d\n",
            datatest[i].station.name,
            datatest[i].station.longitude,
            datatest[i].station.latitude,
            datatest[i].station.elevation
        );
    }
    free_weatherstation_arr(datatest, files_l);

}


/*
Crear unha función que dadas dúas datas e os datos tomados nunha rede de estacións meteorolóxica, nos devolva os valores de temperatura máxima e mínima rexistrados nese período e a estación onde ser rexistrou cada un deles. Pensade no xeito máis axeitado para devolver todos eses datos.

Comprobaciones: ninguna, la logica especifica de esta funcion es simple, y se asume que las funciones anteriores utilizadas para esta funcion funcionan correctamente.

SALIDA 

Maxt:38.1 C on 5-8-2005 at STAT420-81
Mint:-10.1 C on 2-3-2005 at STAT420-75
*/
void test3()
{
    int files_l = 5;
    char* filenames[FILENAME_L] = {
        "../data/weatherdata-420-72.csv",
        "../data/weatherdata-420-75.csv",
        "../data/weatherdata-420-78.csv",
        "../data/weatherdata-420-81.csv",
        "../data/weatherdata-420-84.csv"
    };
    data_t d1 = {1,1,2004}, 
           d2 = {1,1,2005};

    weatherstation_t* datatest = get_weatherstation_fromfilenames(filenames, files_l);
    temppeaks_t temppeaks = get_temperature_peaks(datatest, files_l, d1, d2);

    printf("Maxt:%.1f C on %d-%d-%d at %s\n",
        temppeaks.maxt_data.value,
        temppeaks.maxt_data.data.dd,
        temppeaks.maxt_data.data.mm,
        temppeaks.maxt_data.data.yy,
        temppeaks.maxt_data.station.name
    );

    printf("Mint:%.1f C on %d-%d-%d at %s\n",
        temppeaks.mint_data.value,
        temppeaks.mint_data.data.dd,
        temppeaks.mint_data.data.mm,
        temppeaks.mint_data.data.yy,
        temppeaks.mint_data.station.name
    );
    free_weatherstation_arr(datatest, files_l);
}


/*
Crear unha función que dada unha data e os datos tomados nunha rede de estacións meteorolóxica, nos evolva os valores medios de temperaturas máximas e mínimas nesa área xeográfica.

No hice ninguna comprobacion especifica, mire que los valores de salida se pudiesen corresponder con la fecha. 

SALIDA:
On 1-1-2000:
Max temp med 9.1
Min temp med -3.8
On 1-8-2004:
Max temp med 30.2
Min temp med 13.7
On 1-4-2006:
Max temp med 11.9
Min temp med 6.2
On 31-12-2010:
Max temp med 10.4
Min temp med 5.2
*/
void test4()
{
    int files_l = 5;
    char* filenames[FILENAME_L] = {
        "../data/weatherdata-420-72.csv",
        "../data/weatherdata-420-75.csv",
        "../data/weatherdata-420-78.csv",
        "../data/weatherdata-420-81.csv",
        "../data/weatherdata-420-84.csv"
    };

    weatherstation_t* datatest = get_weatherstation_fromfilenames(filenames, files_l);
    mediumtemppeaks_t medtemp;
    data_t d1;

    d1 = (data_t){1,1,2000};
    printf("On %d-%d-%d:\n", d1.dd, d1.mm, d1.yy);
    medtemp = get_temperature_mediumpeaks(datatest, files_l, d1);
    printf("Max temp med %.1f\n", medtemp.maxt);
    printf("Min temp med %.1f\n", medtemp.mint);

    d1 = (data_t){1,8,2004};
    printf("On %d-%d-%d:\n", d1.dd, d1.mm, d1.yy);
    medtemp = get_temperature_mediumpeaks(datatest, files_l, d1);
    printf("Max temp med %.1f\n", medtemp.maxt);
    printf("Min temp med %.1f\n", medtemp.mint);

    d1 = (data_t){1,4,2006};
    printf("On %d-%d-%d:\n", d1.dd, d1.mm, d1.yy);
    medtemp = get_temperature_mediumpeaks(datatest, files_l, d1);
    printf("Max temp med %.1f\n", medtemp.maxt);
    printf("Min temp med %.1f\n", medtemp.mint);

    d1 = (data_t){31,12,2010};
    printf("On %d-%d-%d:\n", d1.dd, d1.mm, d1.yy);
    medtemp = get_temperature_mediumpeaks(datatest, files_l, d1);
    printf("Max temp med %.1f\n", medtemp.maxt);
    printf("Min temp med %.1f\n", medtemp.mint);
}


int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}