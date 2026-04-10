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
