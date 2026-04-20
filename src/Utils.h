#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include "Farm.h"

#include <iomanip> 

Farm load(string);

void print_vector(vector<int>);

void print_examples();

void print_matrix(const vector<vector<int>>);

template <typename F>
tuple<tuple<int, vector<int>>, long long> take_time(F function)
{
  auto start = chrono::high_resolution_clock::now();
  auto solution = function();
  auto end = chrono::high_resolution_clock::now();
  return tuple<tuple<int, vector<int>>, long long>(
      solution,
      chrono::duration_cast<chrono::microseconds>(end - start).count());
}

template <typename F>
void print_function_metrics(string title, F function)
{ 
  cout << "-----------------------------\n";
  cout << title << "\n" << endl;
  auto solution_and_time = take_time([&]
                                     { return function(); });

  auto [solution, time] = solution_and_time; // desempaqueta la tupla externa
  auto [cost, order] = solution;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order);
  cout << "El costo es: " << cost << endl;
  cout << "El tiempo fue: " << time << " microsegundos\n";
  cout << "-----------------------------\n";
}