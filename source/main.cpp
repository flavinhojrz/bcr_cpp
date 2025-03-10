/** @file main.cpp
 *
 * @description
 * This program implements a bar char race animation.
 *
 * ===========================================================================
 * @license
 *
 * This file is part of BAR_CHART_RACE project.
 *
 * BAR_CHART_RACE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BAR_CHART_RACE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BARCHART RACE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2021-2024 Selan R. dos Santos.
 * ===========================================================================
 *
 * @author	Selan R dos Santos, <selan.santos@ufrn.br>
 * @date	2021
 *
 * @remark On 2021-09-19 changed ...
 */

#include <cstdlib> // EXIT_SUCCESS

#include "../inc/animation_manager.hpp"

int main(int argc, char **argv) {
  animation_manager animation;

  // Parse CLI options or .INI file.
  animation.initialize(argc, argv);

  // The Game Loop architecture or design pattern.
  while (not animation.is_end()) {
    animation.process();
    animation.update();
    animation.render();
  }

  return EXIT_SUCCESS;
}
