#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { cin.get(); cin.get(); } } _;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))

// Шаблоны классов. Класса Стек
// Задание 1.
// Доделать работу в классе "2-Работа в классе-Stack.txt".
// Реализовать методы :
// Stack(int depth);
// Stack(const Stack& obj);
// Stack& operator=(const Stack& obj);
// ~Stack();

template <class T>
class Stack
{
private:
    T* Data; // данные стека
    int Depth, SP; // текщуая глубина стека, указатель на вершину стека
public:
    Stack() : Data(), Depth(), SP() {} // пустой стек
    Stack(int depth) : Data(), SP(), Depth()
    {
        SetDepth(depth);
    }
    
    Stack(const Stack<T>& obj) : Data(), SP(), Depth()
    {
        *this = obj;
    }

    Stack<T>& operator=(const Stack<T>& obj)
    {
        SetDepth(obj.GetDepth());
        for (int i = 0; i < obj.GetSP(); i++)
        {
            push(obj.Data[i]);
        }
        return *this;
    }

    ~Stack() { delete[] Data; }

    int GetSP()    const { return SP; }
    int GetDepth() const { return Depth; }

    void SetDepth(int newDepth) {
        T* temp = new T[newDepth];
        int MinCount = (SP < newDepth) ? SP : newDepth;
        for (int i = 0; i < MinCount; i++) {
            temp[i] = Data[i];
        }
        delete[]Data; // удаляем старый массив
        Data = temp;  // запоминаем новый адрес массива стека
        Depth = newDepth; // новая глубина стека
        SP = MinCount;
    }
    // положить данные val в стек
    void push(T val) {
        if (SP < Depth) {
            Data[SP] = val;
            SP++;
        }
        else {
            SetDepth(Depth * 1.5 + 1);
            Data[SP++] = val;
        }
    }
    //
    T pop() {
        if (SP > 0) {
            SP--;
            return Data[SP];
        }
        cout << "Ошибка: Выход за границы стека снизу!\n";
        //return ?
        throw "Выход за границы стека снизу!"; // исключение
    }
    // cout << A.top();
    T top() const {
        if (SP > 0) {
            return Data[SP - 1]; // возвращаем по значению
            //  - копия Data[SP-1]
        }
        cout << "Ошибка: Выход за границы стека снизу!\n";
        throw "Выход за границы стека снизу!"; // исключение
    }
    // A.top() = 123;
    T& top() {
        if (SP > 0) {
            return Data[SP - 1]; // возвращаем по ссылке
        }
        cout << "Ошибка: Выход за границы стека снизу!\n";
        throw "Выход за границы стека снизу!"; // исключение
    }


    friend ostream& operator << (ostream& os,
        const Stack<T>& obj)
    {
        os << "Depth = " << obj.GetDepth() << endl;
        os << "Stack pointer = " << obj.GetSP() << endl;
        os << "Count = " << obj.GetSP() << endl;
        for (int i = 0; i < obj.GetSP(); i++) {
            os << obj.Data[i] << " ";
        }
        return os << endl; // return os;
    }

}; // class Stack<>;


int main()
{
    Stack<int> A(10);
    A.push(1);
    A.push(5);
    A.push(7);
    A.push(6);
    A.push(9);
    cout << A;

    cout << "--------------------------------------------------\n";
    Stack<int> B(A);
    cout << B;

    cout << "--------------------------------------------------\n";
    Stack<int> C;
    C = A;
    cout << C;
}