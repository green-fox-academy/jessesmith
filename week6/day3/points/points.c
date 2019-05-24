#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Create a point struct which has two float variables: x and y
Create a function that constructs a point
It should take it's x and y coordinate as parameter
Create a function that takes 2 points and returns the distance between them
Example:
int main()
{
	point_t p1 = create_point(1, 1);
	point_t p2 = create_point(1, 5.5);
	float dist = distance(p1, p2);
	printf("%f", dist);
	return 0;
}
*/

typedef struct point_s {
    float x, y;
} point;

point build_point(float p_x, float p_y);

float distance_between_points(point point_1, point point_2);

int main()
{
    point p1 = build_point(1, 1);
    point p2 = build_point(2, 4);
    float dist = distance_between_points(p1, p2);
    printf("%f", dist);
    return 0;
}

point build_point(float p_x, float p_y)
{
    point p;
    p.x = p_x;
    p.y = p_y;
    return p;
}

float distance_between_points(point point_1,point point_2)
{
    float x1 = point_1.x;
    float y1 = point_1.y;
    float x2 = point_2.x;
    float y2 = point_2.y;

    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}