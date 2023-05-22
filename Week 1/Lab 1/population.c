// Say we have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away.

// For example, if we were to start with n = 1200 llamas, then in the first year, 1200 / 3 = 400 new llamas would be born and 1200 / 4 = 300 llamas would pass away. At the end of that year, we would have 1200 + 400 - 300 = 1300 llamas.

// To try another example, if we were to start with n = 1000 llamas, at the end of the year, we would have 1000 / 3 = 333.33 new llamas. We can’t have a decimal portion of a llama, though, so we’ll truncate the decimal to get 333 new llamas born. 1000 / 4 = 250 llamas will pass away, so we’ll end up with a total of 1000 + 333 - 250 = 1083 llamas at the end of the year.

#include <cs50.h>
#include <stdio.h>

int start(void);
int end_population(int start);
int calculate_years(int start, int end);

int main(void)
{
    // TODO: Prompt for start size
    int start_size = start();

    // TODO: Prompt for end size
    int end = end_population(start_size);

    // TODO: Calculate number of years until we reach threshold
    int years =  calculate_years(start_size, end);

    // TODO: Print number of years
    printf("Years: %i", years);
}

int start(void)
{
    int s ;
    do
    {
        s = get_int("Start size: ");
    }
    while(s < 9);
    return s;
}

int end_population(int start)
{
    int end ;
    do
    {
        end = get_int("End size: ");
    }
    while(end < start);

    return end;
}

int calculate_years(int start, int end)
{
    int year = 0;
    while(start < end)
    {
        start = start + (start/3) - (start/4);
        year++;
    }
    return year;
}