// PropertyTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cmath>
#include <ctime>

#include "Property.h"

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
    ////テスト アクセス権限 あんま上手くいかないのでとりあえず後回し
    //int t3_value = 0;

    ////Getterのみ
    //Property<int> t3
    //{
    //    [&t3_value]()-> int& { return t3_value; },
    //    [](const int& _value) {  }
    //};

    //t3_value = 50;

    //t3 = 100;

    //std::cout << "t3: " << t3 << std::endl;
}
