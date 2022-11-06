//
// Created by andre on 19-10-2022.
//
/**
 * @brief Class que exprime os métodos necessários para encontrar e gerir horários
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <limits>
#include "Estudante.h"
#include "Aula.h"
#include "Pedido.h"
#ifndef AED_PROJECT_GESTAOHORARIOS_H
#define AED_PROJECT_GESTAOHORARIOS_H


class GestaoHorarios {
public:
    /**
     * @brief Um construtor default que invoca todos os métodos do tipo Read quando chamado
     * Complexidade-O (6n²)
     */
    GestaoHorarios();
    /**
     * @brief A partir de um ficheiro escolhido( Classes.csv), armazena todas as aulas possíveis no curso de L.EIC, bem como organiza as suas caractísticas
     */
    void readAulas();//! Complexidade-O (2n²)
    /**
    * @brief A partir de um ficheiro escolhido( students_classes.csv), armazena todas os estudantes inscritos no curso de L.EIC,
    e armazena em cada estudante todas as turmas em que está inscrito
    */
    void readEstudantes();//! Complexidade-O (2n²)
    /**
     * Complexidade- O(n²)
    * @brief A partir de um ficheiro escolhido( students_classes.csv), armazena todas os códigos de todas as cadeiras existentes no curso de L.EIC
    */
    void readCodes();
    /**
     *  Complexidade- O(n²)
    * @brief A partir de um ficheiro escolhido( students_classes.csv), armazena todas os códigos de todas as turmas existentes no curso de L.EIC
    */
    void readTurmas();

    /**
    * @brief Adiciona um pedido x feito por um estudante
    * @param x
    */
    void addPedido(const Pedido& x);//! Complexidade- O(1)
    /**
    * @brief Processa sucessivamente todos os pedidos feitos até esta chamada, separando em vetores os pedidos que tiveram sucesso, e os que falharam
    * @param x
    */
    //! Complexidade- O(n²)
    void processarPedido();
    /**
     * @brief Replica uma listagem de todos os estudantes, com todas as suas turmas correspondentes
     */
    void output() const; //! Complexidade- O(1) /
    /**
     * @brief Escreve num ficheiro a descrição de cada pedido feito por estudantes que tenha falhado, identificado o estudante respetivo.
     */
    void outputFails()const; //! Complexidade- O(1) /
    /**
     * @brief Obtêm a lista de todos os estudantes inscritos no curso de L.EIC
     * @return estudantes
     */
    vector<Estudante> getEstudantes() const;//! Complexidade - O(1) /
    /**
     * @brief Obtêm a lista de todas as Turmas e cadeiras respetivas no curso
     * @return horario
     */
    vector<UCTurma> getUCTurmas() const;//! Complexidade - O(1) /
    /**
     * @brief Obtêm a lista dos códigos de todas as cadeiras do curso
     * @return codes
     */
    vector<string> getCodes() const;//! Complexidade - O(1)
    /**
    * @brief Obtêm a lista de todas as turmas existentes do curso de L.EIC
    * @return turmas
    */
    vector<string> getTurmas() const;//! Complexidade - O(1) /
    /**
    * @brief Obtêm a fila de todos os pedidos feitos por estudantes do curso de L.EIC
    * @return pedidos
    */
    queue<Pedido> getPedidos() const;//! Complexidade - O(1) /
    /**
    * @brief De todos os pedidos realizados por estudantes do curso de L.EIC, obtêm o conjunto de todos os qeu foram concedidos
    * @return sucesso
    */
    vector<Pedido> getSuccessos() const {return sucesso;};//! Complexidade - O(1) /
    /**
    * @brief De todos os pedidos realizados por estudantes do curso de L.EIC, obtêm o conjunto de todos os que falharam
    * @return fail
    */
    vector<Pedido> getFails() const {return fail;};//! Complexidade - O(1) /
    void outputSucessos() const;
private:
    vector<Estudante> estudantes;/*! Conjunto de estudantes */
    vector<UCTurma> horario;/*! Conjunto de disciplinas e turmas */
    vector<string> codes;/*! Conjuntos de códigos de cadeiras (uccodes) */
    vector<string> turmas;/*! Conjuntos de códigos de turmas (classcodes) */
    queue<Pedido> pedidos;/*! Conjuntos de pedidos feitos por estudantes */
    vector<Pedido> sucesso;/*! Conjuntos de pedidos feitos que tiveram sucesso */
    vector<Pedido> fail;/*! Conjuntos de pedidos feitos que falharam */
};


#endif //AED_PROJECT_GESTAOHORARIOS_H
