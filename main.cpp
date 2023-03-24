#include "map/map.hpp"
#include "snake/snake.hpp"

#include <unistd.h>
#include <cstdlib>
#include <ctime>

constexpr int mapWidth = 20, mapHeight = 10, width = mapWidth - 1,
              height = mapHeight - 1;

bool isSnakeDead(bodyPos *head, const int snakeLength) {
  if ((head->x < 1 || head->x >= width) || (head->y < 1 || head->y >= height)) {
    return true;
  }

  bodyPos *body = head - snakeLength + 1;

  for (int i = 0; i < snakeLength - 1; i++) {
    if (body[i].x == head->x && body[i].y == head->y) {
      return true;
    }
  }

  return false;
}

inline bool isInSnake(const bodyPos &target, const bodyPos *snakeBody,
                      const int snakeLength) {
  for (int i = 0; i < snakeLength; i++) {
    if (target.x == snakeBody[i].x && target.y == snakeBody[i].y) {
      return true;
    }
  }

  return false;
}

mapPos genFruit(bodyPos *head, const int &snakeLength) {
  bodyPos *body = head - snakeLength + 1;
  mapPos fruit;

  do {
    fruit = {.x = rand() % (width - 1) + 1, .y = rand() % (height - 1) + 1};
  } while (isInSnake(*(const bodyPos *)&fruit, body, snakeLength));

  return fruit;
}

int main() {
  int snakeLen = 5;
  Snake snake(snakeLen, width * height - 1, mapWidth / 2 - snakeLen,
              mapHeight / 2);
  Map map(mapWidth, mapHeight);

  map.fill('-');
  map.border('*');

  map.render();

  direction currentDir = direction::right;

  srand(time(NULL));
  mapPos fruit = genFruit(snake.head, snakeLen);

  long long _t = 0, delayBFrame = 2e8;
  while (1) {
    if (_t < delayBFrame) {
      _t++;
      continue;
    }

    getInput(currentDir);

    bodyPos snakeBack;
    const bodyPos *snakeBody = snake.move(currentDir, snakeBack);

    if (isSnakeDead(snake.head, snakeLen)) {
      break;
    }

    if (snake.head->x == fruit.x && snake.head->y == fruit.y) {
      snake.grow(snakeLen);
      fruit = genFruit(snake.head, snakeLen);
      delayBFrame -= 1e6;
    }

    map.draw('-', snakeBack.x, snakeBack.y);
    map.draw('o', fruit.x, fruit.y);
    map.multipleDraw('#', (const mapPos *)snakeBody, snakeLen);

    _t = 0;
    map.render();
  }

  return 0;
}
