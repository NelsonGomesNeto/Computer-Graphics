#include <queue>
#include <set>
#include <string>
#include <string.h>
#include "cube.h"
#include "solverSteps.h"
#include "../sleep.h"
using namespace std;

struct State
{
  Cube cube; int step; double value;
  bool operator<(const State& b) const { return(value < b.value || (value == b.value && step > b.step)); }
};
set<string> visited;
void display();

char op[7] = "RUFruf";
void bfs(Cube &c)
{
  visited.clear();
  queue<State> q; q.push({c, 0});
  while (!q.empty())
  {
    State now = q.front(); q.pop();
    c = now.cube; display();

    if (cross(now.cube) == 0)
    {
      printf("Took %d\n", now.step);
      break;
    }

    now.step ++;
    for (int i = 0; i < n; i ++)
    {
      if (i == n / 2) continue;
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        string cubeHash = now.cube.calculateHash();
        if (!visited.count(cubeHash))
        q.push(now), visited.insert(cubeHash);
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
    }
  }
  printf("Ended\n");
}

void Astar(Cube &c, double (*heuristic)(Cube&))
{
  visited.clear();
  priority_queue<State> q; q.push({c, 0, 0});
  while (!q.empty())
  {
    State now = q.top(); double prev = -now.value; q.pop();
    c = now.cube; display();
    printf("%lf\n", now.value);

    if (heuristic(now.cube) == 0)
    {
      printf("Took %d\n", now.step);
      break;
    }

    now.step ++;
    for (int i = 0; i < n; i ++)
    {
      if (i == n / 2) continue;
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        string cubeHash = now.cube.calculateHash();
        if (!visited.count(cubeHash))
        {
          now.value = -heuristic(now.cube);
          q.push(now), visited.insert(cubeHash);
        }
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
    }
  }
  printf("Ended\n");
}

void solve(Cube &c)
{
  Astar(c, cross);
  Astar(c, crossSides);
}
