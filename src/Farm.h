#pragma once
#include "Plot.h"
#include <tuple>
#include <vector>
#include <climits>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cmath>

class Farm
{

private:
  vector<Plot> plots;

public:

  //Funciones del problema
  Farm(vector<Plot>);
  vector<int> calc_schedule(vector<int>);
  int calc_total_cost(vector<int>);

  //Funciones para la solucion ingenua
  vector<int> delete_position(vector<int>, int);
  vector<int> add_element(vector<int>, int);
  void generate(vector<int>, vector<int>, vector<vector<int>> &);
  vector<vector<int>> get_permutations(int);
  tuple<int, vector<int>> naive_solution();

  //Funciones para la solucion dinamica

  //Acercamiento Top - Down
  int calc_total_subset_time(int);
  int auxiliar_top_down(int, vector<int> &);
  void build_solution_top_down(int, vector<int>&, vector<int>&);
  tuple<int, vector<int>> dynamic_solution_top_down();

  //Acercamiento Bottom - Up
  void fill_cost_matrix(vector<vector<int>> &, const unordered_map<int, pair<int, vector<int>>> &, int, vector<vector<int>> &);
  tuple<int, vector<int>> dynamic_solution_bottom_up();
};