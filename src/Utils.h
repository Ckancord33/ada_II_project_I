#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include "Farm.h"
#include <unordered_map>

Farm load(string);

void print_vector(vector<int>);

void print_examples();

void print_map(const unordered_map<int, pair<int, vector<int>>>&);

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