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

unsigned char is_uppercase(unsigned char c) {
  return ((c <= 'Z') && (c >= 'A'));
}

unsigned char is_alpha(unsigned char c) {
  return (is_uppercase(c) || is_lowercase(c));
}

unsigned char is_number(unsigned char c) {
  return ((c >= '0') && (c <= '9'));
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

    if(is_alpha(*fen)) {
      game.board64[boardCase++] = (c | (strchr(p, to_lowercase(*fen)) - p));
    }
    else if(is_number(*fen)) {
      for(int i = 0; i < ((*fen) - '0'); i++)
        game.board64[boardCase++] = 15;
    }
    else if((*fen) == '/') {
      for(; (boardCase % 8) != 0;)
        game.board64[boardCase++] = 15;
    }

    fen++;
  }

  fen++;
  game.nextMove = ((*fen) == 'w' ? WHITE_C : BLACK_C);
  fen++; fen++;

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

  fen++; fen++;

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

void fill_buffer(buffer_t buffer, unsigned short color) {
  unsigned char *s;
  for(int i = 0; i < buffer.height; i++) {
    for(int j = 0; j < buffer.width; j++) {
      *(s = (buffer.buffer + 2 * (i * buffer.width + j))) = color & 0xFF;
      *(s + 1) = (color & 0xFF00) >> 8;
    }
  }
}

void draw_horiz_line_noclip(buffer_t buffer, unsigned short x, unsigned short y, unsigned short w, unsigned short color) {
  unsigned char *s = buffer.buffer + 2 * (y * buffer.width + x);

  for(int i = 0; i < w; i++) {
    *(s++) = color & 0xFF;
    *(s++) = (color & 0xFF00) >> 8;
  }
}

void draw_rect_noclip(buffer_t buffer, unsigned short x, unsigned short y, unsigned short w, unsigned char h, unsigned short color) {
  for(int i = 0; i < h; i++)
    draw_horiz_line_noclip(buffer, x, y + i, w, color);
}

void draw_sprite_noclip(buffer_t buffer, unsigned char *sprite, unsigned short x, unsigned char y, unsigned short w, unsigned char h) {
  unsigned char *s, *t;

  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if((*(t = (sprite + 2 * (i * w + j))) != ((buffer.transparentColor & 0xFF00) >> 8)) || (*(t + 1) != ((buffer.transparentColor & 0xFF)))) { // if color != transparentColor (*2 because of two bytes per pixel)
        *(s = (buffer.buffer + 2 * ((i + y) * buffer.width + j + x))) = *(t + 1); // same reason
        *(s + 1) = *t;
      }
    }
  }
}

unsigned char *get_sprite(int value) {
  color_e color = (value & 8) >> 3;

  switch(value & 7) {
    case 0:
      return rook[color];
    case 1:
      return knight[color];
    case 2:
      return bishop[color];
    case 3:
      return queen[color];
    case 4:
      return king[color];
    case 5:
    default:
      return pawn[color];
  }
}

void draw_board_noclip(buffer_t buffer, game_t game, parameters_t param) {
  fill_buffer(buffer, param.backgroundColor);

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      draw_rect_noclip(buffer, param.x + 21 * j, param.y + 21 * i, 21, 21, param.caseColors[(i + j) % 2]);
      if(game.board8x8[i][j] < 15)
        draw_sprite_noclip(buffer, /*pieces[game.board8x8[i][j] & 7][(game.board8x8[i][j] & 8) >> 3]*/get_sprite(game.board8x8[i][j]), param.x + 21 * j, param.y + 21 * i, 21, 21);
    }
  }
}
