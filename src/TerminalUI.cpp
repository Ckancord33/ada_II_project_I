#include "TerminalUI.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "Farm.h"
#include "Utils.h"

namespace fs = std::filesystem;

namespace
{
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string MAGENTA = "\033[35m";

struct AppState
{
  bool has_selected_file = false;
  fs::path selected_file;
};

void clear_screen()
{
  std::cout << "\033[2J\033[H";
}

void pause_for_enter()
{
  std::cout << "\nPresiona Enter para continuar...";
  std::string line;
  std::getline(std::cin, line);
}

void print_title(const std::string &title)
{
  std::cout << BOLD << CYAN;
  std::cout << "==============================================\n";
  std::cout << "      " << title << "\n";
  std::cout << "==============================================\n";
  std::cout << RESET;
}

int read_int_in_range(const std::string &prompt, int min_value, int max_value)
{
  while (true)
  {
    std::cout << YELLOW << prompt << RESET;
    std::string line;
    if (!std::getline(std::cin, line))
    {
      throw std::runtime_error("Entrada finalizada inesperadamente.");
    }

    std::stringstream ss(line);
    int value;
    char extra;
    if ((ss >> value) && !(ss >> extra) && value >= min_value && value <= max_value)
    {
      return value;
    }

    std::cout << RED << "Entrada invalida. Debe ser un numero entre " << min_value
              << " y " << max_value << ".\n" << RESET;
  }
}

int read_non_negative_int(const std::string &prompt)
{
  while (true)
  {
    std::cout << YELLOW << prompt << RESET;
    std::string line;
    if (!std::getline(std::cin, line))
    {
      throw std::runtime_error("Entrada finalizada inesperadamente.");
    }

    std::stringstream ss(line);
    int value;
    char extra;
    if ((ss >> value) && !(ss >> extra) && value >= 0)
    {
      return value;
    }

    std::cout << RED << "Entrada invalida. Debe ser un numero entero mayor o igual que 0.\n" << RESET;
  }
}

bool ask_yes_no(const std::string &prompt)
{
  while (true)
  {
    std::cout << YELLOW << prompt << " (s/n): " << RESET;
    std::string line;
    if (!std::getline(std::cin, line))
    {
      throw std::runtime_error("Entrada finalizada inesperadamente.");
    }

    if (line == "s" || line == "S")
    {
      return true;
    }
    if (line == "n" || line == "N")
    {
      return false;
    }

    std::cout << RED << "Respuesta invalida. Escribe 's' o 'n'.\n" << RESET;
  }
}

fs::path resolve_input_directory()
{
  std::vector<fs::path> candidates = {
      fs::current_path() / "input",
      fs::current_path() / "../input",
      fs::current_path() / "../../input"};

  for (const auto &candidate : candidates)
  {
    if (fs::exists(candidate) && fs::is_directory(candidate))
    {
      return fs::weakly_canonical(candidate);
    }
  }

  fs::path fallback = fs::current_path() / "input";
  fs::create_directories(fallback);
  return fs::weakly_canonical(fallback);
}

std::vector<fs::path> list_input_files(const fs::path &input_dir)
{
  std::vector<fs::path> files;

  for (const auto &entry : fs::directory_iterator(input_dir))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".txt")
    {
      files.push_back(entry.path());
    }
  }

  std::sort(files.begin(), files.end(), [](const fs::path &a, const fs::path &b)
            { return a.filename().string() < b.filename().string(); });

  return files;
}

template <typename F>
void run_and_print_metrics(const std::string &title, F solver)
{
  std::cout << "\n" << BOLD << MAGENTA << title << RESET << "\n";

  auto solution_and_time = take_time([&]
                                     { return solver(); });

  auto [solution, time] = solution_and_time;
  auto [cost, order] = solution;

  std::cout << GREEN << "Orden encontrado: " << RESET;
  print_vector(order);
  std::cout << GREEN << "Costo total: " << RESET << cost << "\n";
  std::cout << GREEN << "Tiempo de ejecucion: " << RESET << time << " microsegundos\n";
}

void run_solver_menu(const fs::path &file_path)
{
  clear_screen();
  print_title("Resolver Instancia");
  std::cout << "Archivo: " << file_path.string() << "\n\n";

  Farm farm = load(file_path.string());

  std::cout << "Elige un metodo:\n";
  std::cout << "  1) Fuerza bruta\n";
  std::cout << "  2) Programacion dinamica Top-Down\n";
  std::cout << "  3) Programacion dinamica Bottom-Up\n";
  std::cout << "  0) Volver\n\n";

  int option = read_int_in_range("Tu opcion: ", 0, 3);

  if (option == 0)
  {
    return;
  }

  if (option == 1)
  {
    if (ask_yes_no("Fuerza bruta puede tardar mucho. Deseas continuar?"))
    {
      run_and_print_metrics("Resultado - Fuerza bruta", [&]
                            { return farm.naive_solution(); });
    }
  }
  else if (option == 2)
  {
    run_and_print_metrics("Resultado - Dinamica Top-Down", [&]
                          { return farm.dynamic_solution_top_down(); });
  }
  else if (option == 3)
  {
    run_and_print_metrics("Resultado - Dinamica Bottom-Up", [&]
                          { return farm.dynamic_solution_bottom_up(); });
  }

  pause_for_enter();
}

