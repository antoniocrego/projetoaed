//
// Created by andre on 19-10-2022.
//

#include "Estudante.h"
#include <iostream>

Estudante::Estudante(int studentcode, string name) {
    studentcode_=studentcode;
    name_=name;
}

int Estudante::getCode() const {
    return studentcode_;
}

string Estudante::getName() const {
    return name_;
}

void Estudante::print() const {
    cout << studentcode_ << ',' << name_ << endl;
    for (UCTurma turma : turmasEstudante) turma.print();
}

bool Estudante::operator==(const Estudante &aluno) const{
    if (studentcode_==aluno.getCode()) return true;
    else return false;
}

bool Estudante::operator==(int x) const {
    return studentcode_==x;
}

bool Estudante::operator<(const Estudante &aluno) const{
    return name_<aluno.getName();
}

void Estudante::adicionarTurma(const UCTurma &turma){
    turmasEstudante.push_back(turma);
}
vector<UCTurma> Estudante::getturmasEstudante() {
    return turmasEstudante;
}

void Estudante::removerTurma(const UCTurma& turma){
    vector<UCTurma>::iterator itr;
    for (UCTurma t : turmasEstudante){
        if (turma.getClassCode()==t.getClassCode() && turma.getUC()==t.getUC()){
            break;
        }
        itr++;
    }
    turmasEstudante.erase(itr);
}
