#define PlayerAnimLen 2
#define PlayerTicksPerFrame 15
#define PlayerColor SPR4

#define LEFT_BOUNDS 8
#define RIGHT_BOUNDS 233


struct Player{
  sbyte Vel[2];
  int Pos[2];
  sbyte Acc[2];
  char Color;
  char InitSprite;
  char Frame;
  byte bGrounded;
};

void Player_Init(struct Player* p) {
  p->Pos[0] = 0; p->Pos[1] = (FLOOR_H-1)*32;
  p->Vel[0] = 0; p->Vel[1] = 0;
  p->Acc[0] = 0; p->Acc[1] = 0;
  p->Frame = 0;
  p->InitSprite = 0xD8;
  p->bGrounded = 0;
}

#define PlayerSpeed 2
#define PlayerMaxJump 2
void Player_Events(struct Player* p, char e) {
  p->Vel[0] = 0;
  if (e & PAD_RIGHT)
    p->Vel[0] = PlayerSpeed;//DrawDebugMsg("Right",5);
  if (e & PAD_LEFT)
    p->Vel[0] = -PlayerSpeed;//DrawDebugMsg("Left",5);
  if ((e & PAD_UP) && p->bGrounded < PlayerMaxJump)
  {
    p->Vel[1] = -6; p->Acc[1] = 1; p->bGrounded += 1;
  }
}

void Player_Update(struct Player* p) {
  p->Frame = (p->Frame + !(__Ticks % PlayerTicksPerFrame) * 1) % PlayerAnimLen;
  
  p->Pos[0] += p->Vel[0]; p->Pos[1] += p->Vel[1];
  p->Vel[0] += p->Acc[0]; p->Vel[1] += p->Acc[1];
  if (p->Pos[0] < LEFT_BOUNDS)
    p->Pos[0] = LEFT_BOUNDS;
  else if (p->Pos[0] > RIGHT_BOUNDS)
    p->Pos[0] = RIGHT_BOUNDS;
  if (p->Pos[1] > FLOOR_PIXEL_H)
  {
    p->Pos[1] = FLOOR_PIXEL_H; p->Vel[1] = 0; p->Acc[1] = 0;
    p->bGrounded = 0;
  }
}

void Player_Draw(struct Player* p, char* oam) {
  char attrib = PlayerColor|FLIPHORZ * (p->Vel[0] < 0);
  DrawSprite(p->InitSprite, p->Pos, p->Frame, oam, attrib);
}

