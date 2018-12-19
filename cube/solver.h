#include <queue>
#include <string.h>
#include "cube.h"
#include "../sleep.h"
using namespace std;

struct State
{
  Cube cube; int step; double value;
  bool operator<(const State& b) const { return(value < b.value); }
};
void display();

int solved(Cube &c)
{
  int value = c.face[3][0][1] == 3;
  value += c.face[3][1][2] == 3; value += c.face[3][1][1] == 3;
  value += c.face[3][2][1] == 3; value += c.face[3][1][0] == 3;
  return(value);
}

char op[7] = "RUFruf";
void bfs(Cube &c)
{
  queue<State> q; q.push({c, 0});
  while (!q.empty())
  {
    State now = q.front(); q.pop();
    c = now.cube; display();

    if (solved(now.cube) == 5)
    {
      printf("Took %d\n", now.step);
      break;
    }
    // if (now.step > 1) continue;

    now.step ++;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        q.push(now);
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
  }
  printf("Ended\n");
}

void Astar(Cube &c)
{
  priority_queue<State> q; q.push({c, 0});
  while (!q.empty())
  {
    State now = q.top(); q.pop();
    c = now.cube; display();

    if (now.value == 5)
    {
      printf("Took %d\n", now.step);
      break;
    }
    // if (now.step > 1) continue;

    now.step ++;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < 6; j ++)
      {
        moveCube(now.cube, op[j], i);
        now.value = solved(now.cube);
        q.push(now);
        moveCube(now.cube, op[(j + 3) % 6], i);
      }
  }
  printf("Ended\n");
}
