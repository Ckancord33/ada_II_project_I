#include "Farm.h"

int inf = INT_MAX;

Farm::Farm(vector<Plot> plots) : plots(plots) {}

// Calcula el tiempo en el que se inicia cada tablon
vector<int> Farm::calc_schedule(vector<int> plots_order)
{
  int n = plots_order.size();
  vector<int> schedule(n, 0);
  int time = 0;
  for (int i = 0; i < n; i++)
  {
    int idx = plots_order[i];
    schedule[idx] = time;
    time += plots[idx].get_tr();
  }
  return schedule;
}

int Farm::calc_total_cost(vector<int> plots_order)
{
  vector<int> schedule = calc_schedule(plots_order);
  int total_cost = 0;
  for (int i = 0; i < schedule.size(); i++)
  {
    total_cost += plots[i].calc_cost(schedule[i]);
  }
  return total_cost;
}

vector<int> Farm::delete_position(vector<int> original, int idx)
{
  if (idx >= 0 && idx < original.size())
  {
    original.erase(original.begin() + idx);
  }
  return original;
}

vector<int> Farm::add_element(vector<int> original, int element)
{
  original.push_back(element);
  return original;
}

void Farm::generate(vector<int> remaining, vector<int> current, vector<int>& best_solution, int& best_cost)
{
  if (remaining.size() == 0)
  {
    int new_cost = calc_total_cost(current);
    if(new_cost < best_cost){
      best_cost = new_cost;
      best_solution = current;
    }
    return;
  }

  for (int i = 0; i < remaining.size(); i++)
  {
    int next = remaining[i];
    generate(delete_position(remaining, i), add_element(current, next), best_solution, best_cost);
  }
}

tuple<int, vector<int>> Farm::naive_solution()
{
  int n = plots.size();
  vector<int> init(n, 0);
  for (int i = 0; i < n; i++)
  {
    init[i] = i;
  }
  vector<int> best_solution;
  int best_cost = INT_MAX;
  generate(init, {}, best_solution, best_cost);
  return tuple<int, vector<int>>(best_cost, best_solution);
}

int Farm::calc_total_subset_time(int bitmask)
{
  int total_time = 0;
  for (int sub = bitmask; sub; sub &= (sub - 1))
  {
    int i = __builtin_ctz(sub);
    total_time += plots[i].get_tr();
  }
  return total_time;
}

int Farm::auxiliar_top_down(int bitmask, vector<int> &memo, int time)
{
  if (memo[bitmask] != -1)
    return memo[bitmask];
  int min_cost = INT_MAX;
  for (int sub = bitmask; sub > 0; sub &= (sub - 1))
  {
    int i = __builtin_ctz(sub);
    int new_bitmask = bitmask & ~(1 << i);
    int new_time = time - plots[i].get_tr();
    int cost = auxiliar_top_down(new_bitmask, memo, new_time) + plots[i].calc_cost(new_time);
    min_cost = min(min_cost, cost);
  }
  memo[bitmask] = min_cost;
  return memo[bitmask];
}

void Farm::build_solution_top_down(int bitmask, vector<int> &memo, vector<int> &solution, int time)
{
  if (bitmask == 0)
  {
    return;
  }
  int idx = -1;
  int min_cost = INT_MAX;
  int best_bitmask = -1;
  int best_time = time;
  for (int sub = bitmask; sub > 0; sub &= (sub - 1))
  {
    int i = __builtin_ctz(sub);
    int new_bitmask = bitmask & ~(1 << i);
    int new_time = time - plots[i].get_tr();
    int cost = memo[new_bitmask] + plots[i].calc_cost(new_time);
    if (cost < min_cost)
    {
      min_cost = cost;
      idx = i;
      best_bitmask = new_bitmask;
      best_time = new_time;
    }
  }
  solution.insert(solution.begin(), idx);
  build_solution_top_down(best_bitmask, memo, solution, best_time);
}

