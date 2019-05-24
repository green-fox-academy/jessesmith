#include <stdio.h>
#include <stdlib.h>
#include "pi.h"

// define a variable called PI with the value of 3.14
// create a function which takes the radius of a circle as a parameter
// and return the area of that cirle
// area = radius * radius * PI


int main()
{
    float radius;
    scanf("%f", &radius);

    printf("Area: %f\n", get_area_from_radius(radius));
    printf("Radius %f", get_circumference_from_radius(radius));
    return 0;
}

float get_area_from_radius(float rad)
{
    return rad * rad * PI;
}

float get_circumference_from_radius(float rad){
    return 2 * PI * rad;
}