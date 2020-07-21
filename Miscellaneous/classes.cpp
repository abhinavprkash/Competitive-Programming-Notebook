#include <bits/stdc++.h>
using namespace std;
template<typename T>
ostream &operator<<(ostream &os, vector<T>v)
{
    os << "[ ";
    for(auto it : v)
        os << it << " ";
    return os << "]";
}
void debug()
{
    cerr << "\n";
}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T)
{
    cerr << H << " ";
    debug(T...);
}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : ";debug(__VA_ARGS__);
void console()
{
    cout << "\n";
}
template<typename Head, typename... Tail>
void console(Head H, Tail... T)
{
    cout << H << " ";
    console(T...);
}
#define console(...) cout<<"["<<#__VA_ARGS__<<"] : ";console(__VA_ARGS__);
class A
{
    int x, y;
public:
    A(): x(0), y(0) {}
    A(int _x, int _y = 0): x(_x), y(_y) {};
    ~A() {}
    A(const A &b)
    {
        this->x = b.x;
        this->y = b.y;
    }
    void setx(const int &v)
    {
        this->x = v;
        this->y = v;
    }
    int getx() const
    {
        return this->x;
    }
    int gety() const
    {
        return this->y;
    }
    void operator = (const A &a) // = overloading
    {
        x = a.x;
        y = a.y;
    };
    A operator +(const A &a) // + overloading
    {
        return {x + a.x, y + a.y};
    }
    int operator () () // () overloading
    {
        return x * x + y * y;
    }
    operator string () // Conversion Operator
    {
        return to_string(x);
    }
    void operator +=(const A &a)
    {
        x += a.x;
        y += a.y;
    }
    // Increment and Decrement Operators
    // 1.   Pre-Increment operator
    int operator ++()
    {
        x += 1;
        return x;
    }
    int operator --()
    {
        x -= 1;
        return x;
    }
    // Dummy value passed to differentiate from pre-increment overloaders
    // 2. Post-increment operator
    int operator ++(int)
    {
        int temp = x;
        x += 1;
        return temp;
    }
    int operator --(int)
    {
        int temp = x;
        x -= 1;
        return temp;
    }
};

class mult_by
{
    int x = 1;
public:
    mult_by(int n): x(n) {}
    int operator() (int a) const
    {
        return x * a;
    }
};
struct mult
{
    int x = 1;
    mult(int c): x(c) {}
    int operator() (int a) const
    {
        return x * a;
    }
};
int main()
{
    A a = 2; // Implicit conversion works with only one parameter
    // ( Declare constructor with explicit keyword to restrict the use)

    // Uses string conversion operator
    string s = "value of a is ";
    s += a;
    console(s);

    A c;
    c = a; // assignment overloading
    console(a.getx(), a.gety());
    console(c.getx(), c.gety());

    // + overloading
    A b = a + a;

    //Pre decrement overloading
    A d = --b;
    console(b.getx(), b.gety());
    console(d.getx(), d.gety());

    //Post decrement overloading
    A e = b--;
    console(b.getx(), b.gety());
    console(e.getx(), e.gety());

    // new and delete (memory management)
    A *o = new A(3, 40);
    console(o->getx(), o->gety());
    delete(o); // Calls destructor first

    // Functors
    const mult_by times_five(5);
    const mult_by times_ten(10);
    const mult_by times_fifteen(15);
    const mult times_hundred(100);
    console(times_five(3), times_ten(3), times_fifteen(3));
    console(times_hundred(3));
}
/*
Output::
[s] : value of a is 2
[a.getx(), a.gety()] : 2 0
[c.getx(), c.gety()] : 2 0
[b.getx(), b.gety()] : 3 0
[d.getx(), d.gety()] : 3 0
[b.getx(), b.gety()] : 2 0
[e.getx(), e.gety()] : 3 0
[o->getx(), o->gety()] : 3 40
[times_five(3), times_ten(3), times_fifteen(3)] : 15 30 45
[times_hundred(3)] : 300
*/
