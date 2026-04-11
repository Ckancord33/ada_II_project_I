#include <iostream>
#include "Farm.h"
#include "Utils.h"

int main()
{

  print_examples(); // Muestra la correctitud del codigo con los ejemplos del enunciado

  Farm farm = load("../input/input3.txt");

  cout << "\n--------Mejor solucion con fuerza bruta----------\n" << endl;
  auto solution_and_time = take_time([&]{ return farm.naive_solution(); });

  auto [solution, time] = solution_and_time; // desempaqueta la tupla externa
  auto [cost, order] = solution;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order);
  cout << "El costo es: " << cost << endl;
  cout << "El tiempo fue: " << time << " microsegundos" << endl;

  cout << "\n--------Costo solucion dinamica----------\n" << endl;
  auto solution_and_time_dymamic = take_time([&]{ return farm.naive_solution(); });
  auto [solution_dynamic, time_dynamic] = solution_and_time_dymamic;
  auto [cost_dynamic, order_dynamic] = solution_dynamic;             // desempaqueta la tupla interna
  cout << "El costo es: " << cost_dynamic << endl;
  cout << "El tiempo fue: " << time_dynamic<< " microsegundos" << endl;

  return 0;
}