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
            if (i == 0) StudentCode = substr;
            if (i == 1) StudentName = substr;
            if (i == 2) UcCode = substr;
            if (i == 3) ClassCode = substr.substr(0,7);
            i++;
        }
        i = 0;
        int StudentCodeInt = stoi(StudentCode);
        UCTurma turma = UCTurma(UcCode, ClassCode);
        Estudante estudante = Estudante(StudentCodeInt, StudentName);
        if (find(estudantes.begin(), estudantes.end(), estudante) == estudantes.end()) {
            estudantes.push_back(estudante);
            estudantes.back().adicionarTurma(turma);
        }
        else (find(estudantes.begin(), estudantes.end(), estudante)->adicionarTurma(turma));
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
            if (i==0) ClassCode=substr;
            if (i==1) UcCode=substr;
            if (i==2) Weekday=substr;
            if (i==3) StartHour=substr;
            if (i==4) Duration=substr;
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
    }
}
void GestaoHorarios::readCodes() {
    ifstream in1("../Tests/classes_per_uc.csv");
    string line;
    getline(in1, line);
    while (getline(in1, line)) {
        string Uccode;
        Uccode = line.substr(0,line.find_first_of(','));
        if (find(codes.begin(), codes.end(), Uccode)==codes.end()) codes.push_back(Uccode);
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
    }
}

void GestaoHorarios::addPedido(const Pedido& x) {
    pedidos.push(x);
}

