#include <libndls.h>
#include <ngc.h>
#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

#define DEBUG

void debug_display_board(game_t game) {
  char p[] = "RNBQKP  rnbqkp  ";

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      printf("%c", p[game.board8x8[i][j] % 16]);
    }
    printf("\n");
  }
}

buffer_t screenBuffer = {.buffer = NULL, .width = 320, .height = 240, .transparentColor = 0xFFFF};
unsigned char startFEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main(int argc, char *argv[]) {
  lcd_init(SCR_320x240_565);

  if(!(screenBuffer.buffer = malloc(320*240*2)))
    die("Couldn't allocate buffer !");

  game_t game = FEN_to_game(startFEN);

#ifdef DEBUG
  debug_display_board(game);
#endif

  parameters_t parameters = {.backgroundColor = 0x39A6, .caseColors = {0xEF7A, 0x74AA}, .x = 76, .y = 36};
  draw_board_noclip(screenBuffer, game, parameters);
  lcd_blit(screenBuffer.buffer, SCR_320x240_565);

  wait_key_pressed();

  lcd_init(SCR_TYPE_INVALID);;
  free(screenBuffer.buffer);

  return 0;
}
