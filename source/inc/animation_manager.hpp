#ifndef ANIMATION_MANAGER
#define ANIMATION_MANAGER

#include "./bar_chart.hpp"
#include "./bar_item.hpp"
#include "./database.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * @class animation_manager
 * @brief Gerencia o fluxo de animação e exibição de gráficos de barras com base
 * nos dados fornecidos.
 */
class animation_manager {
  /**
   * @enum animation_state
   * @brief Define os diferentes estados da animação.
   */
  enum class animation_state {
    START,   /**< Estado inicial antes de qualquer ação. */
    WELCOME, /**< Exibição da mensagem de boas-vindas. */
    READING, /**< Lendo o arquivo de entrada. */
    RACING,  /**< Exibição do gráfico animado. */
    END      /**< Finalização do programa. */
  };

  /**
   * @enum input
   * @brief Representa os tipos de entrada do usuário.
   */
  enum class input {
    ENTER, /**< Entrada do usuário confirmando uma ação (Enter). */
    UNDEF  /**< Entrada indefinida. */
  };

  animation_state a_curr_state{
      animation_state::START};      /**< Estado atual da animação. */
  input u_curr_input{input::UNDEF}; /**< Entrada atual do usuário. */
  int b_value = {5};                /**< Número de barras (padrão). */
  int f_value = {24};               /**< Frames da exibição (padrão). */
  database db;                 /**< Objeto que gerencia os dados carregados. */
  std::string input_data_file; /**< Caminho do arquivo de entrada dos dados. */

  /**
   * @brief Exibe mensagens de ajuda ao usuário.
   */
  void print_helper();

  /**
   * @brief Exibe uma mensagem de boas-vindas ao usuário.
   */
  void print_welcome();

  /**
   * @brief Lê os dados do arquivo especificado pelo usuário.
   */
  void read_input_file();

  /**
   * @brief Limpa a tela e posiciona o cursor no topo.
   */
  void clear_screen();

  /**
   * @brief Exibe o gráfico de barras na tela.
   */
  void display_bars();

  /**
   * @brief Exibe uma barra de progresso na parte inferior da tela.
   *
   * @param maxValue Valor máximo do gráfico.
   * @param maxBarLength Comprimento máximo da barra.
   * @param console_width Largura do console.
   */
  void display_low_bar(int maxValue, int maxBarLength, int console_width);

public:
  /**
   * @brief Inicializa o gerenciador de animação com os argumentos fornecidos na
   * linha de comando.
   *
   * @param argc Número de argumentos.
   * @param argv Vetor de argumentos.
   */
  void initialize(int argc, char **argv);

  /**
   * @brief Processa o estado atual da animação.
   */
  void process();

  /**
   * @brief Atualiza o estado da animação com base na entrada ou nos dados.
   */
  void update();

  /**
   * @brief Renderiza o conteúdo da animação na tela.
   */
  void render();

  /**
   * @brief Verifica se o estado atual é o de finalização.
   *
   * @return true Se o estado for END.
   * @return false Caso contrário.
   */
  bool is_end() { return a_curr_state == animation_state::END; }
};

#endif
