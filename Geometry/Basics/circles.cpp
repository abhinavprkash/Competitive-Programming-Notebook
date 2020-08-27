struct Point
{
    ld x, y;
    Point(ld px, ld py)
    {
        x = px;
        y = py;
    }
    Point sub(Point p2)
    {
        return Point(x - p2.x, y - p2.y);
    }
    Point add(Point p2)
    {
        return Point(x + p2.x, y + p2.y);
    }
    ld distance(Point p2)
    {
        return sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
    }
    Point normal()
    {
        ld length = sqrt(x * x + y * y);
        return Point(x / length, y / length);
    }
    Point scale(ld s)
    {
        return Point(x * s, y * s);
    }
};
struct circle
{
    ld x, y, r;
    pair<Point, Point> intersections(circle c)
    {
        Point P0(x, y);
        Point P1(c.x, c.y);
        ld d, a, h;
        d = P0.distance(P1);
        a = (r * r - c.r * c.r + d * d) / (2 * d);// Distance from P0 of axis of intersection
        h = sqrt(r * r - a * a);// Height of point above a
        Point P2 = P1.sub(P0).scale(a / d).add(P0);//Line Ratio Theorem
        ld x3, y3, x4, y4;
        x3 = P2.x + h * (P1.y - P0.y) / d;
        y3 = P2.y - h * (P1.x - P0.x) / d;
        x4 = P2.x - h * (P1.y - P0.y) / d;
        y4 = P2.y + h * (P1.x - P0.x) / d;
        return pair<Point, Point>(Point(x3, y3), Point(x4, y4));
    }
};