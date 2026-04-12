#include <iostream>
#include "Farm.h"
#include "Utils.h"

void imprimirMapa(const unordered_map<int, pair<int, vector<int>>>& mapa) {
    cout << "--- CONTENIDO DEL MAPA ---" << endl;
    
    for (const auto& [clave, valor] : mapa) {
        cout << "Clave: [" << clave << "]" << endl;
        cout << "  - Valor entero: " << valor.first << endl;
        cout << "  - Lista de numeros: { ";
        
        const vector<int>& lista = valor.second;
        for (size_t i = 0; i < lista.size(); ++i) {
            cout << lista[i] << (i < lista.size() - 1 ? ", " : "");
        }
        
        cout << " }" << endl;
        cout << "--------------------------" << endl;
    }
}

void imprimiMatrix(const vector<vector<int>> matriz){
  int number = 0;
 for (int i = 0; i < matriz.size(); i++) {
        
        // Recorremos las columnas de la fila actual
        for (int j = 0; j < matriz[i].size(); j++) {
            number = matriz[i][j];
            if (number == INT_MAX){
              cout << "-" << "\t";
            }else{
              cout << number << "\t"; // \t para que las columnas queden alineadas
            }
            
        }
        
        cout << endl; 
    }
}

int main()
{

  //print_examples(); // Muestra la correctitud del codigo con los ejemplos del enunciado

  Farm farm = load("../input/input4.txt");

  

    cout << "\n--------Mejor solucion con programación dinamica----------\n" << endl;
  auto solution_and_time_dp = take_time([&]{ return farm.dynamic_programming_solution(); });

  auto [solution_dp, time_dp] = solution_and_time_dp; // desempaqueta la tupla externa
  auto [cost_dp, order_dp] = solution_dp;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order_dp);
  cout << "El costo es: " << cost_dp << endl;
  cout << "El tiempo fue: " << time_dp << " microsegundos" << endl;

  cout << "\n--------Mejor solucion con fuerza bruta----------\n" << endl;
  auto solution_and_time_brute = take_time([&]{ return farm.naive_solution(); });

  auto [solution_brute, time_brute] = solution_and_time_brute; // desempaqueta la tupla externa
  auto [cost_brute, order_brute] = solution_brute;             // desempaqueta la tupla interna

  cout << "La solucion es: ";
  print_vector(order_brute);
  cout << "El costo es: " << cost_brute << endl;
  cout << "El tiempo fue: " << time_brute << " microsegundos" << endl;

  return 0;
}