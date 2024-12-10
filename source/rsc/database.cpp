#include "../inc/database.hpp"
#include "../inc/bar_chart.hpp"
#include "../libs/text_color.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define GREEN "\033[32m"
#define RESET "\033[0m"
namespace fs = std::filesystem;

std::vector<std::string> split(const std::string &text, char sep) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;

  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }

  tokens.push_back(text.substr(start));
  return tokens;
}

// Carregar os dados do arquivo
void database::load_data(std::string file_path) {
  // Verifica se o arquivo existe
  if (!fs::exists(file_path)) {
    throw std::runtime_error("Error: File does not exist in path: " +
                             file_path);
  }

  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Error: Could not open file: " + file_path);
  }

  // Carrega o cabeçalho
  std::string line;
  for (int i = 0; i < 3 && std::getline(file, line); i++) {
    if (line.empty() ||
        line.find_first_not_of(" \t\n\r") == std::string::npos) {
      throw std::runtime_error(
          "Error: Header line is empty or invalid at line " +
          std::to_string(i + 1));
    }
    header.push_back(line);
  }

  // Carrega os dados
  while (std::getline(file >> std::ws, line)) {
    if (line.empty())
      continue; // Ignora linhas vazias

    try {
      int block_count = std::stoi(line);
      if (block_count <= 0) {
        throw std::runtime_error("Error: Invalid block count: " + line);
      }
      data_c = block_count;

      bar_chart b_chart;
      b_chart.charts.reserve(std::min(static_cast<size_t>(block_count),
                                      b_chart.charts.max_size()));

      for (int i = 0; i < block_count; i++) {
        if (std::getline(file >> std::ws, line)) {
          if (line.empty())
            continue; // Ignora linhas vazias

          std::vector<std::string> tokens = split(line, ',');
          bar_item item;
          item.time_stemp = tokens[0];
          item.label = tokens[1];
          item.value = tokens[3];
          item.category = tokens[4];

          b_chart.charts.push_back(item);
          categories.insert(item.category);
        }
      }
      data_charts.push_back(std::move(b_chart));
    } catch (...) {
      throw std::runtime_error("Error while parsing data");
    }
  }

  file.close();
}

std::string database::get_headers(int index) { return header[index]; }

std::vector<bar_chart> database::get_data() { return data_charts; }
std::unordered_set<std::string> database::get_categories() {
  return categories;
}

// Summary
void database::print_summary(int animation_speed) {
  std::cout << "\n";
  std::cout << GREEN << ">>> We have \"" << data_charts.size()
            << "\" charts, each with \"" << data_c << "\" bars.\n\n";

  std::cout << ">>> Animation speed is: " << animation_speed << ".\n";
  std::cout << ">>> Title: " << header[0] << "\n";
  std::cout << ">>> Value is: " << header[1] << "\n";
  std::cout << ">>> Source: " << header[2] << "\n";
  std::cout << ">>> # of categories found: " << categories.size() << "\n";
  std::cout << ">>> Press enter to begin the animation.\n" << RESET;
  std::cout << "\n";
  for (auto &cat : categories) {
    std::cout << "- " << cat << " ";
  }
}
