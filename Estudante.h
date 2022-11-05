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
    /**
    * Cria um estudante, definido pelo seu nome e código de estudante
    * @brief Constructor.
    *@param studentcode
    *@param name
    */
    Estudante(int studentcode, string name);//! Complexidade O(1)
    /**
     * @brief obtẽm o código do estudante
     * @return studentcode
     */
    int getCode() const;//! Complexidade O(1)
    /**
     * @brief obtẽm o nome do estudante
     * @return name
     */
    string getName() const;//! Complexidade O(1)
    /**
     * @brief devolve o conjunto de turmas e disciplinas respetivas (UCTURMAS) em que o estudante está inscrito
     * @return turmasEstudante
     */

    vector<UCTurma> getturmasEstudante();//! Complexidade O(1)
    /**
     * @brief imprime sequencialmente  o código e nome do estudante, bem como cada turma e disciplina correspondente a que o estudante está inscrito
    */
    void print() const;//! Complexidade O(1)
    /**
     * @brief define a igualdade de estudantes pela comparação entre os seus códigos de estudante
     * @param aluno
     * @return studentcode==aluno.getCode()
    */
    bool operator==(const Estudante &aluno) const;//! Complexidade O(1)
    /**
     * @brief recebe como parâmetro um inteiro, e compara este com o código de estudante do objeto
     * @param x
     * @return studentcode==x
     */
    bool operator==(int x) const;//! Complexidade O(1)
    /**
     * @brief relaciona os estudantes pela comparação entre os seus códigos de estudante ( códigos de estudante inferiores definem posições anteriores em vetores de estudante ordenados)
     * @param aluno
     * @return studentcode.getCode()==x
     */
    bool operator<(const Estudante& aluno) const;//! Complexidade O(1)
    /**
     * @brief recebe um código de uma disciplina e remova o estudante da turma correspondente a essa disciplina
     * @param uc
     *
     */
    void removerTurma(string uc);//! Complexidade O(n)
    /**
     * @brief recebe um código de uma disciplina e remova o estudante da disiciplina correspondente ao código recebido
     * @param uc
     */
    void removerUC(string uc);//! Complexidade O(n)
    /**
     * @brief adiciona um aluno a uma turma , e à sua disciplina correspondente.
     * @param turma
     */
    void adicionarTurma(const UCTurma &turma);//! Complexidade O(1)
private:
    int studentcode_; /*! Código de estudante do estudante */
    string name_; /*! Nome do estudante */
    vector<UCTurma> turmasEstudante;/*! Vetor que representa o conjunto de todos as turmas e disciplinas correspondentes nas quais o estudante está inscrito */

};


#endif //AED_PROJECT_ESTUDANTE_H
