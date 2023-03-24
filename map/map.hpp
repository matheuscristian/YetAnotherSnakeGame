struct mapPos {
  int x;
  int y;
};

class Map {
private:
  char **matrix;
  bool firstFrame;

public:
  int width, height;

  Map(const int width, const int height);
  ~Map();

  void fill(const char _char);
  void border(const char _char);
  void draw(const char _char, const int x, const int y);
  void multipleDraw(const char _char, const mapPos *positions, const int _s);

  void render();
};
