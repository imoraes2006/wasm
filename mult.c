
/* 
  include needed to get access to EMSCRIPTEN_KEEPALIVE 
  macro that tells the compiler not to remove a function 
  if it appears unused
 */

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE

int mult(int a, int b) {
  return a*b;
}

