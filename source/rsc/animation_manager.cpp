#include "../inc/animation_manager.hpp"
#include "../libs/text_color.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>
#include <vector>

const std::string HELP_FILE_PATH = "./helper.txt";

std::unordered_map<std::string, short>
generate_color_map(std::unordered_set<std::string> categories) {
  std::vector<short> colors = {
      Color::RED,         Color::GREEN,          Color::YELLOW,
      Color::BLUE,        Color::MAGENTA,        Color::CYAN,
      Color::BRIGHT_RED,  Color::BRIGHT_GREEN,   Color::BRIGHT_YELLOW,
      Color::BRIGHT_BLUE, Color::BRIGHT_MAGENTA, Color::BRIGHT_CYAN,
      Color::WHITE,       Color::BRIGHT_WHITE};

  std::unordered_map<std::string, short> color_map;
  size_t color_index = 0;

  for (const auto &category : categories) {
    if (color_index >= colors.size()) {
      color_index = 0;
    }
    color_map[category] = colors[color_index++];
  }

  return color_map;
}

// Helper file
void animation_manager::print_helper() {
  std::ifstream helper_file(HELP_FILE_PATH);
  std::string line;
  while (std::getline(helper_file, line)) {
    std::cout << line << "\n";
  }
  helper_file.close();
}

// Welcome
void animation_manager::print_welcome() {
  std::cout << "\n==============================================\n";
  std::cout << "Welcome to the Bar Chart Race, v1.0\n";
  std::cout << "Copyright (C) 2020, Selan R. dos Santos\n";
  std::cout << "==============================================\n";
  std::cout << "\n";
}

// Get Args
void animation_manager::initialize(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-b" && i + 1 < argc) {
      try {
        b_value = std::stoi(argv[++i]);
        if (b_value < 1 || b_value > 15)
          throw std::out_of_range("Invalid value");
      } catch (...) {
        print_helper();
        std::exit(EXIT_FAILURE);
      }
    } else if (arg == "-f" && i + 1 < argc) {
      try {
        f_value = std::stoi(argv[++i]);
        if (f_value < 1 || f_value > 24)
          throw std::out_of_range("Invalid value");
      } catch (...) {
        print_helper();
        std::exit(EXIT_FAILURE);
      }
    } else if (i == argc - 1) {
      input_data_file = argv[i];
    } else {
      print_helper();
      std::exit(EXIT_FAILURE);
    }
  }

  if (input_data_file.empty()) {
    print_helper();
    std::exit(EXIT_FAILURE);
  }
}

// Read data
void animation_manager::read_input_file() {
  try {
    db.load_data(input_data_file);
    std::cout << ">>> Input file successfully read.\n";
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    std::exit(EXIT_FAILURE);
  }
}

void animation_manager::clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Pegar o tamanho da tela
int get_console_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

void animation_manager::display_low_bar(int maxValue, int maxBarLength,
                                        int console_width) {
  const int scale_steps = 5;
  int scale_interval = maxValue / scale_steps;
  int segment_length = maxBarLength / scale_steps;

  // Linha superior
  std::cout << std::string(0, ' ');
  for (int i = 0; i <= scale_steps; ++i) {
    if (i == scale_steps) {
      std::cout << ">";
    } else {
      std::cout << "+";
      std::cout << std::string(segment_length - 1, '-');
    }
  }
  std::cout << "\n";

  // Linha inferior
  std::cout << std::string(0, ' ');
  for (int i = 0; i <= scale_steps; ++i) {
    int scale_value = i * scale_interval;
    if (i == scale_steps) {
      scale_value = maxValue + 100;
    }
    std::string scale_text = std::to_string(scale_value);
    std::cout << Color::tcolor(scale_text, Color::YELLOW);
    std::cout << std::string(segment_length - scale_text.length(), ' ');
  }
  std::cout << "\n";
}

