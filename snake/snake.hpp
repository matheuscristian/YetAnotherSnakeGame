enum direction { up, right, down, left };

struct bodyPos {
  int x;
  int y;
};

class Snake {
private:
  bodyPos *body;
  int length;
  int maxLength;

public:
  bodyPos *head;

  Snake(const int initialLength, const int maxLength, const int initialX,
        const int initialY);
  ~Snake();

  const bodyPos *move(const direction &_dir, bodyPos &_out_back);
  void grow(int &_out_length);
};

extern void getInput(direction &_out_dir);
