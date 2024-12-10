#ifndef BAR_CHART_HPP
#define BAR_CHART_HPP

#include "./bar_item.hpp"
#include <algorithm>
#include <string>
#include <vector>

/**
 * @brief Estrutura que representa um gráfico de barras.
 *
 * A estrutura `bar_chart` contém um vetor de itens de barras (`bar_item`) e um
 * método para ordenar essas barras com base em seus valores numéricos.
 */
struct bar_chart {

  std::vector<bar_item> charts; /** Vetor de itens de barra que representam as
                                   barras do gráfico. */

  /**
   * @brief Ordena as barras do gráfico em ordem decrescente de valor.
   *
   * Este método ordena o vetor `charts` usando a função `std::sort`, comparando
   * os valores das barras convertidos de string para inteiro. As barras com
   * valores maiores vêm antes.
   *
   * Se a conversão de algum valor para inteiro falhar, o item será ignorado na
   * ordenação.
   */
  void sort_bars() {
    std::sort(
        charts.begin(), charts.end(), [](const bar_item &a, const bar_item &b) {
          try {
            int value_a =
                std::stoi(a.value); ///< Converte o valor de `a` para inteiro
            int value_b =
                std::stoi(b.value);   ///< Converte o valor de `b` para inteiro
            return value_a > value_b; ///< Ordena em ordem decrescente
          } catch (const std::exception &e) {
            return false; ///< Se falhar, não altera a ordem
          }
        });
  }
};

#endif
