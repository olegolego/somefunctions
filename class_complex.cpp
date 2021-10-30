#include <cmath>
#include <fstream>
#include <iostream>

template <typename T>
class complex
{
 private:
    T m_re, m_im;

 public:
    complex()
    {
        m_re = 0;
        m_im = 0;
    }

    complex(T x)
    {
        m_re = x;
        m_im = 0;
    }

    complex(T x, T y)
    {
        m_re = x;
        m_im = y;
    }

    T re()
    {
        return m_re;
    }

    T im()
    {
        return m_im;
    }

    T abs()
    {
        return std::sqrt(m_re * m_re + m_im * m_im);
    }

    T arg()
    {
        return atan2(m_im, m_re);
    }

    complex<T> conj() const
    {
        return complex(m_re, -m_im);
    }

    static complex<T> polar(T r, T angle);
    static complex<T> sqrt(complex<T> a);
    static void solve_quadratic_equation(complex<T> a, complex<T> b, complex<T> c, complex<T> &z1, complex<T> &z2);
    static complex<T> pow(complex<T> z, int n);
    static complex<T> pow(complex<T> z, T x);
    static complex<T> exp(complex<T> z);
    static complex<T> sin(complex<T> z);
    static complex<T> cos(complex<T> z);
    static complex<T> log(complex<T> z);
    static complex<T> pow(complex<T> z, complex<T> w);
    static void complex<T>::solve_cubic_equation(complex<T> a, complex<T> b, complex<T> c, complex<T> d, complex<T> & z1, complex<T> & z2, complex<T> & z3); 
};

complex<double> operator"" _i(long double a)
{
    return complex<double>(0, a);
}

complex<double> operator"" _i(unsigned long long a)
{
    return complex<double>(0, a);
}

complex<float> operator"" _if(long double a)
{
    return complex<float>(0, a);
}

complex<float> operator"" _if(unsigned long long a)
{
    return complex<float>(0, a);
}

complex<long double> operator"" _il(long double a)
{
    return complex<long double>(0, a);
}

complex<long double> operator"" _il(unsigned long long a)
{
    return complex<long double>(0, a);
}

// ==
template <typename T>
bool operator==(complex<T> a, complex<T> b)
{
    return (a.re() == b.re() && a.im() == b.im());
}

template <typename T>
bool operator==(T a, complex<T> b)
{
    return (a == b.re() && b.im() == T(0));
}

template <typename T>
bool operator==(complex<T> b, T a)
{
    return (a == b.re() && b.im() == T(0));
}

// !=
template <typename T>
bool operator!=(complex<T> a, complex<T> b)
{
    return (a.re() != b.re() || a.im() != b.im());
}

template <typename T>
bool operator!=(T a, complex<T> b)
{
    return (a != b.re() || b.im() != T(0));
}

template <typename T>
bool operator!=(complex<T> b, T a)
{
    return (a != b.re() || b.im() != T(0));
}

// <

template <typename T>
bool operator<(complex<T> a, complex<T> b)
{
    if (a.abs() > b.abs())
    {
        return false;
    }

    else if (a.abs() < b.abs())
    {
        return true;
    }

    else
    {
        T arg1 = a.arg();
        T arg2 = b.arg();
        if (arg1 < T(0))
            arg1 += T(2) * M_PI;
        if (arg2 < T(0))
            arg2 += T(2) * M_PI;
        return arg1 < arg2;
    }
}

// +
template <typename T>
complex<T> operator+(complex<T> a, complex<T> b)
{
    return complex<T>(a.re() + b.re(), a.im() + b.im());
}

template <typename T>
complex<T> operator+(complex<T> a, T b)
{
    return complex<T>(a.re() + b, a.im());
}

template <typename T>
complex<T> operator+(T b, complex<T> a)
{
    return complex<T>(a.re() + b, a.im());
}

// -
template <typename T>
complex<T> operator-(complex<T> a, complex<T> b)
{
    return complex<T>(a.re() - b.re(), a.im() - b.im());
}

template <typename T>
complex<T> operator-(complex<T> a, T b)
{
    return complex<T>(a.re() - b, a.im());
}

template <typename T>
complex<T> operator-(T b, complex<T> a)
{
    return complex<T>(b - a.re(), -a.im());
}

// *
template <typename T>
complex<T> operator*(complex<T> a, complex<T> b)
{
    return complex<T>(a.re() * b.re() - b.im() * a.im(), a.im() * b.re() + a.re() * b.im());
}

template <typename T>
complex<T> operator*(complex<T> a, T b)
{
    return complex<T>(a.re() * b, a.im() * b);
}

template <typename T>
complex<T> operator*(T b, complex<T> a)
{
    return complex<T>(b * a.re(), b * a.im());
}

// /
template <typename T>
complex<T> operator/(complex<T> a, complex<T> b)
{
    complex<T> sop = a * b.conj();
    T z = (b.re() * b.re() + b.im() * b.im());
    return complex<T>((sop.re() / z), sop.im() / z);
}

