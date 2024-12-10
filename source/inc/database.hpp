#ifndef DATABASE
#define DATABASE

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../inc/bar_chart.hpp"

/**
 * @brief Classe que representa um banco de dados de gráficos de barras.
 *
 * A classe `database` armazena e gerencia os gráficos de barras, incluindo
 * seus dados, categorias e cabeçalhos. Ela fornece funcionalidades para
 * carregar dados de um arquivo e obter informações sobre os gráficos de barras.
 */
class database {

  std::vector<std::string> header;    /**< Cabeçalho do banco de dados. */
  std::vector<bar_chart> data_charts; /**< Vetor de gráficos de barras. */
  std::unordered_set<std::string> categories; /**< Conjunto de categorias. */
  std::unordered_map<std::string, std::string>
      category_colors; /**< Mapeamento de categorias para cores. */
  size_t data_c{0};    /**< Tamanho do bloco de dados a ser lido. */

public:
  /**
   * @brief Exibe um resumo dos dados carregados.
   *
   * @param animation_speed A velocidade da animação a ser usada.
   */
  void print_summary(int animation_speed);

  /**
   * @brief Carrega os dados de um arquivo.
   *
   * @param file_p O caminho do arquivo que contém os dados a serem carregados.
   */
  void load_data(std::string file_p);

  /**
   * @brief Obtém os dados dos gráficos de barras.
   *
   * @return Um vetor contendo os gráficos de barras.
   */
  std::vector<bar_chart> get_data();

  /**
   * @brief Obtém as categorias únicas dos gráficos de barras.
   *
   * @return Um conjunto contendo as categorias.
   */
  std::unordered_set<std::string> get_categories();

  /**
   * @brief Obtém o cabeçalho no índice especificado.
   *
   * @param index O índice do cabeçalho a ser recuperado.
   * @return A string do cabeçalho correspondente ao índice.
   */
  std::string get_headers(int index);
};

#endif
