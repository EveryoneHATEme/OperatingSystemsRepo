#include <stdio.h>
#include <math.h>
#include <stdlib.h>


struct Point
{
    double x;
    double y;
};


struct Point* createPoint(double x, double y) {
    struct Point *newPoint = malloc(sizeof(struct Point));
    newPoint->x = x;
    newPoint->y = y;
    return newPoint;
}


double distance(struct Point* first, struct Point* second) {
    return sqrt(pow(first->x - second->x, 2.0) + pow(first->y - second->y, 2.0));
}


double area(struct Point* pointA, struct Point* pointB, struct Point* pointC) {
    double result = 1.0 / 2.0 * (pointA->x * pointB->y - pointB->x * pointA->y + pointB->x * pointC->y - pointC->x * pointB->y + pointC->x * pointA->y - pointA->x * pointC->y);
    if (result < 0.0)
        result *= -1.0;
    
    return result;
}


int main() {
    struct Point* pointA = createPoint(2.5, 6.0);
    struct Point* pointB = createPoint(1.0, 2.2);
    struct Point* pointC = createPoint(10.0, 6.0);

    double distanceAB = distance(pointA, pointB);
    double areaABC = area(pointA, pointB, pointC);

    printf("Distance between A and B is %f, area of triangle ABC is %f\n", distanceAB, areaABC);
}