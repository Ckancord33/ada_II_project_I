#pragma once

using namespace std;

class Plot{
  private:
    int ts; //tiempo de supervivencia
    int tr; //tiempo de regado
    int p; //prioridad del tablon
    int rp; //tiempo de riego perfecto
  
  public:
    Plot(int, int, int, int);
    int calc_cost(int);
    int get_tr();
    

};