void select_input_file(AppState &state, const fs::path &input_dir)
{
  clear_screen();
  print_title("Seleccionar Archivo");

  std::vector<fs::path> files = list_input_files(input_dir);
  if (files.empty())
  {
    std::cout << RED << "No hay archivos .txt en: " << input_dir.string() << "\n" << RESET;
    pause_for_enter();
    return;
  }

  std::cout << "Archivos disponibles:\n";
  for (size_t i = 0; i < files.size(); ++i)
  {
    std::cout << "  " << (i + 1) << ") " << files[i].filename().string() << "\n";
  }
  std::cout << "  0) Volver\n\n";

  int option = read_int_in_range("Elige un archivo: ", 0, static_cast<int>(files.size()));

  if (option == 0)
  {
    return;
  }

  state.selected_file = files[option - 1];
  state.has_selected_file = true;

  std::cout << "\n" << GREEN << "Archivo seleccionado: " << state.selected_file.filename().string() << RESET << "\n";
  pause_for_enter();
}

std::string ask_filename()
{
  while (true)
  {
    std::cout << YELLOW << "Nombre del archivo nuevo (sin ruta): " << RESET;
    std::string name;
    if (!std::getline(std::cin, name))
    {
      throw std::runtime_error("Entrada finalizada inesperadamente.");
    }

    if (name.empty())
    {
      std::cout << RED << "El nombre no puede estar vacio.\n" << RESET;
      continue;
    }

    if (name.find('/') != std::string::npos || name.find('\\') != std::string::npos)
    {
      std::cout << RED << "Solo escribe un nombre de archivo, no una ruta.\n" << RESET;
      continue;
    }

    if (name.size() < 4 || name.substr(name.size() - 4) != ".txt")
    {
      name += ".txt";
    }

    return name;
  }
}

void create_instance(AppState &state, const fs::path &input_dir)
{
  clear_screen();
  print_title("Crear Nueva Instancia");

  std::cout << "Cada plot requiere 4 valores enteros:\n";
  std::cout << "  ts: tiempo de supervivencia\n";
  std::cout << "  tr: tiempo de regado\n";
  std::cout << "  p : prioridad\n";
  std::cout << "  rp: tiempo de riego perfecto\n\n";

  int n = read_int_in_range("Cantidad de plots: ", 1, 100000);

  std::vector<std::array<int, 4>> plots;
  plots.reserve(static_cast<size_t>(n));

  for (int i = 0; i < n; ++i)
  {
    std::cout << "\n" << BOLD << "Plot " << (i + 1) << RESET << "\n";
    int ts = read_non_negative_int("  ts: ");
    int tr = read_non_negative_int("  tr: ");
    int p = read_non_negative_int("  p : ");
    int rp = read_non_negative_int("  rp: ");
    plots.push_back({ts, tr, p, rp});
  }

  std::cout << "\n";
  std::string file_name = ask_filename();
  fs::path output_path = input_dir / file_name;

  if (fs::exists(output_path))
  {
    if (!ask_yes_no("El archivo ya existe. Deseas sobreescribirlo?"))
    {
      std::cout << RED << "Operacion cancelada.\n" << RESET;
      pause_for_enter();
      return;
    }
  }

  std::ofstream out(output_path);
  if (!out.is_open())
  {
    throw std::runtime_error("No se pudo crear el archivo: " + output_path.string());
  }

  out << n << "\n";
  for (const auto &plot : plots)
  {
    out << plot[0] << " " << plot[1] << " " << plot[2] << " " << plot[3] << "\n";
  }

  out.close();

  state.selected_file = output_path;
  state.has_selected_file = true;

  std::cout << GREEN << "Instancia creada en: " << output_path.string() << RESET << "\n";
  std::cout << GREEN << "Quedo seleccionada automaticamente para resolverla.\n" << RESET;
  pause_for_enter();
}

} // namespace

void run_terminal_ui()
{
  AppState state;

  try
  {
    fs::path input_dir = resolve_input_directory();

    while (true)
    {
      clear_screen();
      print_title("ADA II - Interfaz de Terminal");

      std::cout << "Directorio input: " << input_dir.string() << "\n";
      if (state.has_selected_file)
      {
        std::cout << "Archivo actual : " << state.selected_file.filename().string() << "\n";
      }
      else
      {
        std::cout << "Archivo actual : (ninguno)\n";
      }

      std::cout << "\nMenu principal:\n";
      std::cout << "  1) Elegir archivo de input\n";
      std::cout << "  2) Elegir metodo y resolver archivo seleccionado\n";
      std::cout << "  3) Crear nueva instancia guiada\n";
      std::cout << "  0) Salir\n\n";

      int option = read_int_in_range("Tu opcion: ", 0, 3);

      if (option == 0)
      {
        clear_screen();
        std::cout << GREEN << "Hasta luego.\n" << RESET;
        break;
      }

      if (option == 1)
      {
        select_input_file(state, input_dir);
      }
      else if (option == 2)
      {
        if (!state.has_selected_file)
        {
          std::cout << "\n" << RED << "Primero debes seleccionar un archivo.\n" << RESET;
          pause_for_enter();
          continue;
        }

        try
        {
          run_solver_menu(state.selected_file);
        }
        catch (const std::exception &e)
        {
          std::cout << "\n" << RED << "Error al resolver: " << e.what() << "\n" << RESET;
          pause_for_enter();
        }
      }
      else if (option == 3)
      {
        try
        {
          create_instance(state, input_dir);
        }
        catch (const std::exception &e)
        {
          std::cout << "\n" << RED << "Error al crear instancia: " << e.what() << "\n" << RESET;
          pause_for_enter();
        }
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cout << RED << "Error de inicializacion: " << e.what() << "\n" << RESET;
  }
}
