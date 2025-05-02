/*#include "../include/curvy_world.h"

curvy_world::curvy_world()
{
    // Initialize control points to zero
    controlPoint1 = Point(0, 0);
    controlPoint2 = Point(0, 0);
    controlPoint3 = Point(0, 0);
    controlPoint4 = Point(0, 0);
}

curvy_world::~curvy_world()
{
    //dtor
}

void curvy_world::generateRoad(float startX, float startY, float width, float height)
{
    //For simplicity, make a smooth curve starting at (startX, startY)
    controlPoint1 = Point(startX, startY);
    controlPoint2 = Point(startX + width * 0.25f, startY + height * 0.3f);
    controlPoint3 = Point(startX + width * 0.75f, startY + height * 0.7f);
    controlPoint4 = Point(startX + width, startY + height);
}

Point curvy_world::bezierPoint(float t)
{
    //Cubic Bezier formula
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Point p = controlPoint1 * uuu; // first term
    p = p + controlPoint2 * 3 * uu * t; // second term
    p = p + controlPoint3 * 3 * u * tt; // third term
    p = p + controlPoint4 * ttt;        // fourth term

    return p;
}

std::vector<Point> curvy_world::sampleBezierCurve(int sampleCount)
{
    std::vector<Point> points;
    points.reserve(sampleCount);

    for (int i = 0; i < sampleCount; ++i)
    {
        float t = static_cast<float>(i) / (sampleCount - 1); // from 0 to 1
        points.push_back(bezierPoint(t));
    }

    return points;
}

std::vector<Point> generateRoadEdges(const std::vector<Point>& curvePoints, float roadWidth)
{
    std::vector<Point> leftEdge, rightEdge;
    float halfWidth = roadWidth / 2;

    for (size_t i = 0; i < curvePoints.size(); ++i) {
        Point p = curvePoints[i];

        // Compute tangent vector
        Point tangent;
        if (i == 0) {
            tangent = curvePoints[i+1] - p;
        } else if (i == curvePoints.size() - 1) {
            tangent = p - curvePoints[i-1];
        } else {
            tangent = curvePoints[i+1] - curvePoints[i-1];
        }
        tangent = tangent.normalized();

        // Normal vector (perpendicular)
        Point normal = tangent.perpendicular().normalized();

        // Offset points
        Point leftPoint = p + normal * halfWidth;
        Point rightPoint = p - normal * halfWidth;

        leftEdge.push_back(leftPoint);
        rightEdge.push_back(rightPoint);
    }

    // Combine left and right edges into a polygon
    std::vector<Point> polygonPoints;
    // Add left edge points
    for (const auto& p : leftEdge) {
        polygonPoints.push_back(p);
    }
    // Add right edge points in reverse to form a closed polygon
    for (auto it = rightEdge.rbegin(); it != rightEdge.rend(); ++it) {
        polygonPoints.push_back(*it);
    }

    return polygonPoints;
}

void curvy_world::drawRoad(sf::RenderWindow& window, const sf::Texture& texture)
{
    auto curvePoints = sampleBezierCurve(100);
    auto polygon = generateRoadEdges(curvePoints, 200.f);

    sf::VertexArray vertices(sf::TriangleFan, polygon.size());

    // Assign texture coordinates (simple mapping)
    for (size_t i = 0; i < polygon.size(); ++i)
    {
        vertices[i].position = sf::Vector2f(polygon[i].x, polygon[i].y);
        // Map texture coordinates proportionally along the length
        float texX = (float)i / polygon.size(); // normalized
        vertices[i].texCoords = sf::Vector2f(texX * texture.getSize().x, 0);
    }

    sf::RenderStates states;
    states.texture = &texture;

    window.draw(vertices, states);
}
*/
