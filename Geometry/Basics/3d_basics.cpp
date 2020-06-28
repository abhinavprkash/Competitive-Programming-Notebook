struct point3d
{
    ld x, y, z;
    point3d() {}
    point3d(ld x, ld y, ld z): x(x), y(y), z(z) {}
    point3d &operator+=(const point3d &t)
    {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d &operator-=(const point3d &t)
    {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d &operator*=(ld t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d &operator/=(ld t
                        ld dot(point3d a, point3d b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    })
    {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const
    {
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const
    {
        return point3d(*this) -= t;
    }
    point3d operator*(ld t) const
    {
        return point3d(*this) *= t;
    }
    point3d operator/(ld t) const
    {
        return point3d(*this) /= t;
    }
};
point3d operator*(ld a, point3d b)
{
    return b * a;
}
ld dot(point3d a, point3d b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

point3d cross(point3d a, point3d b)
{
    return point3d(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}
ld triple(point3d a, point3d b, point3d c)
{
    return dot(a, cross(b, c));
}
// Used Cramer's Rule, triple product is just the determinant of the coordinates.
// Accepts form r*ni=d*ni for i=1,2,3
point3d intersect(point3d a1, point3d n1, point3d a2, point3d n2, point3d a3, point3d n3)
{
    point3d x(n1.x, n2.x, n3.x);
    point3d y(n1.y, n2.y, n3.y);
    point3d z(n1.z, n2.z, n3.z);
    point3d d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point3d(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}
