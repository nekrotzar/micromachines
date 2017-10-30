#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10

typedef GLushort WORD;
typedef GLubyte byte;

typedef struct tImageTGA
{
	int channels;
	int size_x;	
	int size_y;				
	unsigned char *data;
} tImageTGA;


void TGA_Texture(unsigned int *textureArray, char *strFileName, int ID);

tImageTGA *Load_TGA(char *filename);




// www.morrowland.com
// apron@morrowland.com