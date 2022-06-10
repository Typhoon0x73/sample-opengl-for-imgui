#include "Texture.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
Texture::Texture()
: ResourceBase()
, id_(0)
, width_(0) 
, height_(0) 
, format_(FormatType::Unknown) {
}

/**
 * @brief		コンストラクタ
 *				生成と同時に読み込みをおこなう
 * @param[in]	name	読み込むテクスチャ名
 */
Texture::Texture(const char* name)
: ResourceBase()
, id_(0)
, width_(0)
, height_(0)
, format_(FormatType::Unknown) {
	Load(name);
}

/**
 * @brief		デストラクタ
 */
Texture::~Texture() {
	Release();
}

/**
 * @brief		読み込み
 * @param[in]	name	読み込むテクスチャ名
 * @return		true	読み込み成功
 *				false	読み込み失敗
 */
bool Texture::Load(const char* name) {
	//png画像ファイルのロード
	png_structp sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	png_infop   ip = png_create_info_struct(sp);
	FILE* fp = fopen(name, "rb");
	if (!fp)
	{
		ERROR_LOG("テクスチャ" << name << "が開けません");
		return false;
	}
	png_init_io(sp, fp);
	png_read_info(sp, ip);
	int ColorType;
	int bpp;
	png_get_IHDR(sp, ip, (png_uint_32*)&width_, (png_uint_32*)&height_, &bpp, &ColorType, nullptr, nullptr, nullptr);
	//情報を変換して更新
	png_set_expand(sp);
	if (bpp > 8)
	{
		png_set_strip_16(sp);
	}
	if (ColorType == PNG_COLOR_TYPE_GRAY)
	{
		png_set_gray_to_rgb(sp);
	}
	png_read_update_info(sp, ip);
	//チャンネル数設定
	png_byte bits = png_get_channels(sp, ip);
	// メモリ領域確保
	int rb = png_get_rowbytes(sp, ip);
	GLubyte* data = new GLubyte[height_ * rb];
	GLubyte** recv = new GLubyte*[height_];
	for (int i = 0; i < height_; i++)
	{
		recv[i] = &data[i * rb];
	}
	//読み込み
	png_read_image(sp, recv);
	png_read_end(sp, ip);
	png_destroy_read_struct(&sp, &ip, NULL);
	delete[] recv;
	fclose(fp);

	//フォーマットを調べる
	int iFormat = GL_RGBA;
	int Format = GL_RGBA;
	int Type = GL_UNSIGNED_BYTE;
	switch (bits)
	{
	case 1:
		format_ = FormatType::Unknown;
		iFormat = GL_LUMINANCE;
		Format = GL_LUMINANCE;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		break;
	case 2:
		format_ = FormatType::Unknown;
		Type = GL_UNSIGNED_SHORT_4_4_4_4;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
		break;
	case 3:
		format_ = FormatType::R8G8B8;
		iFormat = GL_RGB;
		Format = GL_RGB;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		break;
	case 4:
		format_ = FormatType::R8G8B8A8;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		break;
	}
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D, 0, iFormat, width_, height_, 0, Format, Type, data);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// テクスチャのパラメータを設定する
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;
	name_ = name;
	INFO_LOG("テクスチャ" << name << "を読み込み...");
	return true;
}

/**
 * @brief		生成
 * @param[in]	w		幅
 * @param[in]	h		高さ
 * @param[in]	format	フォーマット
 * @return		true	成功
 *				false	失敗
 */
bool Texture::Create(const int w, const int h, const FormatType format) {
	//パラメーターを保存
	width_ = w;
	height_ = h;
	format_ = format;
	//生成
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	switch (format_)
	{
	case FormatType::R8G8B8:
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		break;

	case FormatType::R8G8B8A8:
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		break;

	case FormatType::Depth:
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		break;
	}
	// テクスチャのパラメータを設定する
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
	GL_ERROR_RETURN("テクスチャの生成に失敗...", false);
	name_ = "FrameBuffer";
	return true;
}

/**
 * @brief		テクスチャへのデータ書き込み
 * @param[in]	offX	書き込みオフセット
 * @param[in]	offY	書き込みオフセット
 * @param[in]	w		書き込みサイズ
 * @param[in]	h		書き込みサイズ
 * @param[in]	pixels	テクスチャに格納するデータ
 * @return		true	書き込み成功
 *				false	書き込み失敗
 */
bool Texture::SubData(GLint offX, GLint offY, GLint w, GLint h, const GLvoid* pixels) {
	glBindTexture(GL_TEXTURE_2D, id_);
	switch (format_)
	{
	case FormatType::R8G8B8:
		glTexSubImage2D(GL_TEXTURE_2D, 0, offX, offY, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		break;

	case FormatType::R8G8B8A8:
		glTexSubImage2D(GL_TEXTURE_2D, 0, offX, offY, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		break;

	case FormatType::Depth:
		glTexSubImage2D(GL_TEXTURE_2D, 0, offX, offY, w, h, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, pixels);
		break;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_ERROR_RETURN("テクスチャへのデータ転送に失敗...", false);
	return true;
}

/**
 * @brief		解放処理
 */
void Texture::Release() {
	if (id_ == 0)
	{
		return;
	}
	glDeleteTextures(1, &id_);
	id_ = 0;
	width_ = 0;
	height_ = 0;
	INFO_LOG("テクスチャ" << name_ << "を解放...");
	name_ = "";
}