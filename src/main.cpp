#include <iostream>
#include "Farm.h"

void print(vector<int> x){
  cout << "{ ";
  for(int i : x){
    cout << i << " ";
  }
  cout << " }" << endl;
}

int main()
{
  vector<Plot> plots = {
      Plot(10, 3, 4, 0),
      Plot(6, 3, 3, 1),
      Plot(2, 2, 1, 0),
      Plot(8, 1, 1, 6),
      Plot(10, 4, 2, 5)};
  
  Farm farm = Farm(plots);

  vector<int> plots_order = {2, 1, 4, 3, 0};

  cout << "La programacion queda: "; 
  print(farm.calc_schedule(plots_order));
  cout << "El costo es: " << farm.calc_total_cost(plots_order) << endl;
  return 0;
}