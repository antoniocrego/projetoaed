//
// Created by andre on 19-10-2022.
//

#include "GestaoHorarios.h"
#include<algorithm>
GestaoHorarios::GestaoHorarios() {
    readAulas();
    readEstudantes();
    readCodes();
    readTurmas();
}

void GestaoHorarios::readEstudantes(){
    ifstream in("../Tests/students_classes.csv");
    int i=0;
    string line;
    getline(in,line);
    while (getline(in,line)) {
        string StudentCode, StudentName, UcCode, ClassCode;
        istringstream iss(line);
        while (iss.good()) {
            string substr;
            getline(iss, substr, ',');
            if (i == 0) {
                StudentCode = substr;
            }
            if (i == 1) {
                StudentName = substr;
            }
            if (i == 2) {
                UcCode = substr;
            }
            if (i == 3) {
                ClassCode = substr.substr(0,7);
            }
            i++;
        }
        i = 0;
        int StudentCodeInt = stoi(StudentCode);
        UCTurma turma = UCTurma(UcCode, ClassCode);
        Estudante estudante = Estudante(StudentCodeInt, StudentName);
        if (find(estudantes.begin(), estudantes.end(), estudante) == estudantes.end()) {
            estudantes.push_back(estudante);
            estudantes.back().adicionarTurma(turma);
        } else (find(estudantes.begin(), estudantes.end(), estudante)->adicionarTurma(turma));
    }
}
void GestaoHorarios::readAulas() {
    ifstream in1("../Tests/classes.csv");
    string line;
    getline(in1, line);
    int i=0;
    while (getline(in1, line)) {
        string ClassCode, UcCode, Weekday, StartHour, Duration, Type;
        istringstream iss(line);
        while (iss.good()) {
            string substr;
            getline(iss, substr, ',');
            if (i==0){
                ClassCode=substr;
            }
            if (i==1){
                UcCode=substr;
            }
            if (i==2){
                Weekday=substr;
            }
            if (i==3){
                StartHour=substr;
            }
            if (i==4){
                Duration=substr;
            }
            if (i==5){
                Type=substr;
                if (Type[Type.length() - 1] == '\r') Type = Type.substr(0, Type.length() - 1);
            }
            i++;
        }
        i=0;
        float start = stof(StartHour);
        float d = stof(Duration);
        UCTurma turma = UCTurma(UcCode, ClassCode);
        Aula aula= Aula(turma.getUC(), turma.getClassCode(), Weekday, start, d, Type);
        if (find(horario.begin(), horario.end(), turma)==horario.end()){
            horario.push_back(turma);
            horario.back().adicionarAula(aula);
        }
        else (find(horario.begin(), horario.end(), turma)->adicionarAula(aula));
/*        for (UCTurma c : horario){
            if (c==turma){
                c.adicionarAula(aula);
                break;
            }
            else if (c==horario.back()){
                horario.push_back(turma);
                horario.back().adicionarAula(aula);
                break;
            }
        }
        if (horario.empty()){
            horario.push_back(turma);
            horario.back().adicionarAula(aula);
        }*/
    }
}
void GestaoHorarios::readCodes() {
    ifstream in1("../Tests/classes_per_uc.csv");
    string line;
    getline(in1, line);
    int i=0;
    while (getline(in1, line)) {
        string Uccode;
        Uccode = line.substr(0,line.find_first_of(','));
        if (find(codes.begin(), codes.end(), Uccode)==codes.end()){
            codes.push_back(Uccode);
        }
        /*
        for (string c: codes){
            if (Uccode==c){
                break;
            }
            if (c==codes.back()) {
                codes.push_back(Uccode);
                break;
            }
        }
        if (codes.empty()){
            codes.push_back(Uccode);
        }*/
    }
}
void GestaoHorarios::readTurmas() {
    ifstream in1("../Tests/classes_per_uc.csv");
    string line;
    getline(in1, line);

    while (getline(in1, line)) {
        string turma;
        turma = line.substr(line.find_first_of(',')+1,7);
        if (find(turmas.begin(), turmas.end(), turma)==turmas.end()) turmas.push_back(turma);
        /*for (string t: turmas){
            if (turma==t){
                break;
            }
            if (t==turmas.back()) {
                turmas.push_back(turma);
                break;
            }
        }
        if (turmas.empty()){
            turmas.push_back(turma);
        }*/
    }
}

