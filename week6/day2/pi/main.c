#include <stdio.h>
#include <stdlib.h>

// define a variable called PI with the value of 3.14
// create a function which takes the radius of a circle as a parameter
// and return the area of that cirle
// area = radius * radius * PI

#define PI 3.14;

float get_area_from_radius(float rad)
{
    return rad * rad * PI;
}

int main()
{
    float radius;
    scanf("%f", &radius);

    float area;
    area = get_area_from_radius(radius);

    printf("Area: %f", area);
    return 0;
}
