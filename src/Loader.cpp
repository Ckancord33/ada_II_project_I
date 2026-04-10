#include "Loader.h"

Plot parsePlot(const string& line) {
    stringstream ss(line);
    int ts, tr, p, rp;
    if (!(ss >> ts >> tr >> p >> rp)) {
        throw runtime_error("Invalid plot line: '" + line + "'");
    }
    string extra;
    if (ss >> extra) {
        throw runtime_error("Extra tokens in plot line: '" + line + "'");
    }
    return Plot(ts, tr, p, rp);
}

Farm load(string path){
  ifstream file(path);
  if (!file.is_open()) {
      throw runtime_error("El archivo no se pudo abrir: " + path);
  }

  string line;
  if (!getline(file, line)) {
    throw runtime_error("Archivo vacío: " + path);
  }

  int n;
  try {
    n = stoi(line);
  } catch (const exception& e) {
    throw runtime_error("Invalid number of plots in first line: '" + line + "'");
  }

  vector<Plot> plots;
  plots.reserve(n);
  for (int i = 0; i < n; ++i) {
    if (!getline(file, line)) {
      throw runtime_error("Unexpected end of file while reading plots (expected " + to_string(n) + ")");
    }
    plots.push_back(parsePlot(line));
  }
  if(getline(file, line)){
    throw runtime_error("More than '" + to_string(n) + "' lines defined");
  }

  return Farm(plots);
}