#include <iostream>
#include <cmath>
using namespace std;

class VectorFloat {
private:
    float* data;  
    int size;    
public:
   
    VectorFloat(int s = 1) : size(s) {
        data = new float[size];  // Виділення пам'яті під масив
        for (int i = 0; i < size; i++) data[i] = 0;  
    }
    
    // Конструктор копіювання
    VectorFloat(const VectorFloat& other) : size(other.size) {
        data = new float[size];  
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];  // Копіювання даних
        }
    }
    
    // Оператор присвоєння
    VectorFloat& operator=(const VectorFloat& other) {
        if (this != &other) {
            delete[] data;  
            size = other.size;  
            data = new float[size];  // Виділяємо нову пам'ять
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];  
            }
        }
        return *this;
    }

   
    ~VectorFloat() {
        delete[] data;  // Звільняємо пам'ять
    }
    
    void input() {
       
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]: ";
            cin >> data[i];
        }
    }
    
    void output() const {
      
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]" << endl;
    }

    VectorFloat operator+(const VectorFloat& other) const {
        // Операція додавання двох векторів
        VectorFloat result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    VectorFloat operator-(const VectorFloat& other) const {
        // Операція віднімання двох векторів
        VectorFloat result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    VectorFloat operator*(float val) const {
        // Операція множення вектора на число
        VectorFloat result(size);
        for (int i = 0; i < size; i++) result.data[i] = data[i] * val;
        return result;
    }

    VectorFloat operator/(float val) const {
        // Операція ділення вектора на число
        VectorFloat result(size);
        for (int i = 0; i < size; i++) result.data[i] = (val != 0) ? data[i] / val : 0;
        return result;
    }

    bool operator==(const VectorFloat& other) const {
        // Операція порівняння двох векторів
        for (int i = 0; i < size; i++) {
            if (fabs(data[i] - other.data[i]) > 1e-6) 
                return false;
        }
        return true;
    }

    float& operator[](int index) {
        
        return data[index];
    }
};

int main() {
    int size;
    cout << "Введіть розмір масиву: ";
    cin >> size;
    VectorFloat a(size), b(size);
    
   
    cout << "Введіть елементи для вектора A: " << endl;
    a.input();
    
    cout << "Введіть елементи для вектора B: " << endl;
    b.input();
    
   
    cout << "Вектор A: ";
    a.output();
    
    cout << "Вектор B: ";
    b.output();
    
   
    VectorFloat c = a + b;
    cout << "A + B: ";
    c.output();
    
    c = a - b;
    cout << "A - B: ";
    c.output();
    
    c = a * 2;
    cout << "A * 2: ";
    c.output();
    
    c = b / 2;
    cout << "B / 2: ";
    c.output();
    
    // Порівняння векторів
    cout << "A == B: " << (a == b ? "true" : "false") << endl;
    

    cout << "A[0]: " << a[0] << endl;
    
    return 0;
}
