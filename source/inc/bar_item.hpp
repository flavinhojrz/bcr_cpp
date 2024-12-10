#ifndef BAR_ITEM_HPP
#define BAR_ITEM_HPP

#include <string>
#include <unordered_map>

/**
 * @brief Estrutura que representa um item de barra em um gráfico.
 *
 * A estrutura `bar_item` armazena informações sobre uma barra, incluindo o
 * rótulo, o valor, a categoria e o timestamp associado à barra.
 */
struct bar_item {
  std::string time_stemp; /**< Carimbo de data/hora da barra. */
  std::string label;      /**< Nome ou descrição da barra. */
  std::string value;      /**< Valor númerico da barra. */
  std::string category;   /**< Categória associada a barra. */
};

#endif
