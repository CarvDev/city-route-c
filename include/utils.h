#pragma once

#include <stddef.h>
#include <stdint.h>

/*
 * Utilitários compartilhados entre módulos.
 * Algumas funções pequenas são definidas aqui como "static inline"
 * para permitir que o compilador elimine o custo de chamada. 
 * Funções static inline são implementadas direto no .h. Não é um erro.
*/

/*
 * Otimização para GCC/compiladores compatíveis:
 * Com __has_builtin, detecta suporte a __builtin_mul_overflow e habilita 
 * HAVE_BUILTIN_MUL_OVERFLOW para usar a detecção de overflow do compilador, 
 * que é mais eficiente. Caso contrário, usa a solução portável.
 */
#if defined(__has_builtin)
#  if __has_builtin(__builtin_mul_overflow)
#    define HAVE_BUILTIN_MUL_OVERFLOW 1
#  endif
#endif

/*
 * Função: mul_estoura_size.
 * Complexidade Temporal : O(1).
 * Retorna valor diferente de zero se a multiplicação a*b exceder SIZE_MAX;
 * caso contrário, retorna 0.
 */
static inline int mul_estoura_size(size_t a, size_t b) {
    #ifdef HAVE_BUILTIN_MUL_OVERFLOW // detecção do compilador (mais eficiente)
        size_t r; // variável descartável
        return (int)__builtin_mul_overflow(a, b, &r);
    #else // verificação portátil baseada em divisão.
        return b != 0 && a > (SIZE_MAX / b);
    #endif
}
