#include <iostream>
#include "Farm.h"
#include "Utils.h"
#include "TerminalUI.h"

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    cerr << "Uso: main.exe <ruta_txt> [opcion]" << endl;
    run_terminal_ui(); 
    return 0;
  }

  string path = argv[1];
  string opcion = (argc > 2) ? argv[2] : "";

  try
  {
    Farm myFarm = load(path);
    if (opcion == "naive solution")
    {
      print_function_metrics("Resultados de la solución ingenua", [&]()
                             { return myFarm.naive_solution(); });
    }
    else if (opcion == "dynamic solution (bottom up)")
    {
      print_function_metrics("Resultados de la solución con programación dinamica \n(Bottom Up)", [&]()
                             { return myFarm.dynamic_solution_bottom_up(); });
    }
    else if (opcion == "dynamic solution (top down)")
    {
      print_function_metrics("Resultados de la solución con programación dinamica \n(Top Down)", [&]()
                             { return myFarm.dynamic_solution_top_down(); });
    }
    else if (opcion == "greedy solution")
    {
      cout << "Impelementacion proximantente" << endl;
    }
    else
    {
      cout << "Eliga un algoritmo correcto" << endl;
    }
  }
  catch (const exception &e)
  {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }
  return 0;
}