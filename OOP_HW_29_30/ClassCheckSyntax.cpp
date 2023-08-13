#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { cin.get(); cin.get(); } } _;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))

// ������� 2.
// ���� ������ ��������, ��������� �����, ������� �������� ������ ';'.
// � ������ ����� ���� ��������, �������, ���������� ������.
// ������ ����� ���� ������������ � ������������.
// ���������� ��������� ������������ ����������� ������.
// ��� ���� ����������, ����� ����������� ��������� ������� :
// 1) ������ ����������� ������ ������ ����� ������ ����� �� �����������.�������� ����� ������ ���� �����.
// 2) ����������� � ����������� ���� ������ ������ ����� ������ ���� ��������� ����������� �� ��������� ���� � �����.
// 
// - ������ ���������� ������ : ({ x - y - z }*[x + 2y] - (z + 4x));
// -������ ������������ ������ : ([x - y - z}*[x + 2y) - {z + 4x)]; .
// 
// ���� ��� ������� ��������� �������� �������������� ��������� � ������������ ������, ����� �������� ������ �� ����� ������������� ������ ������.

template <class T>
class Stack
{
private:
    T* Data; // ������ �����
    int Depth, SP; // ������� ������� �����, ��������� �� ������� �����
public:
    Stack() : Data(), Depth(), SP() {} // ������ ����
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
        delete[]Data; // ������� ������ ������
        Data = temp;  // ���������� ����� ����� ������� �����
        Depth = newDepth; // ����� ������� �����
        SP = MinCount;
    }
    // �������� ������ val � ����
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
        cout << "������: ����� �� ������� ����� �����!\n";
        //return ?
        throw "����� �� ������� ����� �����!"; // ����������
    }
    // cout << A.top();
    T top() const {
        if (SP > 0) {
            return Data[SP - 1]; // ���������� �� ��������
            //  - ����� Data[SP-1]
        }
        cout << "������: ����� �� ������� ����� �����!\n";
        throw "����� �� ������� ����� �����!"; // ����������
    }
    // A.top() = 123;
    T& top() {
        if (SP > 0) {
            return Data[SP - 1]; // ���������� �� ������
        }
        cout << "������: ����� �� ������� ����� �����!\n";
        throw "����� �� ������� ����� �����!"; // ����������
    }


    friend ostream& operator << (ostream& os, const Stack<T>& obj)
    {
        os << "Depth = " << obj.GetDepth() << endl;
        os << "Stack pointer = " << obj.GetSP() << endl;
        os << "Count = " << obj.GetSP() << endl;
        for (int i = 0; i < obj.GetSP(); i++)
        {
            os << obj.Data[i] << " ";
        }
        return os << endl; // return os;
    }

}; // class Stack<>;


class CheckSyntax
{
private:
    Stack<char> stack;
    string Sym;
    int Index;
public:
    CheckSyntax() : stack(), Sym(), Index(-1) {}

    string GetString() const { return Sym; }
    int GetIncorrectSym() const { return Index; }
    void SetIncorrectSym(int i) { Index = i; }

    bool IsCorrect()
    {
        for (int i = 0; i < Sym.size(); i++)
        {
            switch (Sym[i])
            {
            case '(': stack.push(')'); break;
            case '[': stack.push(']'); break;
            case '{': stack.push('}'); break;

            case ')':
            case ']':
            case '}':
                if (stack.GetSP() == 0 || stack.top() != Sym[i])
                {
                    SetIncorrectSym(i);
                    return false;
                }
                else { stack.pop(); }
                break;
            }
        }
        return stack.GetSP() == 0;
    }

    void ShowIncorrectSym()
    {
        if (Index != -1 && Index < Sym.size())
        {
            cout << "Incorrect symbol at index " << Index << ": " << Sym[Index] << endl;
        }
    }

    CheckSyntax& operator = (const string& s)
    {
        this->Sym = s;
        return *this;
    }

    friend ostream& operator<< (ostream& os, const CheckSyntax& obj)
    {
        os << obj.GetString() << endl;
        return os;
    }
};


int main()
{
    CheckSyntax A;
    CheckSyntax B;

    A = "({ x - y - z }*[x + 2y] - (z + 4x));";
    B = "([x-y-z}*[x+2y)-{z+4x)];";

    cout << "1) " << A;
    cout << "2) " << B;

    cout << "--------------------------------------------------\n";
    (A.IsCorrect()) ? cout << "Syntax is correct!" << endl : cout << "Error: Syntax is incorrect!" << endl;
    (B.IsCorrect()) ? cout << "Syntax is correct!" << endl : cout << "Error: Syntax is incorrect!" << endl;
    
    cout << "--------------------------------------------------\n";
    if (!A.IsCorrect()) { A.ShowIncorrectSym(); }
    if (!B.IsCorrect()) { B.ShowIncorrectSym(); }
}