#include <iostream>
#include <cmath>
using namespace std;

class VectorFloat {
    float* data;
    int size, codeError;
public:
    VectorFloat() : size(1), codeError(0)
    {
        data = new(nothrow) float[1];
        if (!data) codeError = 1;
        else data[0] = 0;
    }
    VectorFloat(int s) : size(s), codeError(0)
    {
        data = new(nothrow) float[s];
        if (!data) codeError = 1;
        else for (int i = 0; i < s; ++i) data[i] = 0;
    }
    VectorFloat(int s, float val) : size(s), codeError(0)
    {
        data = new(nothrow) float[s];
        if (!data) codeError = 1;
        else for (int i = 0; i < s; ++i) data[i] = val;
    }
    VectorFloat(const VectorFloat& other) : size(other.size), codeError(0)
    {
        data = new(nothrow) float[size];
        if (!data) codeError = 1;
        else for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
    ~VectorFloat()
    {
        delete[] data;
    }
    VectorFloat& operator=(const VectorFloat& other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            data = new(nothrow) float[size];
            if (!data) codeError = 1;
            else for (int i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }
    VectorFloat& operator++()
    {
        for (int i = 0; i < size; ++i) data[i] += 1.0f;
        return *this;
    }
    VectorFloat operator++(int)
    {
        VectorFloat temp(*this);
        ++(*this);
        return temp;
    }
    VectorFloat& operator--()
    {
        for (int i = 0; i < size; ++i) data[i] -= 1.0f;
        return *this;
    }
    VectorFloat operator--(int)
    {
        VectorFloat temp(*this);
        --(*this);
        return temp;
    }
    bool operator!() const
    {
        for (int i = 0; i < size; ++i)
            if (data[i] != 0) return false;
        return true;
    }
    VectorFloat operator-() const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = -data[i];
        return result;
    }
    VectorFloat& operator+=(const VectorFloat& other)
    {
        for (int i = 0; i < size; ++i) data[i] += other.data[i];
        return *this;
    }
    VectorFloat& operator-=(const VectorFloat& other)
    {
        for (int i = 0; i < size; ++i) data[i] -= other.data[i];
        return *this;
    }
    VectorFloat& operator*=(float val)
    {
        for (int i = 0; i < size; ++i) data[i] *= val;
        return *this;
    }
    VectorFloat& operator/=(float val)
    {
        for (int i = 0; i < size; ++i) data[i] = (val != 0 ? data[i] / val : 0);
        return *this;
    }
    VectorFloat& operator%=(int val)
    {
        for (int i = 0; i < size; ++i) data[i] = fmod(data[i], val);
        return *this;
    }
    VectorFloat operator+(const VectorFloat& other) const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = data[i] + other.data[i];
        return result;
    }
    VectorFloat operator-(const VectorFloat& other) const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = data[i] - other.data[i];
        return result;
    }
    VectorFloat operator*(float val) const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = data[i] * val;
        return result;
    }
    VectorFloat operator/(float val) const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = (val != 0 ? data[i] / val : 0);
        return result;
    }
    VectorFloat operator%(int val) const
    {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) result.data[i] = fmod(data[i], val);
        return result;
    }
    friend VectorFloat operator<<(const VectorFloat& vec, int shift);
    friend VectorFloat operator>>(const VectorFloat& vec, int shift);
    friend istream& operator>>(istream& in, VectorFloat& vec);
    friend ostream& operator<<(ostream& out, const VectorFloat& vec);
    bool operator==(const VectorFloat& other) const
    {
        for (int i = 0; i < size; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }
    bool operator!=(const VectorFloat& other) const
    {
        return !(*this == other);
    }
    bool operator>(const VectorFloat& other) const
    {
        for (int i = 0; i < size; ++i)
            if (data[i] <= other.data[i]) return false;
        return true;
    }
    bool operator<(const VectorFloat& other) const
    {
        for (int i = 0; i < size; ++i)
            if (data[i] >= other.data[i]) return false;
        return true;
    }
    bool operator>=(const VectorFloat& other) const
    {
        return !(*this < other);
    }
    bool operator<=(const VectorFloat& other) const
    {
        return !(*this > other);
    }
    float& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            codeError = 5;
            return data[size - 1];
        }
        return data[index];
    }
    void operator()() const
    {
        cout << "Вектор: ";
        for (int i = 0; i < size; ++i) cout << data[i] << " ";
        cout << endl;
    }
    int getCodeError() const
    {
        return codeError;
    }
};
VectorFloat operator<<(const VectorFloat& vec, int shift)
{
    VectorFloat result(vec);
    if (shift <= 0 || shift >= vec.size) return result;
    for (int i = 0; i < vec.size - shift; ++i)
        result.data[i] = vec.data[i + shift];
    for (int i = vec.size - shift; i < vec.size; ++i)
        result.data[i] = 0;
    return result;
}
VectorFloat operator>>(const VectorFloat& vec, int shift)
{
    VectorFloat result(vec);
    if (shift <= 0 || shift >= vec.size) return result;
    for (int i = vec.size - 1; i >= shift; --i)
        result.data[i] = vec.data[i - shift];
    for (int i = 0; i < shift; ++i)
        result.data[i] = 0;
    return result;
}
istream& operator>>(istream& in, VectorFloat& vec)
{
    for (int i = 0; i < vec.size; ++i) {
        cout << "[" << i << "]: ";
        in >> vec.data[i];
    }
    return in;
}
ostream& operator<<(ostream& out, const VectorFloat& vec)
{
    out << "[ ";
    for (int i = 0; i < vec.size; ++i) out << vec.data[i] << " ";
    out << "]";
    return out;
}
int main()
{
    int size;
    cout << "Розмір масиву: ";
    cin >> size;
    VectorFloat a(size), b(size);
    cout << "Елементи масиву A:" << endl;
    cin >> a;
    cout << "Елементи масиву B:" << endl;
    cin >> b;
    cout << "A = " << a << endl;
    cout << "B = " << b << endl;

    ++a; cout << "++A = " << a << endl;
    a++; cout << "A++ = " << a << endl;
    --a; cout << "--A = " << a << endl;
    a--; cout << "A-- = " << a << endl;
    cout << "!A = " << (!a ? "true" : "false") << endl;
    cout << "-A = " << (-a) << endl;
    VectorFloat c = a;
    c = a; c += b; cout << "A += B => " << c << endl;
    c = a; c -= b; cout << "A -= B => " << c << endl;
    c = a; c *= 3; cout << "A *= 3 => " << c << endl;
    c = a; c /= 2; cout << "A /= 2 => " << c << endl;
    c = a; c %= 2; cout << "A %= 2 => " << c << endl;
    cout << "A + B = " << (a + b) << endl;
    cout << "A - B = " << (a - b) << endl;
    cout << "A * 2 = " << (a * 2.0f) << endl;
    cout << "B / 2 = " << (b / 2.0f) << endl;
    cout << "B % 2 = " << (b % 2) << endl;
    cout << "A << 1 = " << (a << 1) << endl;
    cout << "B >> 1 = " << (b >> 1) << endl;
    cout << "A == B: " << (a == b ? "true" : "false") << endl;
    cout << "A != B: " << (a != b ? "true" : "false") << endl;
    cout << "A[0] = " << a[0] << endl;
    cout << "A > B:  " << (a > b ? "true" : "false") << endl;
    cout << "A >= B: " << (a >= b ? "true" : "false") << endl;
    cout << "A < B:  " << (a < b ? "true" : "false") << endl;
    cout << "A <= B: " << (a <= b ? "true" : "false") << endl;
    cout << "A[1000] = " << a[1000] << " (Error: " << a.getCodeError() << ")" << endl;
    a();
    return 0;
}
