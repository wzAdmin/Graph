#include "ImageBuffer.h"
#include <stdlib.h>
#include <memory>
#ifdef __cplusplus
extern "C" {
#endif
	// libjpeg, need place it in extern C
#include "jpeglib.h"
#ifdef __cplusplus
}
#endif

static void jpeg_error_exit(j_common_ptr cinfo) {
	(*cinfo->err->output_message)(cinfo);
}

static void jpeg_output_message(j_common_ptr cinfo) {
//	char buffer[JMSG_LENGTH_MAX];
	/* Create the message */
// 	(*cinfo->err->format_message)(cinfo, buffer);
// 
// 	// output log
// 	LOGE("%s", buffer);
}

CImage_JPG::CImage_JPG():CImageBuffer()
{

}

CImage_JPG::~CImage_JPG()
{
}

void CImage_JPG::To565(const char* data)
{
	for (int i = 0; i < mHeight ; i++)
	{
		for (int j = 0; j < mWidth ; j++)
		{
			mData[i * mWidth + j] = ConstructRGB(data[4*(i*mWidth+j)],data[4*(i*mWidth+j)+1],data[4*(i*mWidth+j)+2]);
		}
	}
}
void CImage_JPG::LoadFromMem(const char* data , int len)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr pub;
	JSAMPARRAY buffer;
	int row_stride;

	// use custom error handler
	cinfo.err = jpeg_std_error(&pub);
	pub.error_exit = jpeg_error_exit;
	pub.output_message = jpeg_output_message;

	// init decompress struct
	jpeg_create_decompress(&cinfo);

	// specify data source
	jpeg_stdio_buffer_src(&cinfo, data, len);

	// read header
	jpeg_read_header(&cinfo, TRUE);

	// save size
	Initialize(cinfo.image_width,cinfo.image_height,false);

	// set out color space
	cinfo.out_color_space = JCS_RGBA_8888;

	// start decompress
	jpeg_start_decompress(&cinfo);

	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;

	/* Make a one-row-high sample array that will go away when done with image */
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
										JPOOL_IMAGE, row_stride, 1);

	// allocate returned buffer
	char* image_data = (char*)malloc(mHeight * row_stride * sizeof(char));
	char* tmp = image_data;

	/*
		* Here we use the library's state variable cinfo.output_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		*/
	while (cinfo.output_scanline < cinfo.output_height) {
		/*
			* jpeg_read_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could ask for
			* more than one scanline at a time if that's more convenient.
			*/
		jpeg_read_scanlines(&cinfo, buffer, 1);

		// put to returned buffer
		memcpy(tmp, buffer[0], row_stride * sizeof(char));
		tmp += row_stride;
	}
	// Finish decompression
	jpeg_finish_decompress(&cinfo);
	// This is an important step since it will release a good deal of memory
	jpeg_destroy_decompress(&cinfo);
	To565(image_data);
	free(image_data);
}