//
// Created by andre on 19-10-2022.
//

#include "Aula.h"
#include <string>
#include <iostream>
using namespace std;

Aula::Aula(const string& uccode, const string& classcode, const string& dia, float inicio, float duracao, const string& tipo){
    uccode_ = uccode;
    classcode_ = classcode;
    dia_=dia;
    inicio_=inicio;
    duracao_=duracao;
    tipo_=tipo;
    fim_=inicio+duracao;
}

void Aula::print() {
    cout << "\tUC: " << uccode_ << ", Turma: " << classcode_ << ", Duração: " << inicio_ << "-" << fim_ << ", Tipo: " << tipo_ << endl;
}

string Aula::getDay() const{
    return dia_;
}

float Aula::getInicio() const{
    return inicio_;
}

float Aula::getFim() const{
    return fim_;
}

string Aula::getTipo() const {
    return tipo_;
}

bool Aula::operator<(const Aula &aula2) const {
    return inicio_<aula2.getInicio();
}
bool Aula::isPossible(const Aula& aula2) const {
    if(dia_ == aula2.getDay()){
        if(tipo_=="T" || aula2.getTipo()=="T") return true;
        else {
            if (inicio_==aula2.getInicio()) return false;
            if ((inicio_<aula2.getInicio()<fim_) && (aula2.getInicio()<inicio_<aula2.getFim())) return false;
        }
    }
    return true;
}