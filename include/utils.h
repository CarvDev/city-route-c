#pragma once

#include <stddef.h>
#include <stdint.h>

/*
 * Verifica se a multiplicação de dados size_t resultará em overflow.
 * Retorna 1 caso sim, 0 caso não.
 */
static inline int overflow_mul_size(size_t a, size_t b) {
    if (b != 0 && a > (SIZE_MAX / b)) {
        return 1; // Vai ocorrer overflow
    }

    return 0;
}
