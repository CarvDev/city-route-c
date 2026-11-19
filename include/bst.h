#ifndef BST_H
#define BST_H

#include "tipos.h"

/*
 * Insere recursivamente um novo PontoEntrega na BST, ordenado por id_ponto.
 * Se a chave já existir, a estrutura não é modificada e define *ok = 0.
 * Em caso de sucesso na inserção, define *ok = 1 e retorna a raiz atualizada.
 * Em caso de falha na alocação de memória, define *ok = 0; quando a falha
 * ocorre na posição de inserção (raiz == NULL) retorna NULL, e quando ocorre
 * em nível mais profundo os ancestrais mantêm suas subárvores intactas.
 * Valida com segurança se ok != NULL antes de desreferenciar.
 *
 * O(n) pior: BST pode ficar degenerada.
 */
NoBST *bst_inserir(NoBST *raiz, PontoEntrega ponto, int *ok);

/*
 * Realiza a busca recursiva de um ponto de entrega pelo seu id_ponto.
 * Explora as propriedades da BST (menores à esquerda, maiores à direita).
 * Retorna ponteiro constante para o nó correspondente ou NULL se não existir
 * (inclusive para o caso de árvore vazia).
 *
 * O(n) pior: busca recursiva por id_ponto.
 */
const NoBST *bst_buscar(const NoBST *raiz, int id_ponto);

/*
 * Percorre recursivamente a BST em-ordem (esq -> raiz -> dir) para imprimir
 * todos os pontos cadastrados em ordem crescente de id_ponto.
 * Formata os dados de forma legível (ID, Nome, Latitude, Longitude).
 * Não imprime mensagens extras caso a raiz seja nula (caso base silencioso).
 *
 * O(n): imprime todos os pontos em ordem crescente.
 */
void bst_listar_em_ordem(const NoBST *raiz);

/*
 * Remove recursivamente um PontoEntrega identificado por id_ponto.
 * Trata os 3 casos clássicos de remoção em BST:
 * 1. Nó folha (0 filhos): desaloca e retorna NULL.
 * 2. Nó com 1 filho: desaloca o nó e promove seu único filho para religação.
 * 3. Nó com 2 filhos: copia os dados do sucessor em-ordem (menor nó da subárvore
 *    direita) para o nó atual e remove recursivamente o sucessor na subárvore direita.
 * Define *ok = 1 em caso de remoção bem-sucedida e *ok = 0 se o ponto não for
 * encontrado ou se a árvore estiver vazia. Valida se ok != NULL.
 *
 * O(n) pior: remove folha, no com 1 ou 2 filhos.
 */
NoBST *bst_remover(NoBST *raiz, int id_ponto, int *ok);

/*
 * Desaloca recursivamente toda a memória ocupada pelos nós da árvore
 * utilizando percurso em pós-ordem (esq -> dir -> raiz).
 * Garante que os nós filhos sejam liberados antes de seus pais, prevenindo
 * use-after-free e vazamentos de memória. Totalmente segura quando raiz == NULL.
 *
 * O(n): libera todos os nos da arvore.
 */
void bst_liberar(NoBST *raiz);

#endif
