#include "meteo.h"


int is_leapYear(int aa)
{
    return (aa % 400 == 0) || ((aa % 100 != 0) && (aa % 4 == 0));
}


int get_year_day(data_t _Data)
{
    int days = 0; 

    int this_month_len[] = month_len;
    if (is_leapYear(_Data.yy))
        this_month_len[1]++;

    for (int i = _Data.mm - 1; i != 0; i--)
    {
        days += this_month_len[i - 1];
    }

    days += _Data.dd;

    return days;
}


int leap_years(int year)
{
    return year/4 - year/100 + year/400;
}


int calcular_distancia(data_t d1, data_t d2)
{
    int days1 = (d1.yy-1) * 365 + get_year_day(d1) + leap_years(d1.yy-1);
    int days2 = (d2.yy-1) * 365 + get_year_day(d2) + leap_years(d2.yy-1);
    return (days1 > days2) ? days1 - days2 : days2 - days1;
}


int data_compare(data_t d1, data_t d2)
{
    if (d1.yy != d2.yy)
    {
        return d1.yy > d2.yy;
    }
    else if (d1.mm != d2.mm)
    {
        return d1.mm > d2.mm;
    }
    else
    {
        return d1.dd > d2.dd;
    }
}