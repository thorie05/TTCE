g++ -O0 -Wall -shared -std=c++23 -fPIC $(python3 -m pybind11 --includes) -I \
    engine/ $(find engine -type f -name "*.cpp") \
    -o game/ttce$(python3-config --extension-suffix)