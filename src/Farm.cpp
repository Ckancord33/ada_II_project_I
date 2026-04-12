#include "Farm.h"

int inf = numeric_limits<int>::max();

Farm::Farm(vector<Plot> plots) : plots(plots) {}

unordered_map<int, pair<int, vector<int>>> get_dictionary_bits(int n);

// Calcula el tiempo en el que se inicia cada tablon
vector<int> Farm::calc_schedule(vector<int> plots_order)
{
  int n = plots_order.size();
  vector<int> schedule(n, 0);
  int time = 0;
  for (int i = 0; i < n; i++)
  {
    int idx = plots_order[i];
    schedule[idx] = time;
    time += plots[idx].get_tr();
  }
  return schedule;
}

int Farm::calc_total_cost(vector<int> plots_order)
{
  vector<int> schedule = calc_schedule(plots_order);
  int total_cost = 0;
  for (int i = 0; i < schedule.size(); i++)
  {
    total_cost += plots[i].calc_cost(schedule[i]);
  }
  return total_cost;
}

vector<int> Farm::delete_position(vector<int> original, int idx)
{
  if (idx >= 0 && idx < original.size())
  {
    original.erase(original.begin() + idx);
  }
  return original;
}

vector<int> Farm::add_element(vector<int> original, int element)
{
  original.push_back(element);
  return original;
}

void Farm::generate(vector<int> remaining, vector<int> current, vector<vector<int>> &permutations)
{
  if (remaining.size() == 0)
  {
    permutations.push_back(current);
    return;
  }

  for (int i = 0; i < remaining.size(); i++)
  {
    int next = remaining[i];
    generate(delete_position(remaining, i), add_element(current, next), permutations);
  }
}

vector<vector<int>> Farm::get_permutations(int n)
{
  vector<int> init(n, 0);
  for (int i = 0; i < n; i++)
  {
    init[i] = i;
  }
  vector<vector<int>> permutations;
  generate(init, {}, permutations);
  return permutations;
}

tuple<int, vector<int>> Farm::naive_solution()
{
  int n = plots.size();
  vector<vector<int>> all_orders = get_permutations(n);
  vector<int> best_solution;
  int best_cost = INT_MAX;
  for (vector<int> order : all_orders)
  {
    int new_cost = calc_total_cost(order);
    if (new_cost < best_cost)
    {
      best_cost = new_cost;
      best_solution = order;
    }
  }
  return tuple<int, vector<int>>(best_cost, best_solution);
}

int Farm::calc_total_subset_time(int bitmask)
{
  int total_time = 0;
  for (int i = 0; i < plots.size(); i++)
  {
    if (bitmask & (1 << i))
    {
      total_time += plots[i].get_tr();
    }
  }
  return total_time;
}

int Farm::auxiliar_top_down(int bitmask, vector<int> &memo, unordered_map<int, pair<int, vector<int>>> &dictionary_bits)
{
  if (memo[bitmask] != -1)
    return memo[bitmask];
  int min_cost = INT_MAX;
  for (int i : dictionary_bits.at(bitmask).second)
  {
    int new_bitmask = bitmask & ~(1 << i);
    int time = calc_total_subset_time(new_bitmask);
    int cost = auxiliar_top_down(new_bitmask, memo, dictionary_bits) + plots[i].calc_cost(time);
    min_cost = min(min_cost, cost);
  }
  memo[bitmask] = min_cost;
  return memo[bitmask];
}

tuple<int, vector<int>> Farm::dynamic_solution_top_down()
{
  int n = plots.size();
  unordered_map<int, pair<int, vector<int>>> dictionary_bits = get_dictionary_bits(1 << n);
  vector<int> memo(1 << plots.size(), -1);
  memo[0] = 0;
  for (int i = 0; i < plots.size(); i++)
  {
    memo[1 << i] = plots[i].calc_cost(0);
  }
  int init_bitmask = (1 << plots.size()) - 1;
  int best_cost = auxiliar_top_down(init_bitmask, memo, dictionary_bits);
  return tuple<int, vector<int>>(best_cost, {});
}

