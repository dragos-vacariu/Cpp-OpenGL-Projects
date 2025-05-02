/*#ifndef CURVY_WORLD_H
#define CURVY_WORLD_H

#include "../include/cross_functions.h"

#include <SFML/Graphics.hpp>
using namespace sf;

struct Point
{
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}

    Point operator+(const Point& other) const
    {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(const Point& other) const
    {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(float scalar) const
    {
        return Point(x * scalar, y * scalar);
    }
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }
    Point normalized() const
    {
        float len = length();
        if (len == 0) return Point(0,0);
        return Point(x / len, y / len);
    }
    Point perpendicular() const
    {
        return Point(-y, x); // perpendicular vector
    }
};

class curvy_world
{
    public:
        // Control points for Bezier curve
        Point controlPoint1;
        Point controlPoint2;
        Point controlPoint3;
        Point controlPoint4;

        // Constructor
        curvy_world();
        virtual ~curvy_world();

        // Generate control points for the road
        void generateRoad(float startX, float startY, float width, float height);

        // Generate points along the Bezier curve
        std::vector<Point> sampleBezierCurve(int sampleCount);

        // Draw the road
        void drawRoad(sf::RenderWindow& window, const sf::Texture& texture)

    private:
        // Helper functions
        Point bezierPoint(float t);
};

#endif // CURVY_WORLD_H
*/
