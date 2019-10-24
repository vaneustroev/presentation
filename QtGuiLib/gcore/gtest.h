// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef GTEST
#define GTEST

#include <iostream>
#include <numeric>
#include <vector>

#include <stdio.h>
#include <string.h>

namespace Garbage {

class monstr
{
public:
    monstr(int health=1);
    monstr(char *name);
    ~monstr(void);

    monstr(const monstr &M);

private:

    char *name;
    int health;
    int ammo;
    int skin;
};

//template <class T> class A
//{
//public:
//    T x1; T x2;

//    T func(T x3)
//    {
//        x3 += x1 + x2; return x3;
//    }
//};

//class A
//{
//public: // error 1
//    char* m_Char;

//    //A(const char* chr)
//    A(const char* chr)
//    {
//        m_Char = new char[strlen(chr)];
//        memcpy(m_Char, chr, strlen(chr));
//    }

//    ~A()
//    {
//        delete m_Char;
//    }

//    friend void printf(A oA);
//};

//class A
//{
//bool m_bFlag;

//public:
//  A(bool b) { m_bFlag = b;}
//};


//class A
//{
//public:
//  A () {}
//  virtual void func1() {printf("A1");}
//  void func2() {printf("A2");}
//  virtual void func3() {printf("A3");}
//  virtual void func4() {func1(); func2(); func3();}
//};

//class B : public A
//{
//public:
//  B () {}
//  void func1() {printf("B1");}
//  void func2() {printf("B2");}
//  virtual void func3() {printf("B3");}
//};

//class A
//{
//public:
//  A () {std::cerr << "A" << std::endl;}
//  virtual void func1() {std::cerr << "A1";}
//  void func2() {std::cerr << "A2";}
//  virtual void func3() {std::cerr << "A3";}
//  virtual void func4() {func1(); func2(); func3();}
//};

//class B : public A
//{
//public:
//  B () {std::cerr << "B" << std::endl;}
//  void func1() {std::cerr << "B1";}
//  void func2() {std::cerr << "B2";}
//  virtual void func3() {std::cerr << "B3";}
//};

class B
{
public:
    B(int i=0) {
        std::cerr << "B" << i << "\r\n";
    }
};

//class A
//{
//public:
//    A():ch('k'), a(0){}

//    int a;
//    int b;
//    static int cc = 40;
//    static float f;
//    static float g;
//    char ch;

//    static void func()
//    {
//        static int vv = 40;
//    }

//};

class A
{
public:
    A():ch(12), a(11){}

    B a;
    B b;
    static B cc;
    static B f;
    static B g;
    B ch;

    static void func()
    {
        static B vv = 40;
    }

};

short Sum(short * pArray, int nSize);
short sumAccumulate(std::vector<short> pArray);

} // namespace Garbage

#endif // GTEST

