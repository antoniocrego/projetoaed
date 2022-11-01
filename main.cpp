#include <iostream>
#include <sstream>
#include <fstream>
#include "Estudante.h"
#include "Aula.h"
#include "GestaoHorarios.h"
#include "UCTurma.h"
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;
bool sortEstudantesNome(const Estudante &Estudante1, const Estudante &Estudante2 ){
    if(Estudante1.getName()< Estudante2.getName()){
        return true;
    }
    return false;
}
void Option1(GestaoHorarios gestor, string code){
    vector <Estudante> StudentsUC;
    for (Estudante a: gestor.getEstudantes()){
        for (UCTurma turma: a.getturmasEstudante()){
            if (turma.getUC()==code) StudentsUC.push_back(a);
        }
    }
    sort(StudentsUC.begin(),StudentsUC.end(), sortEstudantesNome);
    for (Estudante a: StudentsUC){
        cout << a.getCode() << ',' << a.getName() << endl;
    }
    cout << "Estão inscritos " << StudentsUC.size() << " alunos nesta disciplina";
}
void Option2(GestaoHorarios gestor, string turma, string code){
    vector<Estudante> StudentsTurma;
    for (Estudante a: gestor.getEstudantes()){
        for (UCTurma turmas: a.getturmasEstudante()){
            if (turmas.getUC()==code && turmas.getClassCode()==turma) StudentsTurma.push_back(a);
        }
    }
    sort(StudentsTurma.begin(),StudentsTurma.end(), sortEstudantesNome);
    for (Estudante a: StudentsTurma){
        cout << a.getCode() << ',' << a.getName() << endl;
    }
    if (StudentsTurma.empty()) cout << "Nenhum estudante está inscrito na turma " << turma << " da UC " << code << endl;
}
void Option3(GestaoHorarios gestor, string name) {
    vector<Estudante> estudantes;
    vector<UCTurma> turmas;
    vector<Aula> horario;
    for (Estudante e: gestor.getEstudantes()) {
        if (e.getName() == name) {
            turmas = e.getturmasEstudante();
        }
    }
    for (UCTurma t: turmas) {
        for (Aula a: t.getHorarioUCTurma())
            horario.push_back(a);
    }
    for (Aula a: horario) {
        a.print();
    }
}

void Option4(GestaoHorarios gestor, char ano){

    vector <Estudante> firstyear;
    vector <Estudante> secondyear;
    vector <Estudante> thirdyear;
    if (ano=='3'){
        for (Estudante a: gestor.getEstudantes()){
            for(UCTurma turma: a.getturmasEstudante() ){
                if (turma.getClassCode().at(0)==ano){
                    thirdyear.push_back(a);
                    break;
                }
            }
        }
    }
    if (ano=='2'){
        for (Estudante a: gestor.getEstudantes()){
            for(UCTurma turma: a.getturmasEstudante() ){
                if (turma.getClassCode().at(0)==ano){
                    secondyear.push_back(a);
                    break;
                }
            }
        }
    }
    if (ano=='1'){
        for (Estudante a: gestor.getEstudantes()){
            for(UCTurma turma: a.getturmasEstudante() ){
                if (turma.getClassCode().at(0)==ano){
                    secondyear.push_back(a);
                    break;
                }
            }
        }
    }
}

int main() {
    bool flag=true;
    GestaoHorarios gestor = GestaoHorarios();
    int quit;
    while(flag) {
        cout << endl << "Gestor de Horários de Estudantes L.EIC" << endl;
        cout << "Digite 0 a qualquer momento para fechar o programa" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "1 - Ver estudantes de uma cadeira" << endl;
        cout << "2 - Ver estudantes de uma turma" << endl;
        cout << "3 - Ver estudantes inscritos em n UCs" << endl;
        cout << "4 - Ver estudantes de um ano letivo" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Selecione uma opção: ";
        int selection = 0;
        while (!(cin >> selection) or selection > 9 or selection < 0) {
            cout << "Opção inválida!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Selecione uma opção: ";
        }
        if (selection == 1) {
            string code;
            vector<string> codigos = gestor.getCodes();
            cout << "Insira o código da UC: ";
            while (cin>>code and find(codigos.begin(), codigos.end(), code) == codigos.end()) {
                if (code=="0") break;
                cout << "Opção inválida!" << endl;
                cin.clear();
                cout << endl << "Insira o código da UC: ";
            }
            if (code=="0") flag = false;
            Option1(gestor, code);
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            while (!(cin >> quit) or (quit != 0 and quit != 1)) {
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Selecione uma opção: ";
            }
            if (quit==0) flag = false;
        }
        if (selection == 2){
            string code;
            string turma;
            vector<string> codigos = gestor.getCodes();
            vector<string> turmas = gestor.getTurmas();
            cout << "Insira o código da UC: ";
            while (cin>>code and find(codigos.begin(), codigos.end(), code) == codigos.end()) {
                if (code=="0") break;
                cout << "Opção inválida!" << endl;
                cin.clear();
                cout << endl << "Insira o código da UC: ";
            }
            if (code=="0") flag = false;
            cout << "Insira a turma: ";
            while (cin>>turma and find(turmas.begin(), turmas.end(), turma) == turmas.end()) {
                if (turma=="0") break;
                cout << "Opção inválida!" << endl;
                cin.clear();
                cout << endl << "Insira a turma: ";
            }
            if (turma=="0") flag = false;
            Option2(gestor,turma,code);
        }
        if (selection == 3){
            string name;
            cout << "Insira o nome do Estudante para ver o seu horário: ";
            cin>> name;
            vector <string> Turmas= gestor.getTurmas();
            /*while (!(cin >> turma) or find(Turmas().begin(), Turmas().end(), turma) == gestor.getCodes().end()) {
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Insira o código da UC: ";
                cin >> turma;
            }*/
            Option3(gestor,name);
        }
        if (selection==0){
            flag=false;
        }

//    for (UCTurma c : gestor.getUCTurmas()) c.print();           // test
//    for (Estudante c: gestor.getEstudantes()) c.print();        // test
    }
    return 0;
}