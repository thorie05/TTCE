g++ -O0 -std=c++23 -I engine/ auxiliary/test/test.cpp $(find engine \
    -type f -name "*.cpp" ! -name "ttce.cpp") -o auxiliary/test/test
