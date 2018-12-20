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
set<Cube> visited;
void display(); bool DISPLAY = false;

char op[7] = "RUFruf";
void bfs(Cube &c, double (*finished)(Cube&))
{
  queue<State> q; q.push({c, 0});
  while (!q.empty())
  {
    State now = q.front(); q.pop();
    c = now.cube; if (DISPLAY) display();

    for (int i = 0; i < 12; i ++)
    {
      edgePosition ep = findEdgePosition(now.cube, edgeColor[i][0], edgeColor[i][1]);
      // printf("%d %d | %d %d - %d\n", edgeColor[i][0], edgeColor[i][1], ep.face1, ep.face2, mapEdgeColor[ep.face1][ep.face2]);
      if (edgeDistanceMemo[i][edgeColor[i][0] < edgeColor[i][1]][mapEdgeColor[ep.face1][ep.face2]][ep.color1 < ep.color2] == -1)
      {
        edgeDistanceMemo[i][edgeColor[i][0] < edgeColor[i][1]][mapEdgeColor[ep.face1][ep.face2]][ep.color1 < ep.color2] = now.step;
        edgeDistanceMemo[mapEdgeColor[ep.face1][ep.face2]][ep.color1 < ep.color2][i][edgeColor[i][0] < edgeColor[i][1]] = now.step;
      }
    }

    if (finished(now.cube) == 0)
    {
      printf("Took %d steps | Visited %d states\n", now.step, (int) visited.size());
      break;
    }
    if (now.step == 4) continue;

    now.step ++;
    for (int i = 0; i < n; i ++)
    {
      if (i == n / 2) continue;
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        // string cubeHash = now.cube.calculateHash();
        if (!visited.count(now.cube))
          q.push(now), visited.insert(now.cube);
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
    }
  }
  visited.clear();
}

void Astar(Cube &c, double (*heuristic)(Cube&))
{
  priority_queue<State> q; q.push({c, 0, 0});
  while (!q.empty())
  {
    State now = q.top(); double prev = -now.value; q.pop();
    c = now.cube; if (DISPLAY) display();

    if (heuristic(now.cube) == 0)
    {
      printf("Took %d steps | Visited %d states\n", now.step, (int) visited.size());
      break;
    }
    if (q.size() > 1e7) break;

    now.step ++;
    for (int i = 0; i < n; i ++)
    {
      if (i == n / 2) continue;
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        // string cubeHash = now.cube.calculateHash();
        if (!visited.count(now.cube))
        {
          now.value = -heuristic(now.cube);
          q.push(now), visited.insert(now.cube);
        }
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
    }
  }
  visited.clear();
}

void solve(Cube &c)
{
  // bfs(c, cross);
  // bfs(c, crossSides);
  // Astar(c, cross);
  // Astar(c, crossSides);
  // int edgeColor[12][2] = {{0, 1}, {0, 5}, {0, 4}, {0, 3}, {2, 1}, {2, 5}, {2, 4}, {2, 3}, {1, 5}, {1, 4}, {3, 5}, {3, 4}};
  memset(edgeDistanceMemo, -1, sizeof(edgeDistanceMemo));
  bfs(c, edgeDistance);
  for (int i = 0; i < 12; i ++)
    for (int j = 0; j < 12; j ++)
      for (int k = 0; k < 2; k ++)
        for (int m = 0; m < 2; m ++)
          printf("%d (%d) -> %d (%d): %d\n", i, k, j, m, edgeDistanceMemo[i][k][j][m]);
}
