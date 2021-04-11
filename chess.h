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
} buffer_t;

typedef struct {
  unsigned int backgroundColor;
  unsigned int caseColors[2];

  unsigned short x;
  unsigned char y;

  unsigned char zoom;
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

const unsigned char startFEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

game_t FEN_to_game(unsigned char *fen);
void draw_sprite_noclip(buffer_t buffer, unsigned char *sprite, unsigned int x, unsigned char y, unsigned int w, unsigned char h, unsigned char zoom);
void draw_board_noclip(buffer_t buffer, game_t game, parameters_t param);

#endif
