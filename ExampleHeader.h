
static void Util_WriteTo(int[] xy, char* text, unsigned text_len)
{
  vram_adr(NTADR_A(xy[0], xy[1]));
  vram_write(text, text_len);
}

static void Util_WriteTo(char* text, unsigned text_len)
{
  vram_write(text, text_len);
}
  