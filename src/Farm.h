#pragma once
#include "Plot.h"
#include <vector>

class Farm
{

private:
  vector<Plot> plots;

public:
  Farm(vector<Plot>);
  vector<int> calc_schedule(vector<int>);
  int calc_total_cost(vector<int>);
};