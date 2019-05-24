#include <stdio.h>
#include <string.h>

// Write a function that takes a car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

enum car_type {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct car {
    enum car_type type;
    double km;
    double gas;
};

int print_car_stats(struct car c);

int main()
{
    struct car c;
    c.type = VOLVO;
    c.gas = 22.2;
    c.km = 10.0;

    print_car_stats(c);
    return 0;
}

int print_car_stats(struct car c)
{
    char stats_string[100];
    sprintf(stats_string, "km: %0.2f", c.km);
    if(c.type != TESLA) {
        char gas_string[50];
        sprintf(gas_string, ", gas: %0.2f", c.gas);
        strcat(stats_string, gas_string);
    }
    printf("%s", stats_string);

    return 0;
}