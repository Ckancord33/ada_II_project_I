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
  Farm(vector<Plot>);
  vector<int> calc_schedule(vector<int>);
  int calc_total_cost(vector<int>);
  vector<int> delete_position(vector<int>, int);
  vector<int> add_element(vector<int>, int);
  void generate(vector<int>, vector<int>, vector<vector<int>>&);
  vector<vector<int>> get_permutations(int);
  tuple<int, vector<int>> naive_solution();
  void fill_cost_matrix(vector<vector<int>>&, const unordered_map<int, pair<int, vector<int>>>& , int, vector<vector<int>>&) ;
  tuple<int, vector<int>> dynamic_programming_solution();
};