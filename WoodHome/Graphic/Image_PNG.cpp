#include "ImageBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include "png.h"
#define LOGW printf
#define PNG_BYTES_TO_CHECK 8

static void user_read_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
	memcpy(data, png_ptr->io_ptr, length * sizeof(char));
	png_ptr->io_ptr = ((char*)png_ptr->io_ptr) + length;
}

CImage_PNG::CImage_PNG():CImageBuffer()
{

}

CImage_PNG::~CImage_PNG()
{
}

void CImage_PNG::LoadFromMem( const char* data , int len)
{
	if(png_sig_cmp((png_bytep)data, (png_size_t)0, PNG_BYTES_TO_CHECK)) {
		LOGW("verify png sig failed");
	}

	// create necessary struct
	png_structp png_ptr;
	png_infop info_ptr;
	if ((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) == NULL) {
		LOGW("create png struct failed");
	}
	if ((info_ptr = png_create_info_struct(png_ptr)) == NULL) {
		LOGW("create png info struct failed");
		png_destroy_read_struct(&png_ptr, NULL, NULL);
	}

	// set error handler
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	}

	// set custom read function to read png from byte array
	// need to skip sig
	png_set_read_fn(png_ptr, (void*)(data + PNG_BYTES_TO_CHECK), user_read_fn);

	// set sig read
	png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);

	// read info
	int bit_depth;
	int color_type;
	png_uint_32 width;
	png_uint_32 height;
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

	// control png options
	if (!(color_type & PNG_COLOR_MASK_ALPHA))
		png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
	if (bit_depth > 8)
		png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	png_read_update_info(png_ptr, info_ptr);

	// allocate memory for rows
	png_uint_32 rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	char* image_data = NULL;
	if ((image_data = (char*)malloc(height * rowbytes)) == NULL) {
		LOGW("allocate png data buffer failed");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	}

	// allocate memory for row pointers
	png_bytepp row_pointers;
	if ((row_pointers = (png_bytepp)malloc( height * sizeof(png_bytep))) == NULL) {
		LOGW("allocate png row pointer buffer failed");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		free(image_data);
		image_data = NULL;
	}

	// read all rows
	for (png_uint_32 i = 0; i < height; i++)
		row_pointers[i] = (png_bytep)(image_data + i * rowbytes);
	png_read_image(png_ptr, row_pointers);
	free(row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	Initialize(width , height ,true);
	To565(image_data);
	free(image_data);
}


void CImage_PNG::To565( const char* data )
{
	for (int i = 0; i < mHeight ; i++)
	{
		for (int j = 0; j < mWidth ; j++)
		{
			mData[i * mWidth + j] = ConstructRGB(data[4*(i*mWidth+j)],data[4*(i*mWidth+j)+1],data[4*(i*mWidth+j)+2]);
			mAlpha[i * mWidth + j]= (unsigned char)(data[4*(i*mWidth+j)+3])>>3;
		}
	}
}