//
// Created by andre on 02-11-2022.
//

#include "Pedido.h"
Pedido::Pedido(int studentcode, string uccode, string classcode, string uccode2, string classcode2, string type){
    studentcode_=studentcode;
    uccode_=uccode;
    classcode_=classcode;
    uccode2_=uccode2;
    classcode2_=classcode2;
    type_=type;
}

void Pedido::print() const{
    if (type_=="addClass") cout << "*\tAdicionar aluno " << studentcode_ << " à turma " << classcode2_ << " da cadeira " << uccode2_ << ".";
    if (type_=="removeClass") cout << "*\tRemover aluno " << studentcode_ << " da sua turma da cadeira " << uccode_ << ".";
    if (type_=="addUC") cout << "*\tAdicionar aluno " << studentcode_ << " à cadeira " << uccode2_ << ".";
    if (type_=="removeUC") cout << "*\tRemover aluno " << studentcode_ << " da cadeira " << uccode_ << ".";
    if (type_=="changeClass") cout << "*\tTrocar aluno " << studentcode_ << " da sua turma da cadeira " << uccode_ << " para a turma " << classcode2_ << ".";
}