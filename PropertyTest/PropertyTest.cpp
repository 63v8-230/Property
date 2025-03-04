#include <iostream>
#include <cmath>
#include <Windows.h>

#include "Property.h"
//#include "Property_old.h"

int main()
{
    //テスト1 int型 Get改造
    int t1_value = 0;
    int t1v = 90;

    Property<int> t1
    {
        [&t1v]()-> int& { return t1v; },
        [&t1_value](const int& _value) { t1_value = _value + 10; }
    };

    t1 = 10;
    std::cout << "t1: " << t1 << std::endl;

    //===============================
    //テスト2 float型 Set改造
    float t2_value = 0;

    Property<float> t2
    {
        [&t2_value]()-> float& { return t2_value; },
        [&t2_value](const float& _value) { t2_value = floorf(_value); }
    };

    t2 = 33.4f;
    std::cout << "t2: " << t2 << std::endl;


    //===============================
    //テスト アクセス権限

    SYSTEMTIME t;
    GetLocalTime(&t);

    //Getterのみ
    PropertyReadOnly <WORD> t3
    {
        [&t]()-> WORD& { return t.wMinute; },
        //[](const WORD& _value) {  } // <- エラー
    };

    //t3 = 100; // <- エラー

    std::cout << "t3(現在の分): " << t3 << std::endl;

    //===============================
    //テスト Setter <- Getter

    int t41 = 50;
    long t42 = 10;
    
    PropertyReadOnly<int> t4r
    {
        [&t41]()->int& { return t41; }
    };

    PropertyWriteOnly<long> t4w
    {
        [&t42](const long& _value) { t42 = _value; }
    };

    t4w = t4r;

    std::cout << "t4: " << t42 << std::endl;
}
