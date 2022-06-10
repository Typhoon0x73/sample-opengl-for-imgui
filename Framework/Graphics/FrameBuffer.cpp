#include "FrameBuffer.h"

using namespace Sample;

/**
 * @brief		�R���X�g���N�^
 */
FrameBuffer::FrameBuffer()
: id_(0)
, width_(0)
, height_(0)
, color_() 
, depth_() {
}

/**
 * @brief		�f�X�g���N�^
 */
FrameBuffer::~FrameBuffer() {
	Release();
}

/**
 * @brief		����
 * @param[in]	w		��
 * @param[in]	h		����
 * @return		true	����
 *				false	���s
 */
bool FrameBuffer::Create(const int w, const int h) {
	//�T�C�Y�ۑ�
	width_ = w;
	height_ = h;
	// �t���[���o�b�t�@�I�u�W�F�N�g�A�f�v�X�ƃJ���[�p�̃e�N�X�`�����쐬
	glGenFramebuffersEXT(1, &id_);
	GL_ERROR_RETURN("�t���[���o�b�t�@�̍쐬�Ɏ��s...", false);
	color_ = std::make_shared<Texture>();
	color_->Create(w, h, Texture::FormatType::R8G8B8A8);
	depth_ = std::make_shared<Texture>();
	depth_->Create(w, h, Texture::FormatType::Depth);

	// �e�N�X�`�����t���[���o�b�t�@�I�u�W�F�N�g�Ƀo�C���h
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id_);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_->ID(), 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth_->ID(), 0);
	GL_ERROR_RETURN("�t���[���o�b�t�@�̃o�C���h�Ɏ��s...", false);

	// �f�t�H���g�̃^�[�Q�b�g�ɖ߂�
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	return true;
}

/**
 * @brief		�`��p�X�v���C�g����
 * @return		true	����
 *				false	���s
 */
SpritePtr FrameBuffer::CreateSprite(ShaderPtr shader) {
	SpritePtr sprite = std::make_shared<Sprite>();
	sprite->YFlip(true);
	sprite->Create(color_, shader);
	sprite->RefreshMatrix();
	return sprite;
}

/**
 * @brief		�o�C���h
 * @return		true	����
 *				false	���s
 */
bool FrameBuffer::Bind() {
	// �o�b�t�@��ύX
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id_);
	GL_ERROR_RETURN("�t���[���o�b�t�@�̃o�C���h�Ɏ��s...", false);
	glViewport(0, 0, width_, height_);
	return true;
}

/**
 * @brief		�������
 */
void FrameBuffer::Release() {
	if (id_ == 0)
	{
		return;
	}
	glDeleteFramebuffersEXT(1, &id_);
	id_ = 0;
	color_->Release();
	depth_->Release();
}