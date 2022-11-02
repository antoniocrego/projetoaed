//
// Created by andre on 02-11-2022.
//

#ifndef AED_PROJECT_PEDIDO_H
#define AED_PROJECT_PEDIDO_H


#include "UCTurma.h"
#include "Estudante.h"

class Pedido {

    public:
        Pedido(int studentcode, string name, string uccode, string classcode );


    private:

        int studentcode_;
        string name_;
        string  uccode_;
        string classcode_;

};


#endif //AED_PROJECT_PEDIDO_H
