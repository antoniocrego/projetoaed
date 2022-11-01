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
#ifndef AED_PROJECT_GESTAOHORARIOS_H
#define AED_PROJECT_GESTAOHORARIOS_H


class GestaoHorarios {
public:
    GestaoHorarios();
    void readAulas();
    void readEstudantes();
    void readCodes();
    void readTurmas();
    vector<Estudante> getEstudantes() const;
    vector<UCTurma> getUCTurmas() const;
    vector<string> getCodes() const;

    vector<string> getTurmas() const;


private:
    vector<Estudante> estudantes;
    vector<UCTurma> horario;
    vector<string> codes;
    vector<string> turmas;
};


#endif //AED_PROJECT_GESTAOHORARIOS_H