void animation_manager::display_bars() {
  clear_screen();
  int console_width = get_console_width();

  std::vector<bar_chart> data_charts = db.get_data();
  if (data_charts.empty()) {
    std::cerr << "No data available to display.\n";
    return;
  }

  static auto category_color_map = generate_color_map(db.get_categories());
  static size_t current_frame = 0;
  if (current_frame >= data_charts.size()) {
    current_frame = data_charts.size() - 1;
  }

  bar_chart &current_chart = data_charts[current_frame];
  current_chart.sort_bars();

  std::string time_stamp =
      "Time Stamp: " + (current_chart.charts.empty()
                            ? "N/A"
                            : current_chart.charts[0].time_stemp);

  auto center_text = [&](const std::string &text) {
    int padding = (console_width - text.size()) / 2;
    return std::string(std::max(0, padding), ' ') + text;
  };

  std::cout << Color::tcolor(center_text(db.get_headers(0)), Color::BLUE)
            << "\n";
  std::cout << Color::tcolor(center_text(time_stamp), Color::BLUE) << "\n\n";

  if (current_chart.charts.empty()) {
    return;
  }

  const int maxBarLength = 100;
  int maxValue = 0;

  for (auto &barItem : current_chart.charts) {
    int value = 0;
    try {
      value = std::stoi(barItem.value);
    } catch (std::exception &e) {
      continue;
    }
    maxValue = std::max(maxValue, value);
  }
  if (maxValue == 0)
    maxValue = 1;

  int MAX_BARS = 15;
  size_t bars_to_display =
      std::min({static_cast<size_t>(b_value), current_chart.charts.size(),
                static_cast<size_t>(MAX_BARS)});

  for (size_t i = 0; i < bars_to_display; ++i) {
    const auto &barItem = current_chart.charts[i];
    int value = std::stoi(barItem.value);
    int barLength = (value * maxBarLength) / maxValue;

    short color = category_color_map[barItem.category];

    for (int j = 0; j < barLength; ++j) {
      std::cout << Color::tcolor("█", color);
    }

    std::cout << " " << std::setw(6) << std::left
              << Color::tcolor(barItem.label, color, Color::BOLD) << " ["
              << std::setw(2) << value << "]\n\n";
  }
  std::cout << "\n";
  display_low_bar(maxValue, maxBarLength, console_width);

  std::cout << Color::tcolor((db.get_headers(1)), Color::YELLOW) << "\n\n";
  std::cout << Color::tcolor((db.get_headers(2)), Color::WHITE) << "\n";
  for (const auto &category : db.get_categories()) {
    short color = category_color_map[category];
    std::cout << Color::tcolor("█", color) << ": "
              << Color::tcolor(category, color) << " ";
  }
  std::cout << "\n";

  if (current_frame < data_charts.size() - 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / f_value));
    current_frame++;
  }
}

void animation_manager::process() {
  if (a_curr_state == animation_state::READING) {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
      u_curr_input = input::ENTER;
    }
  }
}

void animation_manager::update() {
  static size_t current_frame = 0; // Índice do frame atual
  if (a_curr_state == animation_state::START) {
    a_curr_state = animation_state::WELCOME;
  } else if (a_curr_state == animation_state::WELCOME) {
    read_input_file();
    a_curr_state = animation_state::READING;
  } else if (a_curr_state == animation_state::READING) {
    if (u_curr_input == input::ENTER) {
      a_curr_state = animation_state::RACING;
    }
  } else if (a_curr_state == animation_state::RACING) {
    const auto &data_charts = db.get_data();
    if (current_frame >= data_charts.size()) {
      a_curr_state = animation_state::END;
    } else {
      current_frame++;
    }
  }
}

// Renderize animations
void animation_manager::render() {
  if (a_curr_state == animation_state::WELCOME) {
    print_welcome();
  } else if (a_curr_state == animation_state::READING) {
    db.print_summary(f_value);
  } else if (a_curr_state == animation_state::RACING) {
    display_bars();
  } else if (a_curr_state == animation_state::END) {
    std::cout << "Hope you enjoyed the Bar Chart Race!\n";
  }
}
