//
// Created by andre on 02-11-2022.
//

#ifndef AED_PROJECT_PEDIDO_H
#define AED_PROJECT_PEDIDO_H
#include <string>
#include <iostream>
using namespace std;
/**
 * @brief Class Pedido para manipulação de pedidos
 */

class Pedido {
public:
    /**
     * Create um pedido com diversas características.
     * @brief Constructor.
     * @param studentcode
     * @param uccode
     * @param classcode
     * @param uccode2
     * @param classcode2
     * @param type
     */
    Pedido(int studentcode, string uccode, string classcode, string uccode2, string classcode2, string type); //! Complexidade - O(1)
    /**
     * @brief Devolve o codigo do estudante que faz o pedido
     * @return Codigo do estudante
     */

    int getStudent() const {return studentcode_;}; //! Complexidade - O(1)
    /**
     * @brief Devolve o codigo da UC
     * @return Codigo da UC
     */
    string getUC() const {return uccode_;}; //! Complexidade - O(1)
    /**
     * @brief Devolve o codigo da turma do estudante
     * @return Codigo da turma
     */
    string getClass() const {return classcode_;}; //! Complexidade - O(1)
    /**
     * @brief Devolve o codigo da UC
     * @return Codigo da UC
     */
    string getUC2() const {return uccode2_;}; //! Complexidade - O(1)
    /**
     * @brief Devolve o codigo da turma para a qual o estudante pretende ir
     * @return Codigo da turma
     */
    string getClass2() const {return classcode2_;}; //! Complexidade - O(1)
    /**
     * @brief Devolve o tipo de pedido
     * @return Tipo de pedido
     */
    string getType() const {return type_;}; //! Complexidade - O(1)
    /**
     * @brief Imprimir informação sobre o pedido dependendo do tipo de pedido
     */
    void print() const; //! Complexidade - O(1)

private:
    int studentcode_; /*! Código do estudante */
    string uccode_; /*! Código da UC */
    string classcode_; /*! Código da turma do estudante */
    string uccode2_; /*! Código da UC */
    string classcode2_; /*! Código da turma pretendida pelo estudante */
    string type_; /*! Tipo de pedido */
};


#endif //AED_PROJECT_PEDIDO_H