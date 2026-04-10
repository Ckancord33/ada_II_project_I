#include "Farm.h"

Farm::Farm(vector<Plot> plots) : plots(plots) {}

//Calcula el tiempo en el que se inicia cada tablon
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
  for(int i = 0; i < schedule.size(); i++){
    total_cost += plots[i].calc_cost(schedule[i]);
  }
  return total_cost;
}

vector<int> Farm::delete_position(vector<int> original, int idx){
    if (idx >= 0 && idx < original.size()) {
        original.erase(original.begin() + idx);
    }
    return original;
}

vector<int> Farm::add_element(vector<int> original, int element){
    original.push_back(element);
    return original;
}

void Farm::generate(vector<int> remaining, vector<int> current, vector<vector<int>>& permutations){
  if(remaining.size() == 0){
    permutations.push_back(current);
    return;
  }

  for(int i = 0; i < remaining.size(); i ++){
    int next = remaining[i];
    generate(delete_position(remaining, i), add_element(current, next), permutations);
  }

}

vector<vector<int>> Farm::get_permutations(int n){
  vector<int> init(n, 0);
  for(int i = 0; i < n; i ++){
    init[i] = i;
  }
  vector<vector<int>> permutations;
  generate(init, {}, permutations);
  return permutations;
}

tuple<int, vector<int>> Farm::naive_solution(){
  int n = plots.size();
  vector<vector<int>> all_orders = get_permutations(n);
  vector<int> best_solution;
  int best_cost;
  for(vector<int> order : all_orders){
    int new_cost = calc_total_cost(order);
    if(new_cost < best_cost){
      best_cost = new_cost;
      best_solution = order;
    }
  }
  return tuple<int, vector<int>>(best_cost, best_solution);

}
