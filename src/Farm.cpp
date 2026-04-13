#include "Farm.h"

int inf = INT_MAX;

Farm::Farm(vector<Plot> plots) : plots(plots) {}

//Calcula el tiempo en el que se inicia cada tablon
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
  for(int i = 0; i < schedule.size(); i++){
    total_cost += plots[i].calc_cost(schedule[i]);
  }
  return total_cost;
}

vector<int> Farm::delete_position(vector<int> original, int idx){
    if (idx >= 0 && idx < original.size()) {
        original.erase(original.begin() + idx);
    }
    return original;
}

vector<int> Farm::add_element(vector<int> original, int element){
    original.push_back(element);
    return original;
}

void Farm::generate(vector<int> remaining, vector<int> current, vector<vector<int>>& permutations){
  if(remaining.size() == 0){
    permutations.push_back(current);
    return;
  }

  for(int i = 0; i < remaining.size(); i ++){
    int next = remaining[i];
    generate(delete_position(remaining, i), add_element(current, next), permutations);
  }

}

vector<vector<int>> Farm::get_permutations(int n){
  vector<int> init(n, 0);
  for(int i = 0; i < n; i ++){
    init[i] = i;
  }
  vector<vector<int>> permutations;
  generate(init, {}, permutations);
  return permutations;
}

tuple<int, vector<int>> Farm::naive_solution(){
  int n = plots.size();
  vector<vector<int>> all_orders = get_permutations(n);
  vector<int> best_solution;
  int best_cost = INT_MAX;
  for(vector<int> order : all_orders){
    int new_cost = calc_total_cost(order);
    if(new_cost < best_cost){
      best_cost = new_cost;
      best_solution = order;
    }
  }
  return tuple<int, vector<int>>(best_cost, best_solution);

}


pair<int,int> get_min_and_index(const vector<int>& row_cost_matrix){
  int min = inf;
  int index = 0;
  for (int i = 0; i < row_cost_matrix.size();i++){
      if (row_cost_matrix[i] < min){
        min = row_cost_matrix[i];
        index = i;
      }
  }
  return pair<int,int>(min,index);
}


void Farm::fill_cost_matrix(vector<vector<int>>& cost_matrix, int row, vector<vector<int>>& path){

  vector<int> temp_total_matrix(row);
  bool firstTime = true;
  int pos = 0,pos0 = 0,pos1 = 0, temp = 0,  qAct = 0, mask_only_p1 = 0,mask_only_p0 =0;


  for(int i = 1; i < row; i++){
    qAct = __builtin_popcount(i);
    if (qAct == 1){

      pos = __builtin_ctz(i);
      cost_matrix[i][pos] = plots[pos].calc_cost(0);
      temp_total_matrix[i] =  plots[pos].get_tr();

    }else if (qAct == 2){

      pos0 = __builtin_ctz(i);
      pos1 = __builtin_ctz(i & (i - 1));
      mask_only_p1 = i & (1 << pos1);
      mask_only_p0 = i & (1 << pos0);
      cost_matrix[i][pos0] = cost_matrix[mask_only_p1][pos1] + plots[pos0].calc_cost(plots[pos1].get_tr());
      cost_matrix[i][pos1] = cost_matrix[mask_only_p0][pos0] + plots[pos1].calc_cost(plots[pos0].get_tr());
      temp_total_matrix[i] = temp_total_matrix[mask_only_p1] + temp_total_matrix[mask_only_p0];
      path[i][pos0] = pos1;
      path[i][pos1] = pos0;

    }else{

      firstTime = true;
      for(int sub = i; sub ; sub &= (sub - 1)){
        pos = __builtin_ctz(sub);
        temp = i & ~(1 << pos);
        const auto [minCost,index] = get_min_and_index(cost_matrix[temp]);
        path[i][pos] = index;
        cost_matrix[i][pos] = minCost + plots[pos].calc_cost(temp_total_matrix[temp]);
        if (firstTime){
          temp_total_matrix[i] = temp_total_matrix[temp] + plots[pos].get_tr();
          firstTime = false;
        }
      }

    }
  }
}

vector<int> build_solution(vector<vector<int>> path,int lastPos, int row){

    int nextPos = lastPos;
    int i = row - 1;
    vector<int> solution;
    int parent = 0;

    while (nextPos != -1) {
        solution.insert(solution.begin(), nextPos);
        parent = path[i][nextPos];
        i &= ~(1 << nextPos);
        nextPos = parent;
    }

    return solution;
}


tuple<int, vector<int>> Farm::dynamic_programming_solution(){

  int n = plots.size();
  int row = 1 << n;

  vector<vector<int>> cost_matrix(row, vector<int>(n, inf));

  vector<vector<int>> path(row, vector<int>(n, -1));

  fill_cost_matrix(cost_matrix,row,path);

  auto [minCost,index] = get_min_and_index(cost_matrix[row-1]);

  vector<int> solution = build_solution(path, index,row);

  return tuple<int, vector<int>>(minCost, solution);
 
}

