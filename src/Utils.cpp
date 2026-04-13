#include "Utils.h"

Plot parsePlot(const string &line)
{
  stringstream ss(line);
  int ts, tr, p, rp;
  if (!(ss >> ts >> tr >> p >> rp))
  {
    throw runtime_error("Invalid plot line: '" + line + "'");
  }
  string extra;
  if (ss >> extra)
  {
    throw runtime_error("Extra tokens in plot line: '" + line + "'");
  }
  return Plot(ts, tr, p, rp);
}

Farm load(string path)
{
  ifstream file(path);
  if (!file.is_open())
  {
    throw runtime_error("El archivo no se pudo abrir: " + path);
  }

  string line;
  if (!getline(file, line))
  {
    throw runtime_error("Archivo vacío: " + path);
  }

  int n;
  try
  {
    n = stoi(line);
  }
  catch (const exception &e)
  {
    throw runtime_error("Invalid number of plots in first line: '" + line + "'");
  }

  vector<Plot> plots;
  plots.reserve(n);
  for (int i = 0; i < n; ++i)
  {
    if (!getline(file, line))
    {
      throw runtime_error("Unexpected end of file while reading plots (expected " + to_string(n) + ")");
    }
    plots.push_back(parsePlot(line));
  }

  return Farm(plots);
}

void print_vector(vector<int> x)
{
  cout << "{ ";
  for (int i : x)
  {
    cout << i << " ";
  }
  cout << " }" << endl;
}

void print_examples()
{
  vector<Plot> farm1_plots = {
      Plot(10, 3, 4, 0),
      Plot(6, 3, 3, 1),
      Plot(2, 2, 1, 0),
      Plot(8, 1, 1, 6),
      Plot(10, 4, 2, 5)};
  Farm farm1 = Farm(farm1_plots);

  vector<Plot> farm2_plots = {
      Plot(9, 3, 4, 0),
      Plot(5, 3, 3, 2),
      Plot(2, 2, 1, 0),
      Plot(8, 1, 1, 6),
      Plot(6, 4, 2, 1)};
  Farm farm2 = Farm(farm2_plots);

  vector<int> f1_plots_order_I = {2, 1, 4, 3, 0};
  vector<int> f1_plots_order_II = {0, 1, 4, 2, 3};

  cout << "-------------Ejemplo del enunciado 1-----------------\n" << endl;
  cout << "Para la finca: ≪ 10, 3, 4, 0 >, < 6, 3, 3, 1 >, < 2, 2, 1, 0 >, < 8, 1, 1, 6 >, < 10, 4, 2, 5 ≫" << endl;
  cout << "Usando el orden: ";
  print_vector(f1_plots_order_I);
  cout << "El costo es: " << farm1.calc_total_cost(f1_plots_order_I) << endl;

  cout << "\nPara el orden: ";
  print_vector(f1_plots_order_II);
  cout << "El costo es: " << farm1.calc_total_cost(f1_plots_order_II) << endl;

  vector<int> f2_plots_order_I = {2, 1, 4, 3, 0};
  vector<int> f2_plots_order_II = {2, 1, 4, 0, 3};

  cout << "-------------Ejemplo del enunciado 2-----------------\n" << endl;
  cout << "Para la finca: ≪ 9, 3, 4, 0 >, < 5, 3, 3, 2 >, < 2, 2, 1, 0 >, < 8, 1, 1, 6 >, < 6, 4, 2, 1 ≫" << endl;
  cout << "Usando el orden: ";
  print_vector(f2_plots_order_I);
  cout << "El costo es: " << farm2.calc_total_cost(f2_plots_order_I) << endl;

  cout << "\nPara el orden: ";
  print_vector(f2_plots_order_II);
  cout << "El costo es: " << farm2.calc_total_cost(f2_plots_order_II) << endl;
}


void print_map(const unordered_map<int, pair<int, vector<int>>>& mapa) {
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

void print_matrix(const vector<vector<int>> matriz){
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