void GestaoHorarios::processarPedido() {
    bool doable = true;
    Pedido current = pedidos.front();
    if (current.getType()=="addClass"){
        if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()){
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC2())==codes.end()){
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else if (find(horario.begin(),horario.end(),UCTurma(current.getUC2(), current.getClass2()))==horario.end()){
            current.print();
            cout << " : A turma não existe!" << endl;
            fail.push_back(current);
        }
        else{
            int max;
            cout << endl << "Insira o numero máximo de estudantes da turma: ";
            while (!(cin >> max) or max<0) {
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Insira o numero máximo de estudantes da turma: ";
            }
            for (const UCTurma& t : find(estudantes.begin(),estudantes.end(),current.getStudent())->getturmasEstudante()){
                if (t.getUC()==current.getUC2() && t.getClassCode()=="N/A"){
                    doable = true;
                    break;
                }
                else doable = false;
            }
            if (doable){
                int current_students = 0;
                auto turmaDestino = find(horario.begin(),horario.end(),UCTurma(current.getUC2(), current.getClass2()));
                for (Estudante e: estudantes){
                    for (UCTurma t : e.getturmasEstudante()){
                        if (t==*turmaDestino) current_students++;
                    }
                }
                if (current_students+1>max){
                    current.print();
                    cout << " : A turma " << current.getClass2() << " da UC " << current.getUC2() << " excederia o limite de " << max << " estudantes." << endl;
                    fail.push_back(current);
                }
                else {
                    for (UCTurma turma: find(estudantes.begin(), estudantes.end(),
                                             current.getStudent())->getturmasEstudante()) {
                        for (const Aula &a: turma.getHorarioUCTurma()) {
                            for (const Aula &b: turmaDestino->getHorarioUCTurma()) {
                                if (!a.isPossible(b)) doable = false;
                            }
                        }
                    }
                    if (doable) {
                        find(estudantes.begin(), estudantes.end(), current.getStudent())->removerUC(current.getUC());
                        find(estudantes.begin(), estudantes.end(), current.getStudent())->adicionarTurma(*turmaDestino);
                        cout << " : O estudante " << current.getStudent()
                             << " foi inserido na turma " << current.getClass2() << " da UC "
                             << current.getUC2() << " com sucesso!" << endl;
                        sucesso.push_back(current);
                    }
                    else {
                        current.print();
                        cout << " : O horário do estudante " << current.getStudent()
                             << " é incompatível com o da turma " << current.getClass2() << " da UC "
                             << current.getUC2() << "." << endl;
                        fail.push_back(current);
                    }
                }
            }
            else{
                current.print();
                cout << " : O estudante " << current.getStudent() << " não está inscrito na UC " << current.getUC() << " ou já se encontra numa turma." << endl;
                fail.push_back(current);
            }
        }
    }
    if (current.getType()=="removeClass"){
        if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()){
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC())==codes.end()){
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else{
            for (const UCTurma& t : find(estudantes.begin(),estudantes.end(),current.getStudent())->getturmasEstudante()){
                if (t.getUC()==current.getUC()){
                    doable = true;
                    break;
                }
                else doable = false;
            }
            if (doable) {
                find(estudantes.begin(), estudantes.end(), current.getStudent())->removerTurma(current.getUC());
                cout << " : O estudante " << current.getStudent() << " foi removido da sua turma da UC "
                     << current.getUC() << " com sucesso!" << endl;
                sucesso.push_back(current);
            }
            else{
                current.print();
                cout << " : O estudante " << current.getStudent() << " não está inscrito na UC " << current.getUC() << "." << endl;
                fail.push_back(current);
            }
        }
    }
    if (current.getType()=="addUC"){
        if (find(codes.begin(),codes.end(),current.getUC2())==codes.end()){
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl << "Insira o nome do novo estudante: ";
                }
                estudantes.emplace_back(Estudante(current.getStudent(), nome));
            }
            for (const UCTurma &c: find(estudantes.begin(), estudantes.end(),current.getStudent())->getturmasEstudante()) {
                if (c.getUC() == current.getUC2()) {
                    current.print();
                    cout << " : O estudante já se encontra nesta UC." << endl;
                    fail.push_back(current);
                    doable = false;
                    break;
                }
            }
            if (doable) {
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
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC())==codes.end()){
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else{
            for (const UCTurma& t : find(estudantes.begin(),estudantes.end(),current.getStudent())->getturmasEstudante()){
                if (t.getUC()==current.getUC()){
                    doable = true;
                    break;
                }
                else doable = false;
            }
            if (doable) {
                find(estudantes.begin(), estudantes.end(), current.getStudent())->removerUC(current.getUC());
                current.print();
                cout << " : O aluno " << current.getStudent() << " foi removido da UC " << current.getUC()
                     << " e todas as turmas associadas com sucesso!" << endl;
                sucesso.push_back(current);
            }
            else{
                current.print();
                cout << " : O aluno " << current.getStudent() << " não está inscrito na UC " << current.getUC() << "." << endl;
                fail.push_back(current);
            }
        }
    }
    if (current.getType()=="changeClass"){
        if (find(estudantes.begin(), estudantes.end(), current.getStudent()) == estudantes.end()){
            current.print();
            cout << " : O estudante não existe!" << endl;
            fail.push_back(current);
        }
        else if (find(codes.begin(),codes.end(),current.getUC())==codes.end()){
            current.print();
            cout << " : UC inválida!" << endl;
            fail.push_back(current);
        }
        else if(find(turmas.begin(), turmas.end(), current.getClass2())==turmas.end()){
            current.print();
            cout << " : A turma não existe! " << endl;
            fail.push_back(current);
        }
        else{
            int max;
            cout << endl << "Insira o numero máximo de estudantes da turma: ";
            while (!(cin >> max) or max<0) {
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Insira o numero máximo de estudantes da turma: ";
            }
            auto turmaDestino = find(horario.begin(),horario.end(),UCTurma(current.getUC2(),current.getClass2()));
            int current_students = 0;
            for (Estudante e: estudantes){
                for (UCTurma t : e.getturmasEstudante()){
                    if (t==*turmaDestino) current_students++;
                }
            }
            if (current_students+1>max){
                current.print();
                cout << " : A turma " << current.getClass2() << " da UC " << current.getUC2() << " excederia o limite de " << max << " estudantes." << endl;
                fail.push_back(current);
            }
            else {
                vector<UCTurma> temp = find(estudantes.begin(), estudantes.end(),
                                            current.getStudent())->getturmasEstudante();
                auto itr = temp.begin();
                for (const UCTurma &turma: temp) {
                    if (turma.getUC() == current.getUC()) {
                        temp.erase(itr);
                        break;
                    }
                    itr++;
                }
                for (UCTurma turma: temp) {
                    for (const Aula &a: turma.getHorarioUCTurma()) {
                        for (const Aula &b: turmaDestino->getHorarioUCTurma()) {
                            if (!a.isPossible(b)) doable = false;
                        }
                    }
                }
                if (doable) {
                    find(estudantes.begin(), estudantes.end(), current.getStudent())->removerUC(current.getUC());
                    find(estudantes.begin(), estudantes.end(), current.getStudent())->adicionarTurma(*turmaDestino);
                    current.print();
                    cout << " : O estudante " << current.getStudent()
                         << " foi inserido na turma " << current.getClass2() << " da UC "
                         << current.getUC2() << " com sucesso!" << endl;
                    sucesso.push_back(current);
                } else {
                    current.print();
                    cout << " : O horário do estudante " << current.getStudent() << " é incompatível com o da turma "
                         << current.getClass2() << " da UC " << current.getUC2() << "." << endl;
                    fail.push_back(current);
                }
            }
        }
    }
    pedidos.pop();
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

