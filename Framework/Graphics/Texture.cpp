#include "Texture.h"

using namespace Sample;

/**
 * @brief		�R���X�g���N�^
 */
Texture::Texture()
: ResourceBase()
, id_(0)
, width_(0) 
, height_(0) 
, format_(FormatType::Unknown) {
}

/**
 * @brief		�R���X�g���N�^
 *				�����Ɠ����ɓǂݍ��݂������Ȃ�
 * @param[in]	name	�ǂݍ��ރe�N�X�`����
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
 * @brief		�f�X�g���N�^
 */
Texture::~Texture() {
	Release();
}

/**
 * @brief		�ǂݍ���
 * @param[in]	name	�ǂݍ��ރe�N�X�`����
 * @return		true	�ǂݍ��ݐ���
 *				false	�ǂݍ��ݎ��s
 */
bool Texture::Load(const char* name) {
	//png�摜�t�@�C���̃��[�h
	png_structp sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	png_infop   ip = png_create_info_struct(sp);
	FILE* fp = fopen(name, "rb");
	if (!fp)
	{
		ERROR_LOG("�e�N�X�`��" << name << "���J���܂���");
		return false;
	}
	png_init_io(sp, fp);
	png_read_info(sp, ip);
	int ColorType;
	int bpp;
	png_get_IHDR(sp, ip, (png_uint_32*)&width_, (png_uint_32*)&height_, &bpp, &ColorType, nullptr, nullptr, nullptr);
	//����ϊ����čX�V
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
	//�`�����l�����ݒ�
	png_byte bits = png_get_channels(sp, ip);
	// �������̈�m��
	int rb = png_get_rowbytes(sp, ip);
	GLubyte* data = new GLubyte[height_ * rb];
	GLubyte** recv = new GLubyte*[height_];
	for (int i = 0; i < height_; i++)
	{
		recv[i] = &data[i * rb];
	}
	//�ǂݍ���
	png_read_image(sp, recv);
	png_read_end(sp, ip);
	png_destroy_read_struct(&sp, &ip, NULL);
	delete[] recv;
	fclose(fp);

	//�t�H�[�}�b�g�𒲂ׂ�
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

	// �e�N�X�`���̃p�����[�^��ݒ肷��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] data;
	name_ = name;
	INFO_LOG("�e�N�X�`��" << name << "��ǂݍ���...");
	return true;
}

/**
 * @brief		����
 * @param[in]	w		��
 * @param[in]	h		����
 * @param[in]	format	�t�H�[�}�b�g
 * @return		true	����
 *				false	���s
 */
bool Texture::Create(const int w, const int h, const FormatType format) {
	//�p�����[�^�[��ۑ�
	width_ = w;
	height_ = h;
	format_ = format;
	//����
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
	// �e�N�X�`���̃p�����[�^��ݒ肷��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
	GL_ERROR_RETURN("�e�N�X�`���̐����Ɏ��s...", false);
	name_ = "FrameBuffer";
	return true;
}

/**
 * @brief		�e�N�X�`���ւ̃f�[�^��������
 * @param[in]	offX	�������݃I�t�Z�b�g
 * @param[in]	offY	�������݃I�t�Z�b�g
 * @param[in]	w		�������݃T�C�Y
 * @param[in]	h		�������݃T�C�Y
 * @param[in]	pixels	�e�N�X�`���Ɋi�[����f�[�^
 * @return		true	�������ݐ���
 *				false	�������ݎ��s
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
	GL_ERROR_RETURN("�e�N�X�`���ւ̃f�[�^�]���Ɏ��s...", false);
	return true;
}

/**
 * @brief		�������
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
	INFO_LOG("�e�N�X�`��" << name_ << "�����...");
	name_ = "";
}