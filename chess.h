#ifndef CHESS_H
#define CHESS_H

#define WIDTH 21
#define HEIGHT 21

#define COLUMNS 8
#define LINES 8

typedef enum {
  ROOK = 0,
  KNIGHT = 1,
  BISHOP = 2,
  QUEEN = 3,
  KING = 4,
  PAWN = 5
} type_e;

typedef enum {
  WHITE_C = 0,
  BLACK_C = 1
} color_e;

typedef struct {
  unsigned char *buffer;
  unsigned short width, height;

  unsigned short transparentColor;
} buffer_t;

typedef struct {
  unsigned int backgroundColor;
  unsigned int caseColors[2];

  unsigned short x;
  unsigned char y;

  //unsigned char zoom;
} parameters_t;

typedef struct {
  union {
    unsigned char board64[64];
    unsigned char board8x8[8][8];
  };
  color_e nextMove;
  unsigned char castling[4];
  unsigned char enpassant;
  unsigned char halfmoveClock;
  unsigned char moveNumber;
} game_t;

void die(const char *msg);

game_t FEN_to_game(unsigned char *fen);

void fill_buffer(buffer_t buffer, unsigned short color);
void draw_horiz_line_noclip(buffer_t buffer, unsigned short x, unsigned short y, unsigned short w, unsigned short color);
void draw_rect_noclip(buffer_t buffer, unsigned short x, unsigned short y, unsigned short w, unsigned char h, unsigned short color);
void draw_sprite_noclip(buffer_t buffer, unsigned char *sprite, unsigned short x, unsigned char y, unsigned short w, unsigned char h);
void draw_board_noclip(buffer_t buffer, game_t game, parameters_t param);

#endif
