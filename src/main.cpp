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
  //instancia del enunciado
  vector<Plot> plots = {
      Plot(10, 3, 4, 0),
      Plot(6, 3, 3, 1),
      Plot(2, 2, 1, 0),
      Plot(8, 1, 1, 6),
      Plot(10, 4, 2, 5)};
  
  Farm farm = Farm(plots);

  //Ejemplos del enunciado
  vector<int> plots_order_I = {2, 1, 4, 3, 0};
  vector<int> plots_order_II = {0, 1, 4, 2, 3};

  cout << "-------------Ejemplo del enunciado-----------------\n" << endl;
  cout << "Para el orden: "; 
  print(plots_order_I);
  cout << "El costo es: " << farm.calc_total_cost(plots_order_I) << endl;

  cout << "\nPara el orden: "; 
  print(plots_order_II);
  cout << "El costo es: " << farm.calc_total_cost(plots_order_II) << endl;

  cout << "\n--------Mejor solucion con fuerza bruta----------\n" << endl;
  tuple<int, vector<int>> solution = farm.naive_solution();
    cout << "La solucion es: ";
  print(get<1>(solution));
  cout << "El costo es: " << get<0>(solution) << endl;
  return 0;
}