#include <iostream>
#include "Farm.h"
#include "Utils.h"
#include "TerminalUI.h"

int main()
{

  // print_examples(); // Muestra la correctitud del codigo con los ejemplos del enunciado

  run_terminal_ui(); // Corre el loop de la interfaz

  Farm farm = load("../input/input1.txt");

  string title_dynamic_top_down = "------- solucion dinamica Bottom-Up -----------------";
  print_function_metrics(title_dynamic_top_down, [&]{ return farm.dynamic_solution_bottom_up(); });

  string title_dynamic_bottom_up = "------- solucion dinamica Top-Down -----------------";
  print_function_metrics(title_dynamic_bottom_up, [&]{ return farm.dynamic_solution_top_down(); });

  string title_naive = "------- solucion con fuerza bruta -----------------";
  //print_function_metrics(title_naive, [&]{ return farm.naive_solution(); });

  return 0;
}