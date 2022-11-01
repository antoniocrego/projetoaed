//
// Created by andre on 19-10-2022.
//
#ifndef AED_PROJECT_ESTUDANTE_H
#define AED_PROJECT_ESTUDANTE_H

#include <string>
#include <vector>
#include "UCTurma.h"

class Estudante {
public:
    Estudante(int studentcode, string name);
    int getCode() const;
    string getName() const;
    vector<UCTurma> getturmasEstudante();
    void adicionarTurma(const UCTurma &turma);
    void print() const;
    bool operator==(const Estudante &aluno) const;

private:
    int studentcode_;
    string name_;
    vector<UCTurma> turmasEstudante;

};


#endif //AED_PROJECT_ESTUDANTE_H