unordered_map<int, pair<int, vector<int>>> get_dictionary_bits(int n)
{

  unordered_map<int, pair<int, vector<int>>> dict;

  dict.reserve(n + 1);

  int temp = 0;
  int count = 0;
  int pos = 0;

  for (int i = 0; i < n; ++i)
  {
    temp = i;
    count = 0;
    vector<int> positions;
    while (temp > 0)
    {
      pos = __builtin_ctz(temp);
      positions.push_back(pos);
      count++;
      temp &= (temp - 1);
    }

    dict[i] = {count, positions};
  }

  return dict;
}

void Farm::fill_cost_matrix(vector<vector<int>> &cost_matrix, const unordered_map<int, pair<int, vector<int>>> &dictionary_bits, int row, vector<vector<int>> &path)
{

  int qAct = 0;
  vector<int> positionAct;
  int minCost = 0;
  vector<int> vecRowAct;

  vector<int> temp_total_matrix(row);

  int temp = 0;

  bool firstTime = true;

  int index = 0;

  for (int i = 1; i < row; i++)
  {
    qAct = dictionary_bits.at(i).first;
    positionAct = dictionary_bits.at(i).second;
    if (qAct == 1)
    {
      cost_matrix[i][positionAct[0]] = plots[positionAct[0]].calc_cost(0);
      temp_total_matrix[i] = plots[positionAct[0]].get_tr();
    }
    else if (qAct == 2)
    {
      cost_matrix[i][positionAct[0]] = cost_matrix[i & (1 << positionAct[1])][positionAct[1]] + plots[positionAct[0]].calc_cost(plots[positionAct[1]].get_tr());
      cost_matrix[i][positionAct[1]] = cost_matrix[i & (1 << positionAct[0])][positionAct[0]] + plots[positionAct[1]].calc_cost(plots[positionAct[0]].get_tr());
      temp_total_matrix[i] = temp_total_matrix[i & (1 << positionAct[1])] + temp_total_matrix[i & (1 << positionAct[0])];
      path[i][positionAct[0]] = positionAct[1];
      path[i][positionAct[1]] = positionAct[0];
    }
    else
    {
      firstTime = true;
      for (int pos : positionAct)
      {
        temp = i & ~(1 << pos);
        vecRowAct = cost_matrix[temp];
        minCost = *min_element(vecRowAct.begin(), vecRowAct.end());
        index = distance(vecRowAct.begin(), find(vecRowAct.begin(), vecRowAct.end(), minCost));
        path[i][pos] = index;
        cost_matrix[i][pos] = minCost + plots[pos].calc_cost(temp_total_matrix[temp]);
        if (firstTime)
        {
          temp_total_matrix[i] = temp_total_matrix[temp] + plots[pos].get_tr();
          firstTime = false;
        }
      }
    }
  }
}

vector<int> build_solution(vector<vector<int>> path, int lastPos, int row)
{

  int nextPos = lastPos;
  int i = row - 1;
  vector<int> solution;
  int parent = 0;

  while (nextPos != -1)
  {
    solution.insert(solution.begin(), nextPos);
    parent = path[i][nextPos];
    i &= ~(1 << nextPos);
    nextPos = parent;
  }

  return solution;
}

tuple<int, vector<int>> Farm::dynamic_programming_solution()
{

  int n = plots.size();
  int row = 1 << n;
  int column = n;

  vector<vector<int>> cost_matrix(row, vector<int>(column, inf));

  vector<vector<int>> path(row, vector<int>(column, -1));

  unordered_map<int, pair<int, vector<int>>> dictionary_bits = get_dictionary_bits(row);

  fill_cost_matrix(cost_matrix, dictionary_bits, row, path);

  vector<int> last_row_cost_matrix = cost_matrix[row - 1];

  int minCost = *min_element(last_row_cost_matrix.begin(), last_row_cost_matrix.end());
  int index = distance(last_row_cost_matrix.begin(), find(last_row_cost_matrix.begin(), last_row_cost_matrix.end(), minCost));

  vector<int> solution = build_solution(path, index, row);

  return tuple<int, vector<int>>(minCost, solution);
}
