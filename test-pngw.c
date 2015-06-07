#include "pngw.h"

#include <stdio.h>

void out_fun(struct pngw_arg *p, const void *data, int len)
{
	fwrite(data,len,1,stdout);
}
int read_fun(struct pngw_arg *p)
{
	static int x = 0;
	static int y = 0;
	int k;
	if (x < 32 && y < 32) {
		k=0;
	} else if (y < 32) {
		k=1;
	} else if (x < 32) {
		k=2;
	} else {
		k=0;
	}
	x++;
	if (x == 640) {x=0;y++; }
	return k;
}
int main(int argc, char *argv[])
{
	struct pngw_arg pw;
	unsigned int my_pal[16];

	pw.width = 640;
	pw.height = 400;
	pw.pal_size = 3;
	pw.pal = my_pal;
	my_pal[0] = 0xff0000ff;
	my_pal[1] = 0xff00ff00;
	my_pal[2] = 0xffff0000;
	pw.output = out_fun;
	pw.read_pixel = read_fun;
	pngw(&pw);
	return 0;
}
