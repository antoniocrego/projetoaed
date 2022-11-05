//
// Created by andre on 19-10-2022.
//
/**
 * @brief Classe concebida para gerir uma UCTurma
 */
#ifndef AED_PROJECT_UCTURMA_H
#define AED_PROJECT_UCTURMA_H

#include <string>
#include <vector>
#include "Aula.h"

using namespace std;
class UCTurma {
public:
    /**
     * @brief constructor
     * @param uccode
     * @param classcode
     */
    UCTurma(const string& uccode, const string& classcode);
    /**
     * @brief Obtêm o código da cadeira da UCTurma
     * @return uccode
     */
    string getUC() const;
    /**
     * @brief Obtêm o código da turma da UCTurma
     * @return
     */
    string getClassCode() const;
    /**
     * @brief Imprime o código da uc e o código da uc que lhe é referente
     * */
    void print() const;
    /**
     * @brief Faz overload do operador '==' a fim de comparar a igualdade entre duas turmas
     * @param turma
     * @return Devolve True se se verificar a igualdade de uccode e classcode entre o objeto e o parametro turma
     * @return Devolve False se não se verificar ou a igualdade entre uccodes ou a igualdade entre classcodes
     */
    bool operator==(const UCTurma& turma);
    /**
     * @brief Adiciona uma aula a um horário uma UCTurma
     * @param aula
     */
    void adicionarAula( const Aula& aula);
    /**
     * @brief Obtêm o conjunto de aulas de uma Turma na sua UC
     * @return horário do objeto UCTurma
     */
    vector<Aula> getHorarioUCTurma();
private:
    vector<Aula> horarioUCTurma;/*! Conjunto de aulas de uma UCTurma*/
    string uccode_;/*! Código da cadeira a que a turma pertence*/
    string classcode_;/*! Código da turma que têm uma UC*/
};


#endif //AED_PROJECT_UCTURMA_H