void GestaoHorarios::output() const {
    ofstream file;
    file.open("../students_classes_new.csv",ofstream::out | ofstream::trunc);
    file << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    for(Estudante e : estudantes) {
        for (const UCTurma &t: e.getturmasEstudante()) {
            file << e.getCode() << ',' << e.getName() << ',' << t.getUC() << ',' << t.getClassCode() << '\n';
        }
    }
    file.close();
}

void GestaoHorarios::outputFails() const{
    ofstream file;
    file.open("../PedidoFails.csv",ofstream::out | ofstream::trunc);
    for (const Pedido& p: fail){
        if (p.getType()=="addClass") file << "*\tAdicionar aluno " << p.getStudent() << " à turma " << p.getClass2() << " da cadeira " << p.getUC2() << "." << endl;
        if (p.getType()=="removeClass") file << "*\tRemover aluno " << p.getStudent() << " da sua turma da cadeira " << p.getUC() << "." << endl;
        if (p.getType()=="addUC") file << "*\tAdicionar aluno " << p.getStudent() << " à cadeira " << p.getUC2() << "." << endl;
        if (p.getType()=="removeUC") file << "*\tRemover aluno " << p.getStudent() << " da cadeira " << p.getUC() << "." << endl;
        if (p.getType()=="changeClass") file << "*\tTrocar aluno " << p.getStudent() << " da sua turma da cadeira " << p.getUC() << " para a turma " << p.getClass2() << "." << endl;
    }
    file.close();
}

void GestaoHorarios::outputSucessos() const{
    ofstream file;
    file.open("../PedidoSucessos.csv",ofstream::out | ofstream::trunc);
    for (const Pedido& p: sucesso){
        if (p.getType()=="addClass") file << "*\tAdicionar aluno " << p.getStudent() << " à turma " << p.getClass2() << " da cadeira " << p.getUC2() << "." << endl;
        if (p.getType()=="removeClass") file << "*\tRemover aluno " << p.getStudent() << " da sua turma da cadeira " << p.getUC() << "." << endl;
        if (p.getType()=="addUC") file << "*\tAdicionar aluno " << p.getStudent() << " à cadeira " << p.getUC2() << "." << endl;
        if (p.getType()=="removeUC") file << "*\tRemover aluno " << p.getStudent() << " da cadeira " << p.getUC() << "." << endl;
        if (p.getType()=="changeClass") file << "*\tTrocar aluno " << p.getStudent() << " da sua turma da cadeira " << p.getUC() << " para a turma " << p.getClass2() << "." << endl;
    }
    file.close();
}