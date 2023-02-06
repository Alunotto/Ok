#include <iostream>
#include <math.h>

double gr = 0.618;
long double acc = 0.000001;

using namespace std;

long double function1(long double x, long double y)
{
    return pow(sin(x - 0.5), 2) + pow(atan(y - 0.4), 2);
}
long double function(long double x, long double y)
{
    return (pow(sin(x - 0.5), 2) + pow(atan(y - 0.4), 2));
}
long double gradient_x(long double x)
{
    return 2 * cos(x - 0.5) * sin(x - 0.5);
}
long double gradient_y(long double y)
{
    return (2 * atan(y - 0.4)) / (pow(y - 0.4, 2) + 1);
}

double golden_section_method(long double a, long double b, long double mult1, long double dod1, long double mult2, long double dod2, int n)
{
    long double x1 = 0, x2 = 0;
    for (int i = 0; i < n; i++)
    {
        x1 = a + gr * (b - a);
        x2 = b - gr * (b - a);
        //if (function1(x1*mult1 + dod1,x2*mult2 + dod2) <= function1(x1*mult1 + dod1,x2*mult2 + dod2))
        if (function1(x1 * mult1 + dod1, x1 * mult2 + dod2) <= function1(x2 * mult1 + dod1, x2 * mult2 + dod2))
        {
            a = x2;
            x2 = x1;
            x1 = a + gr * (b - a);
            i = i;
        }
        else
        {
            b = x1;
            x1 = x2;
            x2 = b - gr * (b - a);
            i = i;
        }

    }

    return (x1 + x2) / 2;
}

void some_st_method_for_intervals(long double interval_bx[2], long double interval_by[2], long double* interval_b1)
{
    if (interval_bx[0] > interval_bx[1])
    {
        long double help = interval_bx[1];
        interval_bx[1] = interval_bx[0];
        interval_bx[0] = help;
    }
    if (interval_by[0] > interval_by[1])
    {
        long double help = interval_by[1];
        interval_by[1] = interval_by[0];
        interval_by[0] = help;
    }
    if (interval_bx[0] > interval_by[0])
        interval_b1[0] = interval_bx[0];
    else
        interval_b1[0] = interval_by[0];

    if (interval_bx[1] < interval_by[1])
        interval_b1[1] = interval_bx[1];
    else
        interval_b1[1] = interval_by[1];
}
void conjugate_gradient_method(long double px, long double py, long double lx1, long double lx2, long double ly1, long double ly2)
{
    cout << "for starting points: " << px << "  ,  " << py << endl;
    long double p2[2] = { 0,0 };
    long double b1;
    int i = 0;
    long double h = 0;
    long double k;
    long double d2[2];
    long double d[2] = { -gradient_x(px), -gradient_y(py) };
    long double interval_bx[2] = { ((lx1 + px) / d[0]),((lx2 + px) / d[0]) };
    long double interval_by[2] = { ((ly1 + py) / d[1]),((ly2 + py) / d[1]) };
    long double interval_b1[2];
    some_st_method_for_intervals(interval_bx, interval_by, interval_b1);
    interval_b1[0];
    interval_b1[1];
    k = golden_section_method(-1, 1, d[0], px, d[1], py, 39);
    //k = golden_section_method(-1, 1, d[0], 0, d[1], 0, 7);
    p2[0] = (px + d[0] * k);
    p2[1] = (py + d[1] * k);
    while (sqrt(pow(p2[0] - px, 2)) >= acc || sqrt(pow(p2[1] - py,2)) >= acc)
    {
        cout << "current point:" << p2[0] << "   ,   " << p2[1] << endl;
        h = gradient_x(p2[0]);
        h = gradient_y(p2[1]);
        h = gradient_x(px);
        h = gradient_y(py);
        b1 = (gradient_x(p2[0]) * (gradient_x(p2[0]) - gradient_x(px)) + gradient_y(p2[1]) * (gradient_y(p2[1]) - gradient_y(py)));
        h = (pow(gradient_x(px), 2) + pow(gradient_y(py), 2));
        b1 =b1 / (pow(gradient_x(px), 2) + pow(gradient_y(py), 2));
       
        d2[0] = -1 * gradient_x(p2[0]) + b1 * d[0];
        d2[1] = -1 * gradient_y(p2[1]) + b1 * d[1];
        interval_bx[0] = ((lx1 + p2[0]) / d2[0]);
        interval_bx[1] = ((lx2 + p2[0]) / d2[0]);
        interval_by[0] = ((ly1 + p2[1]) / d2[1]);
        interval_by[1] = ((ly2 + p2[1]) / d2[1]);
        some_st_method_for_intervals(interval_bx, interval_by, interval_b1);
        interval_b1[0];
        interval_b1[1];
        //k = golden_section_method(-1, 1, d2[0], 0, d2[1], 0, 7);
        k = golden_section_method(-1, 1, d2[0], p2[0], d2[1], p2[1], 39);
        px = p2[0];
        py = p2[1];
        p2[0] = (px + d2[0] * k);
        p2[1] = (py + d2[1] * k);
        d[0] = d2[0];
        d[1] = d2[1];
        i++;
        if (p2[0] < lx1)
            p2[0] = lx1;
        if (p2[0] > lx2)
            p2[0] = lx2;
        if (p2[1] < lx1)
            p2[1] = lx1;
        if (p2[1] > lx2)
            p2[1] = lx2;
    }
    cout << "min found at: " << p2[0] << "   ,   " << p2[1] << endl<<endl<<endl;
}

int main()
{
    conjugate_gradient_method(0, 0, -1, 1, -1, 1);
    conjugate_gradient_method(-1, -1, -1, 1, -1, 1);
    conjugate_gradient_method(1, 1, -1, 1, -1, 1);
    conjugate_gradient_method(0, 1, -1, 1, -1, 1);
    conjugate_gradient_method(1, 0, -1, 1, -1, 1);
    conjugate_gradient_method(-0.5, -0.5, -1, 1, -1, 1);
    conjugate_gradient_method(-1, 1, -1, 1, -1, 1);
    conjugate_gradient_method(1, -0.5, -1, 1, -1, 1);

}