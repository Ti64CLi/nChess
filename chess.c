#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chess.h"
#include "sprites.h"

void die(const char *msg) {
  printf(msg);
  exit(EXIT_FAILURE);
}

unsigned char is_space(unsigned char c) {
  return (c == ' ');
}

unsigned char is_lowercase(unsigned char c) {
  return ((c >= 'a') && (c <= 'z'));
}

unsigned char is_number(unsigned char c) {
  return ((c >= '0') && (c <= '9'));
}

unsigned char is_uppercase(unsigned char c) {
  return ((c <= 'Z') && (c >= 'A'));
}

unsigned char is_alpha(unsigned char c) {
  return (is_uppercase(c) || is_lowercase(c));
}

unsigned char to_lowercase(unsigned char c) {
  return (is_uppercase(c) ? (c + 0x20) : c);
}

game_t FEN_to_game(unsigned char *fen) {
  game_t game;
  unsigned char boardCase = 0;
  char p[] = "rnbqkp";

  while(!is_space(*fen)) {
    unsigned char c = (is_lowercase(*fen) ? BLACK_C : WHITE_C) << 3;
    if(is_alpha(*fen))
      game.board64[boardCase++] = (c | (strchr(p, to_lowercase(*fen)) - p));
    else if(is_number(*fen)) {
      for(int i = 0; i < (*fen - '0'); i++)
        game.board64[boardCase++] = 15;
    }
    else if((*fen) == '/') {
      for(int i = 0; i < 8; i++)
        game.board64[boardCase++] = 15;
    }

    fen++;
  }

  fen++;
  game.nextMove = ((*fen) == 'w' ? WHITE_C : BLACK_C);
  fen += 2;

  unsigned char sides[] = "KQkq";
  while(!is_space(*fen)) {
    for(int i = 0; i < 4; i++)
      game.castling[i] = ((*fen) == sides[i]) | game.castling[i];

    fen++;
  }

  if((*fen) == '-')
    game.enpassant = 0;
  else {
    game.enpassant = ((*fen) - 'a') + 8 * (8 - *(++fen) + '0');
  }

  fen += 2;

  unsigned char *t = fen;
  while(!is_space(*(++fen)));

  unsigned char *hm = NULL; // Halfmove Number
  if(!(hm = calloc(fen  - t + 1, sizeof(unsigned char))))
    die("Couldn't allocate memory !");
  memcpy(hm, t, fen - t);
  hm[fen - t] = '\0';
  game.halfmoveClock = atoi(hm);

  fen++;

  game.moveNumber = atoi(fen);

  return game;
}

void draw_sprite_noclip(buffer_t buffer, unsigned char *sprite, unsigned int x, unsigned char y, unsigned int w, unsigned char h, unsigned char zoom) {
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      for(int z = 0; z < zoom; z++) {
        // TODO
        // *(buffer + i *
      }
    }
  }
}

void draw_board_noclip(buffer_t buffer, game_t game, parameters_t param) {
  // TODO
}
