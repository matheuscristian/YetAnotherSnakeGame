echo "Building map..."
g++ map/map.cpp -c -o map/map.o

echo "Building snake..."
g++ snake/snake.cpp -c -o snake/snake.o

echo "Building main..."
g++ main.cpp map/map.o snake/snake.o -o game
