#include <iostream>
#include "Farm.h"
#include "Utils.h"

template <typename F>
void print_function_metrics(string title, F function)
{
  cout << title << "\n" << endl;
  auto solution_and_time = take_time([&]
                                     { return function(); });

  auto [solution, time] = solution_and_time; // desempaqueta la tupla externa
  auto [cost, order] = solution;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order);
  cout << "El costo es: " << cost << endl;
  cout << "El tiempo fue: " << time << " microsegundos\n" << endl;
}

int main()
{

  // print_examples(); // Muestra la correctitud del codigo con los ejemplos del enunciado

  Farm farm = load("../input/input4.txt");

  string title_dynamic_top_down = "------- solucion dinamica Bottom-Up -----------------";
  print_function_metrics(title_dynamic_top_down, [&]
                         { return farm.dynamic_solution_bottom_up(); });

  string title_dynamic_bottom_up = "------- solucion dinamica Top-Down -----------------";
  print_function_metrics(title_dynamic_bottom_up, [&]
                         { return farm.dynamic_solution_top_down(); });

  string title_naive = "------- solucion con fuerza bruta -----------------";
  print_function_metrics(title_naive, [&]
                         { return farm.naive_solution(); });

  return 0;
}