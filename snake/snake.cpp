#include "snake.hpp"

#include <termios.h>
#include <unistd.h>

struct termios defaultTermios;

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &defaultTermios); }

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &defaultTermios);
  struct termios raw = defaultTermios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

extern void getInput(direction &_out_dir) {
  char _c;

  while (read(STDIN_FILENO, &_c, 1)) {
    if (_c == 'w' && _out_dir != direction::down) {
      _out_dir = direction::up;
      break;
    }

    if (_c == 'd' && _out_dir != direction::left) {
      _out_dir = direction::right;
      break;
    }

    if (_c == 's' && _out_dir != direction::up) {
      _out_dir = direction::down;
      break;
    }

    if (_c == 'a' && _out_dir != direction::right) {
      _out_dir = direction::left;
      break;
    }
  }
}

Snake::Snake(const int initialLength, const int maxLength, const int initialX,
             const int initialY) {
  enableRawMode();

  this->length = initialLength;
  this->maxLength = maxLength;
  this->body = new bodyPos[maxLength];

  for (int i = 0; i < initialLength; i++) {
    this->body[i].y = initialY;
    this->body[i].x = initialX + i;
  }

  this->head = &this->body[initialLength - 1];
}

Snake::~Snake() {
  delete[] this->body;
  disableRawMode();
}

const bodyPos *Snake::move(const direction &_dir, bodyPos &_out_back) {
  _out_back = this->body[0];

  for (int i = 0; i < this->length - 1; i++) {
    this->body[i] = this->body[i + 1];
  }

  switch (_dir) {
  case direction::up:
    this->body[this->length - 1].y--;
    break;
  case direction::right:
    this->body[this->length - 1].x++;
    break;
  case direction::down:
    this->body[this->length - 1].y++;
    break;
  case direction::left:
    this->body[this->length - 1].x--;
    break;
  default:
    break;
  }

  return this->body;
}

void Snake::grow(int &_out_length) {
  if (this->length == this->maxLength)
    return;

  for (int i = this->length; i > 0; i--) {
    this->body[i] = this->body[i - 1];
  }

  this->length++;
  _out_length = this->length;
  this->head = &this->body[this->length - 1];
}
