#ifndef MOVE
#define MOVE

#include <cstdint>

class Move {
private:
  uint64_t light, dark, king;
public:
  Move();
  Move(uint64_t L, uint64_t D, uint64_t K);
  uint64_t valLight();
  uint64_t valDark();
  uint64_t valKing();
  void print();
};

#endif
