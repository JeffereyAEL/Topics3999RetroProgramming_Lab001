#include "neslib.h"
#include "Utils.h"

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// main function, run after console reset
void main(void) {

  // set palette colors
  pal_col(0,0x02);	// set screen to dark blue
  pal_col(1,0x14);	// fuchsia
  pal_col(2,0x20);	// grey
  pal_col(3,0x30);	// white

  // write text to name table
  vram_adr(NTADR_A(2, 2));
  vram_write("This is", 7);
  vram_adr(NTADR_A(2,3));
  vram_write("Jefferey Schlueter's", 20);
  vram_adr(NTADR_A(2,4));
  vram_write("first NES game!", 15);
    
  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // infinite loop
  while (1) ;
}