template <typename T>
complex<T> operator/(complex<T> a, T b)
{
    return complex<T>(a.re() / b, a.im() / b);
}

template <typename T>
complex<T> operator/(T b, complex<T> a)
{
    complex<T> sop = b * a.conj();
    T z = (a.re() * a.re() + a.im() * a.im());
    return complex<T>(sop.re() / z, sop.im() / z);
}

template <typename T>
static complex<T> operator-(complex<T> a)
{
    return complex<T>(-a.re(), -a.im());
}

template <typename T>
static complex<T> operator+(complex<T> a)
{
    return complex<T>(a.re(), a.im());
}

template <typename T>
complex<T> complex<T>::polar(T r, T angle)
{
    return complex<T>(r * std::cos(angle), r * std::sin(angle));
}

template <typename T>
complex<T> complex<T>::sqrt(complex<T> a)
{
    return complex<T>::polar(std::sqrt(a.abs()), a.arg() / 2);
}

template <typename T>
void complex<T>::solve_quadratic_equation(complex<T> a, complex<T> b, complex<T> c, complex<T> &z1, complex<T> &z2)
{
    complex<T> discriminant = b * b - T(4) * a * c;
    complex<T> quad = complex<T>::sqrt(discriminant);
    z1 = (-b + quad) / (T(2) * a);
    z2 = (-b - quad) / (T(2) * a);
}

template <typename T>
complex<T> complex<T>::pow(complex<T> z, int n)
{
    int b = n;
    n = std::abs(n);
    complex<T> res = complex<T>(1, 0);
    while (n)
    {
        if (n & 1)
        {
            res = res * z;
            --n;
        }

        else
        {
            z = z * z;
            n >>= 1;
        }
    }

    return (b > 0 ? res : T(1) / res);
}

template <typename T>
complex<T> complex<T>::pow(complex<T> z, T x)
{
    T new_abs = std::pow(z.abs(), x);
    T new_arg = x * z.arg();
    return complex<T>::polar(new_abs, new_arg);
}

template <typename T>
complex<T> complex<T>::exp(complex<T> z)
{
    T modul = std::pow(std::exp(T(1)), z.re());
    return complex<T>::polar(modul, z.im());
}

template <typename T>
complex<T> complex<T>::sin(complex<T> z)
{
    // sin(x + iy)
    T sh = (std::pow(std::exp(T(1)), z.im()) - std::pow(std::exp(T(1)), -(z.im()))) / 2;
    T ch = (std::pow(std::exp(T(1)), z.im()) + std::pow(std::exp(T(1)), -(z.im()))) / 2;
    return complex<T>(std::sin(z.re()) * ch, std::cos(z.re()) * sh);
}

template <typename T>
complex<T> complex<T>::cos(complex<T> z)
{
    // cos(x + iy)
    T sh = (std::pow(std::exp(T(1)), z.im()) - std::pow(std::exp(T(1)), -(z.im()))) / 2;
    T ch = (std::pow(std::exp(T(1)), z.im()) + std::pow(std::exp(T(1)), -(z.im()))) / 2;
    return complex<T>(std::cos(z.re()) * ch, -std::sin(z.re()) * sh);
}

template <typename T>
complex<T> complex<T>::log(complex<T> z)
{
    return complex<T>(std::log(z.abs()), z.arg());
}

template <typename T>
complex<T> complex<T>::pow(complex<T> z, complex<T> w)
{
    return complex<T>::exp(w * complex<T>::log(z));
}

template <typename T>
void complex<T>::solve_cubic_equation(complex<T> a, complex<T> b, complex<T> c, complex<T> d, complex<T> & z1, complex<T> & z2, complex<T> & z3){
    T p = (T(3) * a * c - b * b) / (T(3) * a * a);
    T q = (T(2) * b * b * b - T(9) * a * b * c + T(27) * a * a * d) / T(27) * a * a * a;
    T Q = p  * p * p / T(27) + q * q / T(4);
    T alpha = std::cbrt(-q / T(2) + std::sqrt(Q));
    T beta = std::cbrt(-q / T(2) - std::sqrt(Q));
    z1 = alpha + beta - (b / T(3) * a);
} 

template <typename T>
std::ostream &operator<<(std::ostream &out, complex<T> comp)
{
    if (comp.re() == T(0) && comp.im() == T(0))
    {
        out << "0";
    }

    else if (comp.im() == T(0))
    {
        out << comp.re();
    }

    else if (comp.re() == T(0))
    {
        if (comp.im() == T(1))
        {
            out << "i";
        }

        else if (comp.im() == T(-1))
        {
            out << "-i";
        }

        else
        {
            out << comp.im() << "i";
        }
    }

    else
    {
        out << '(' << comp.re();
        if (comp.im() > T(0))
            out << "+";
        if (comp.im() == T(1))
        {
            out << "i";
        }

        else if (comp.im() == T(-1))
        {
            out << "-i";
        }

        else
        {
            out << comp.im() << "i";
        }
        out << ')';
    }
    return out;
}

using namespace std;
int main(){
    
}