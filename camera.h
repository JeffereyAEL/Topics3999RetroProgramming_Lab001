
struct Camera{
  int Offset[2];
};

void Background_Draw() {//struct Camera* c) {
  vram_adr(NTADR_A(0,0));  
  vram_unrle(nametable);
}