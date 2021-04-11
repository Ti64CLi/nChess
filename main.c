#include <ngc.h>
#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

buffer_t screenBuffer = {.buffer = NULL, .width = 320, .height = 240};

int main(int argc, char *argv[]) {
  lcd_init(SCR_320x240_565);

  if(!(screenBuffer.buffer = malloc(320*240*2)))
    die("Couldn't allocate buffer !");

  game_t game = FEN_to_game(startFEN);

  char p[] = "RNBQKP  rnbqkp  ";
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      printf("%c", p[game.board8x8[i][j]]);
    }
    printf("\n");
  }

  free(screenBuffer.buffer);

  return 0;
}