tuple<int, vector<int>> Farm::dynamic_solution_top_down()
{
  int n = plots.size();
  vector<int> memo(1 << plots.size(), -1);
  memo[0] = 0;
  for (int i = 0; i < plots.size(); i++)
  {
    memo[1 << i] = plots[i].calc_cost(0);
  }
  int init_bitmask = (1 << plots.size()) - 1;
  int total_time = calc_total_subset_time(init_bitmask);
  int best_cost = auxiliar_top_down(init_bitmask, memo, total_time);
  vector<int> solution;
  build_solution_top_down(init_bitmask, memo, solution, total_time);
  return tuple<int, vector<int>>(best_cost, solution);
}


void Farm::fill_cost_matrix(vector<int>& cost_vector, int row, vector<int>& path)
{

  vector<int> temp_total_matrix(row);
  bool firstTime = true;
  int pos = 0, temp = 0, current_cost = 0;

  for(int i = 1; i < row; i++){

      firstTime = true;
      for(int sub = i; sub ; sub &= (sub - 1)){
        pos = __builtin_ctz(sub);
        temp = i & ~(1 << pos);
        
        
        if (firstTime){
          temp_total_matrix[i] = temp_total_matrix[temp] + plots[pos].get_tr();
          firstTime = false;
        }

        current_cost = cost_vector[temp] + plots[pos].calc_cost(temp_total_matrix[temp]);

        if (current_cost < cost_vector[i]){
            cost_vector[i] = current_cost;
            path[i] = pos;
        }

    }

  }
}


vector<int> build_solution_bottom_up(vector<int> path, int row)
{

  int last_opc = row - 1, last_plot = 0;
  vector<int> solution;

  while (last_opc > 0){
    last_plot = path[last_opc];
    solution.insert(solution.begin(),last_plot);
    last_opc &= ~(1 << last_plot);
  }

  return solution;
}

tuple<int, vector<int>> Farm::dynamic_solution_bottom_up()
{

  int n = plots.size();
  int row = 1 << n;

  vector<int> cost_vector(row,inf);
  cost_vector[0] = 0;

  vector<int> path(row,-1);

  fill_cost_matrix(cost_vector,row,path);

  vector<int> solution = build_solution_bottom_up(path, row);

  int minCost = cost_vector[row-1];

  return tuple<int, vector<int>>(minCost, solution);
}

double Farm::calc_greedy_score(int idx, int current_time)
{
  int ts = plots[idx].get_ts();
  int tr = plots[idx].get_tr();
  int p = plots[idx].get_p();
  int rp = plots[idx].get_rp();

  int slack = ts - (current_time + tr);

  if (slack <= 0)
  {
    return 1000000 + (static_cast<double>(p) * abs(slack));
  }

  double bonus = (current_time == rp) ? 10.0 : 1.0;
  return (static_cast<double>(p) * bonus) / static_cast<double>(slack);
}

tuple<int, vector<int>> Farm::greedy_solution()
{
  int n = plots.size();
  vector<int> remaining(n);
  for (int i = 0; i < n; i++)
  {
    remaining[i] = i;
  }

  vector<int> solution;
  solution.reserve(n);

  int current_time = 0;

  while (!remaining.empty())
  {
    int best_pos = 0;
    double best_score = calc_greedy_score(remaining[0], current_time);

    for (int i = 1; i < remaining.size(); i++)
    {
      int candidate = remaining[i];
      double candidate_score = calc_greedy_score(candidate, current_time);

      if (candidate_score > best_score)
      {
        best_score = candidate_score;
        best_pos = i;
      }
    }

    int chosen_plot = remaining[best_pos];
    solution.push_back(chosen_plot);
    current_time += plots[chosen_plot].get_tr();
    remaining.erase(remaining.begin() + best_pos);
  }

  int total_cost = calc_total_cost(solution);
  return tuple<int, vector<int>>(total_cost, solution);
}
