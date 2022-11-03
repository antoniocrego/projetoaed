//
// Created by andre on 19-10-2022.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "Estudante.h"
#include "Aula.h"
#include <vector>
#include <set>
#include <queue>
#include "Pedido.h"
#ifndef AED_PROJECT_GESTAOHORARIOS_H
#define AED_PROJECT_GESTAOHORARIOS_H


class GestaoHorarios {
public:
    GestaoHorarios();
    void readAulas();
    void readEstudantes();
    void readCodes();
    void readTurmas();
    void addPedido(const Pedido& x);
    void processarPedido();
    void addEstudante(const Estudante& e);
    bool isPossible(Aula& aula) const;
    vector<Estudante> getEstudantes() const;
    vector<UCTurma> getUCTurmas() const;
    vector<string> getCodes() const;
    vector<string> getTurmas() const;
    queue<Pedido> getPedidos() const;
    vector<Pedido> getSuccessos() const {return sucesso;};
    vector<Pedido> getFails() const {return fail;};

private:
    vector<Estudante> estudantes;
    vector<UCTurma> horario;
    vector<string> codes;
    vector<string> turmas;
    queue<Pedido> pedidos;
    vector<Pedido> sucesso;
    vector<Pedido> fail;
};


#endif //AED_PROJECT_GESTAOHORARIOS_H
