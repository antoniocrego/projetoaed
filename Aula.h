//
// Created by andre on 19-10-2022.
//

#ifndef AED_PROJECT_AULA_H
#define AED_PROJECT_AULA_H

#include <string>
using namespace std;
//! Uma Classe Aula
/**
 * @brief Class Aula para manipulação de aulas
 */

class Aula{

public:
    /**
     * Create uma aula com diversas características.
     * @brief Constructor.
     * @param uccode
     * @param classcode
     * @param dia
     * @param inicio
     * @param duracao
     * @param tipo
     */

    Aula(const string& uccode, const string& classcode, const string& dia, float inicio, float duracao, const string& tipo);

    /**
     * @brief Obtêm o dia em que a aula tem lugar
     * @return dia
     */
    string getDay() const;//! Complexidade O(1)
   /**
    * @brief Obtêm a hora de início da aula
    * @return A hora de ínício da aula
    */
    float getInicio() const;//! Complexidade O(1)
    /**
     * @brief Obtêm a hora de fim da aula
     * @return A hora de fim da aula
     */
    float getFim() const;//! Complexidade O(1)
    /**
     * @brief Devolve o tipo da aula
     * @return tipo
     */
    string getTipo() const;//! Complexidade O(1)
    /**
     * @brief Redefine o operador '<' a fim de comparar aulas
     * @param aula2
     * @return Verdadeiro se Aula 2 começar mais tarde, o contrário é falso
     */
    bool operator<(const Aula& aula2) const;//! Complexidade O(1)
    /**
     * @brief Imprime todas as caractéristicas da aula de forma sequencial
     * @return Verdadeiro se Aula 2 começar mais tarde, o contrário é falso
     */
    void print();//! Complexidade O(1)
    /**
     * @brief Verifica se é possivel a aula2 ser sobreposta à aula a ser comparada
     * @return Verdadeiro se for possível a sobreposição de aula2, o contrário é falso
     */
    bool isPossible(const Aula &Aula2) const;//! Complexidade O(1)
private:
    string uccode_;/*! Código da disciplina da aula */
    string classcode_;/*! Código da turma que corresponde a essa aula */
    string dia_;/*! Dia da semana em que ocorre a aula */
    float inicio_;/*! Hora a que tem lugar o início da aula*/
    float fim_;/*! Hora de término da aula*/
    float duracao_;/*! Duração da aula*/
    string tipo_;/*! Tipo da aula ( Pode ser Teórica, Prática Laboratorial, Prática) */
};


#endif //AED_PROJECT_AULA_H
