#ifndef MOVE
#define MOVE

#include <cstdint>

class Move {
private:
  uint64_t light, dark, king;
public:
  Move() {
    dark = light = king = 0x0000000000000000;
  }
  Move(uint64_t L, uint64_t D, uint64_t K){
    light = L;
    dark = D;
    king = K;
  }
  uint64_t valLight() {
    return light;
  }
  uint64_t valDark() {
    return dark;
  }
  uint64_t valKing() {
    return king;
  }
};

#endif
