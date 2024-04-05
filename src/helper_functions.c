#include "maze.h"

/**
 * scaler - Multiplies a value by a scale factor
 *
 * @value: Value to multiply.
 *
 * Return: the product of the value and the map scale factor.
*/
float scaler(float value)
{
	return (value * MAP_SCALE);
}

/**
 * normalize - Normalizes an angle to the range [0, 2*PI]
 *
 * @angle: Angle to normalize.
 *
 * Return: Normalized angle.
*/
float normalize(float angle)
{
    angle = remainder(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;

    return (angle);
}

/**
 * distanceBtwn - Calculates the distance between two points.
 *
 * @x1: The X-coordinate of the 1st point.
 * @y1: The Y-coordinate of the 1st point.
 * @x2: The X-coordinate of the 2nd point.
 * @y2: The Y-coordinate of the 2nd point.
 *
 * Return: The distance between the two points.
*/
float distanceBtwn(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * getGridVal - retrieves the content of the map at a given position.
 *
 * @x: The X-coordinate.
 * @y: The Y-coordinate.
 *
 * Return: the value in the map grid corresponding to the given position.
*/
int getGridVal(float x, float y)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return 0;
	int indexX = floor(x / TILE_SIZE);
	int indexY = floor(y / TILE_SIZE);

	return (map[indexY][indexX]);
}
