
struct Camera{
  int Offset[2];
};

void Background_Draw() {//struct Camera* c) {
  // place static level geometry
  char x, y;
  for (x=1; x < VIS_SCREEN_x; x++)
    for (y=FLOOR_H; y < VIS_SCREEN_y; y++)
    { 
      if (FLOOR_H > sin(x))
        vram_adr(NTADR_A(x, y));
        vram_put('\x0C');
    }
}