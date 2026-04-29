#include "Plot.h"

/*
  ts  -> tiempo de supervivencia
    - tiempo máximo que puede pasar sin regar antes de perderse.

  tr  -> tiempo de regado / duración del riego
    - cuánto dura el riego necesario para el tablón.

  p   -> prioridad del tablón
    - peso/penalización para retrasos en el riego; afecta el costo.

  rp  -> tiempo de riego perfecto
    - instante ideal para regar.
*/

Plot::Plot(int ts, int tr, int p, int rp) : ts(ts), tr(tr), p(p), rp(rp) {};

// Dado t (tiempo programado) calcula el costo de regar el tablon
int Plot::calc_cost(int t)
{

  // Cuando el tiempo programado es antes del tiempo de supervivencia y si alcanza a regarlo
  if (t == rp)
    return ts - (t + tr); //bonus por tiempo perfecto
  if (ts - tr >= t)
    return 2 * (ts - (t + tr));

  // en caso de que ya paso el tiempo de supervivencia o no lo alcanza regar antes del tiempo de supervivencia
  else
    return 2 * p * ((t + tr) - ts);
}

int Plot::get_tr(){return tr;}
int Plot::get_ts(){return ts;}
int Plot::get_p(){return p;}
int Plot::get_rp(){return rp;}