#include <coco_conio.h>

int main()
{
  unsigned char c;

  init_screen(40);

  cputsxy( 2, 2, "this is a test..." );
  cvline( 10 );
  cputc( '\n' );

  c = cgetc();

  return 0;
}
