#include "map.hpp"

#include <cstdio>

Map::Map(const int width, const int height) {
  this->width = width;
  this->height = height;

  this->matrix = new char *[height];
  for (int i = 0; i < height; i++) {
    this->matrix[i] = new char[width];
  }

  this->firstFrame = true;
}

Map::~Map() {
  for (int i = 0; i < this->height; i++) {
    delete[] this->matrix[i];
  }

  delete[] this->matrix;
}

void Map::fill(const char _char) {
  for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
      this->matrix[h][w] = _char;
    }
  }
}

void Map::border(const char _char) {
  for (int h = 1; h < this->height - 1; h++) {
    this->matrix[h][0] = _char;
    this->matrix[h][this->width - 1] = _char;
  }

  for (int w = 0; w < this->width; w++) {
    this->matrix[0][w] = _char;
    this->matrix[this->height - 1][w] = _char;
  }
}

void Map::draw(const char _char, const int x, const int y) {
  if ((x < 0 || x >= this->width) || (y < 0 || y >= this->height))
    return;
  this->matrix[y][x] = _char;
}

void Map::multipleDraw(const char _char, const mapPos *positions,
                       const int _s) {
  for (unsigned int i = 0; i < _s; i++) {
    this->draw(_char, positions[i].x, positions[i].y);
  }
}

void Map::render() {
  if (!this->firstFrame)
    printf("\e[%dA", this->height);
  else
    this->firstFrame = false;

  for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
      printf("%c", this->matrix[h][w]);
    }
    printf("\n");
  }
}
