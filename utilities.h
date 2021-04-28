
char Min(char a, char b) {
  return a * (a<b) + b * (a<b);
}
char Max(char a, char b) {
  return a * (a>b) + b * (a>b);
}

#define DebugMsgLen 10
void DrawDebugMsg(char* error_msg, char len) {
  char msg[DebugMsgLen];
  int i;
  char l = Min(len, DebugMsgLen);
  for (i = 0; i < l; ++i) msg[i] = error_msg[i];
  for (; i < DebugMsgLen; ++i) msg[i] = ' ';
  vram_adr(NTADR_A(2,5));
  vram_write(msg, DebugMsgLen);
}

void DrawSprite(char sprite, int pos[2], char frame, char* oam, char attrib){
  if (attrib & FLIPHORZ) {
    *oam = oam_spr(pos[0]+8, pos[1],     sprite+frame*4,     attrib,    *oam);
    *oam = oam_spr(pos[0]+8, pos[1]+8,   sprite+1+frame*4,   attrib,    *oam);
    *oam = oam_spr(pos[0],   pos[1],     sprite+2+frame*4,   attrib,    *oam);
    *oam = oam_spr(pos[0],   pos[1]+8,   sprite+3+frame*4,   attrib,    *oam);
  } else {
    *oam = oam_spr(pos[0],   pos[1],     sprite+frame*4,     attrib,    *oam);
    *oam = oam_spr(pos[0],   pos[1]+8,   sprite+1+frame*4,   attrib,    *oam);
    *oam = oam_spr(pos[0]+8, pos[1],     sprite+2+frame*4,   attrib,    *oam);
    *oam = oam_spr(pos[0]+8, pos[1]+8,   sprite+3+frame*4,   attrib,    *oam);
  }
}

int sin(int x)
{
  int res=0; int pow=x; int fact=1; int i = 0;
  for(; i<5; ++i) {
    res += pow/fact;
    pow = pow * -1 * x * x;
    fact = fact * (( 2*(i+1))*(2*(i+1)+1));
  }
  return res;
}

int GetFloor(int x)
{
  return sin(x);
}