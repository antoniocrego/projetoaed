//
// Created by andre on 19-10-2022.
//

#ifndef AED_PROJECT_AULA_H
#define AED_PROJECT_AULA_H

#include <string>
using namespace std;

class Aula{

public:
    Aula(string uccode, string classcode, string dia, float inicio, float duracao, string tipo);
    string getDay() const;
    float getInicio() const;
    float getFim() const;
    bool operator<(const Aula& aula2) const;
    void print();

private:
    string uccode_;
    string classcode_;
    string dia_;
    float inicio_;
    float fim_;
    float duracao_;
    string tipo_;
};


#endif //AED_PROJECT_AULA_H
