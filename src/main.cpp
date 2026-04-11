#include <iostream>
#include "Farm.h"
#include "Utils.h"

int main()
{

  print_examples(); // Muestra la correctitud del codigo con los ejemplos del enunciado

  Farm farm = load("../input/input2.txt");

  cout << "\n--------Mejor solucion con fuerza bruta----------\n"
       << endl;
  auto solution_and_time = take_time([&]
                                     { return farm.naive_solution(); });

  auto [solution, time] = solution_and_time; // desempaqueta la tupla externa
  auto [cost, order] = solution;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order);
  cout << "El costo es: " << cost << endl;
  cout << "El tiempo fue: " << time << " microsegundos" << endl;
  return 0;
}