void GestaoHorarios::addPedido(const Pedido& x) {
    pedidos.push(x);
}

void GestaoHorarios::processarPedido() {
    bool success = true;
    Pedido current = pedidos.front();
    if (current.getType()=="addClass"){                // precisa compatibilidade horários

    }
    if (current.getType()=="removeClass"){
        if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()){
            success = false;
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC())==codes.end()){
            success = false;
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else{
            find(estudantes.begin(),estudantes.end(),current.getStudent())->removerTurma(current.getUC());
            cout << " : O estudante " << current.getStudent() << " foi removido da sua turma da UC " << current.getUC() << " com sucesso!" << endl;
            sucesso.push_back(current);
        }
    }
    if (current.getType()=="addUC"){
        if (find(codes.begin(),codes.end(),current.getUC2())==codes.end()){
            success = false;
            current.print();
            cout << " : UC inválida!" << endl;
        }
        else {
            if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()) {
                string nome;
                cout << endl << "Insira o nome do novo estudante: ";
                while (!(cin >> nome)) {
                    cout << "Opção inválida!" << endl;
                    cin.clear();
                    cout << endl << "Insira o nome do novo estudante: ";
                }
                estudantes.emplace_back(Estudante(current.getStudent(), nome));
            }
            vector<UCTurma> copy = find(estudantes.begin(), estudantes.end(),current.getStudent())->getturmasEstudante();
            for (const UCTurma &c: copy) {
                if (c.getUC() == current.getUC2()) {
                    current.print();
                    cout << " : O estudante já se encontra nesta UC." << endl;
                    fail.push_back(current);
                    success = false;
                    break;
                }
            }
            if (success) {
                find(estudantes.begin(), estudantes.end(), current.getStudent())->adicionarTurma(
                        UCTurma(current.getUC2(), "N/A"));
                current.print();
                cout << " : O estudante " << current.getStudent() << " foi inserido na UC " << current.getUC2() << " com sucesso!" << endl;
                sucesso.push_back(current);
            }
        }
    }
    if (current.getType()=="removeUC"){
        if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()){
            success = false;
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC())==codes.end()){
            success = false;
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else{
            find(estudantes.begin(),estudantes.end(),current.getStudent())->removerUC(current.getUC());
            current.print();
            cout << " : O aluno " << current.getStudent() << " foi removido da UC " << current.getUC() << " e todas as turmas associadas com sucesso!" << endl;
            sucesso.push_back(current);
        }
    }
    if (current.getType()=="changeClass"){            // precisa compatibilidade horários

    }
    pedidos.pop();
}

void GestaoHorarios::addEstudante(const Estudante &e) {
    estudantes.push_back(e);
}

vector<Estudante> GestaoHorarios::getEstudantes() const {
    return estudantes;
}
vector<UCTurma> GestaoHorarios::getUCTurmas() const {
    return horario;
}
vector<string> GestaoHorarios::getCodes() const{
    return codes;
}
vector<string> GestaoHorarios::getTurmas() const {
    return turmas;
}
queue<Pedido> GestaoHorarios::getPedidos() const {
    return pedidos;
}

bool GestaoHorarios::isPossible(Aula& aula) const {
    for (UCTurma t:horario){
        for(Aula a: t.getHorarioUCTurma()){
            if(a.getDay()!= aula.getDay()) continue;
            if(a.getTipo()=="T" || aula.getTipo()=="T") continue;
            if(a.getInicio()==aula.getInicio()) return false;
            if((a.getInicio() < aula.getInicio() < a.getFim()) && (aula.getInicio() < a.getInicio() < aula.getFim())) return false;
        }
    }
    return true;
}