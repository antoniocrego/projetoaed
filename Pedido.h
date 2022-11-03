//
// Created by andre on 02-11-2022.
//

#ifndef AED_PROJECT_PEDIDO_H
#define AED_PROJECT_PEDIDO_H
#include <string>
#include <iostream>
using namespace std;

class Pedido {
    public:
        Pedido(int studentcode, string uccode, string classcode, string uccode2, string classcode2, string type);
        int getStudent() const {return studentcode_;};
        string getUC() const {return uccode_;};
        string getClass() const {return classcode_;};
        string getUC2() const {return uccode2_;};
        string getClass2() const {return classcode2_;};
        string getType() const {return type_;};
        void print() const;
    private:
        int studentcode_;
        string uccode_;
        string classcode_;
        string uccode2_;
        string classcode2_;
        string type_;
};


#endif //AED_PROJECT_PEDIDO_H
