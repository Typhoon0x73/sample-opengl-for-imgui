#ifndef SPRITEANIMATION_H_
#define SPRITEANIMATION_H_

#include <vector>
#include <string>
#include <utility>
#include <cstdint>

// --------------------------------------------------------------------------------
/// <summary>
/// �X�v���C�g�A�j���[�V�����N���X
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimation
{
public:

	// --------------------------------------------------------------------------------
	/// <summary>
	/// �p�^�[���\����
	/// </summary>
	// --------------------------------------------------------------------------------
	struct Pattern
	{
		std::int32_t        m_ImageNo         {  -1 };     //!< �摜�ԍ�
		std::int32_t        m_OffsetX         {   0 };     //!< �I�t�Z�b�gX
		std::int32_t        m_OffsetY         {   0 };     //!< �I�t�Z�b�gY
		std::int32_t        m_Width           {   0 };     //!< ����
		std::int32_t        m_Height          {   0 };     //!< ����
		double              m_RefreshTime     { 0.0 };     //!< �`�掞��(�P�ʂ͕b)
		std::int32_t        m_DrawOffsetX     {   0 };     //!< �`��I�t�Z�b�gX
		std::int32_t        m_DrawOffsetY     {   0 };     //!< �`��I�t�Z�b�gY

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		// ********************************************************************************
		explicit Pattern() = default;

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="copy">�R�s�[�f�[�^</param>
		// ********************************************************************************
		explicit Pattern(const Pattern& copy);

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="move">���[�u�f�[�^</param>
		// ********************************************************************************
		explicit Pattern(Pattern&& move);

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="n">�摜�ԍ�</param>
		/// <param name="x">�I�t�Z�b�gX</param>
		/// <param name="y">�I�t�Z�b�gY</param>
		/// <param name="w">����</param>
		/// <param name="h">����</param>
		/// <param name="t">�`�掞��(�P�ʂ͕b)</param>
		/// <param name="ox">�`��I�t�Z�b�gX</param>
		/// <param name="oy">�`��I�t�Z�b�gY</param>
		// ********************************************************************************
		explicit Pattern(std::int32_t n, std::int32_t x, std::int32_t y,
			std::int32_t w, std::int32_t h, double t, std::int32_t ox, std::int32_t oy);

		// ********************************************************************************
		/// <summary>
		/// operator= ������Z
		/// </summary>
		/// <param name="copy">�R�s�[�f�[�^</param>
		/// <returns>*this</returns>
		// ********************************************************************************
		SpriteAnimation::Pattern& operator=(const SpriteAnimation::Pattern& copy);

		// ********************************************************************************
		/// <summary>
		/// operator= ������Z
		/// </summary>
		/// <param name="move">���[�u�f�[�^</param>
		/// <returns>*this</returns>
		// ********************************************************************************
		SpriteAnimation::Pattern& operator=(SpriteAnimation::Pattern&& move);

		// ********************************************************************************
		/// <summary>
		/// operator== ������r���Z
		/// </summary>
		/// <param name="pattern">��r�Ώ�</param>
		/// <returns>true : �p�^�[���f�[�^��v, false : ��v���Ȃ�</returns>
		// ********************************************************************************
		bool operator==(const SpriteAnimation::Pattern& pattern) const;

		// ********************************************************************************
		/// <summary>
		/// operator!= ��r���Z
		/// </summary>
		/// <param name="pattern">��r�Ώ�</param>
		/// <returns>!(*this == pattern)</returns>
		// ********************************************************************************
		bool operator!=(const SpriteAnimation::Pattern& pattern) const;
	};

public:

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	// ********************************************************************************
	explicit SpriteAnimation() = default;

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="copy">�R�s�[�f�[�^</param>
	// ********************************************************************************
	explicit SpriteAnimation(const SpriteAnimation& copy);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="move">���[�u�f�[�^</param>
	// ********************************************************************************
	explicit SpriteAnimation(SpriteAnimation&& move);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="patterns">�p�^�[���z��</param>
	/// <param name="hasLooped">���[�v�t���O</param>
	// ********************************************************************************
	explicit SpriteAnimation(const std::vector<SpriteAnimation::Pattern>& patterns, bool hasLooped);
	
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="patterns">�p�^�[���z��(���[�u)</param>
	/// <param name="hasLooped">���[�v�t���O</param>
	// ********************************************************************************
	explicit SpriteAnimation(std::vector<SpriteAnimation::Pattern>&& patterns, bool hasLooped);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="patterns">�p�^�[���z��</param>
	/// <param name="count">�p�^�[���o�^��</param>
	/// <param name="hasLooped">���[�v�t���O</param>
	// ********************************************************************************
	explicit SpriteAnimation(SpriteAnimation::Pattern* patterns, std::size_t count, bool hasLooped);
	
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimation();

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	/// <param name="deltaTime">�X�V����(�P�ʂ͕b)</param>
	/// <returns>true : �X�V����, false : �X�V�Ȃ�</returns>
	// ********************************************************************************
	bool update(const float deltaTime);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̒ǉ�
	/// </summary>
	/// <param name="pattern">�ǉ�����p�^�[���f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addPattern(const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̒ǉ�
	/// </summary>
	/// <param name="pattern">�ǉ�����p�^�[���f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addPattern(SpriteAnimation::Pattern&& pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����z��ԍ�</param>
	/// <param name="pattern">�ύX��̃p�^�[���f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setPattern(std::size_t no, const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����z��ԍ�</param>
	/// <param name="pattern">�ύX��̃p�^�[���f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setPattern(std::size_t no, SpriteAnimation::Pattern&& pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̍폜
	/// </summary>
	/// <param name="no">�폜����z��ԍ�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removePattern(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̍폜
	/// </summary>
	/// <param name="pattern">�폜����p�^�[���f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removePattern(const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̍폜
	/// </summary>
	/// <param name="pattern">�폜����p�^�[���f�[�^�̃C�e���[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removePattern(std::vector<SpriteAnimation::Pattern>::const_iterator pattern);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̑S�폜
	/// </summary>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool clear();

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���z��̕ύX
	/// </summary>
	/// <param name="patterns">�ύX��̃p�^�[���z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setPatternArray(const std::vector<SpriteAnimation::Pattern>& patterns);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���z��̕ύX
	/// </summary>
	/// <param name="patterns">�ύX��̃p�^�[���z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setPatternArray(std::vector<SpriteAnimation::Pattern>&& patterns);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���z��̕ύX
	/// </summary>
	/// <param name="patterns">�ύX��̃p�^�[���z��</param>
	/// <param name="count">�ύX��̃p�^�[����</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setPatternArray(SpriteAnimation::Pattern* patterns, std::size_t count);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����̃��[�v�ݒ�
	/// </summary>
	/// <param name="hasLooped">true : ���[�v����, false : ���[�v���Ȃ�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setLoop(bool hasLooped);

	// ********************************************************************************
	/// <summary>
	/// �Đ����p�^�[���ԍ��̕ύX
	/// </summary>
	/// <param name="no">�ύX��̃p�^�[���ԍ�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setCurrentPatternNo(std::int32_t no);

	// ********************************************************************************
	/// <summary>
	/// ���Ԏw��ɂ��Đ����p�^�[���ԍ��̕ύX
	/// </summary>
	/// <param name="t">�Đ��������A�j���[�V�����o�ߎ���(�P�ʂ͕b)</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setCurrentPatternNoByTime(double t);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���A�j���[�V�����̍Đ�
	/// </summary>
	/// <param name="no">�Đ��J�n�p�^�[���ԍ�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool play(std::size_t no = 0);

	// ********************************************************************************
	/// <summary>
	/// �J�n���Ԏw��ɂ��p�^�[���A�j���[�V�����̍Đ�
	/// </summary>
	/// <param name="t">�Đ��J�n�A�j���[�V��������(�P�ʂ͕b)</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool playByTime(double t = 0.0);
	
	// ********************************************************************************
	/// <summary>
	/// �p�^�[���z��̎擾
	/// </summary>
	/// <returns>�p�^�[���z��|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const std::vector<SpriteAnimation::Pattern>* const patternArray() const;

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���z��̎擾
	/// </summary>
	/// <returns>�p�^�[���z��|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	std::vector<SpriteAnimation::Pattern>* const patternArray();

	// ********************************************************************************
	/// <summary>
	/// ���Ԏw��ɂ��p�^�[���f�[�^�̎擾
	/// </summary>
	/// <param name="t">�擾�������A�j���[�V��������(�P�ʂ͕b)</param>
	/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const patternByTime(double t) const;

	// ********************************************************************************
	/// <summary>
	/// ���Ԏw��ɂ��p�^�[���f�[�^�̎擾
	/// </summary>
	/// <param name="t">�擾�������A�j���[�V��������(�P�ʂ͕b)</param>
	/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const patternByTime(double t);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̎擾
	/// </summary>
	/// <param name="no">�擾�������z��ԍ�</param>
	/// <returns>�p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no) const;

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���f�[�^�̎擾
	/// </summary>
	/// <param name="no">�擾�������z��ԍ�</param>
	/// <returns>�p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃p�^�[���f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const currentPattern() const;

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃p�^�[���f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const currentPattern();

	// ********************************************************************************
	/// <summary>
	/// ���[�v�ݒ�̊m�F
	/// </summary>
	/// <returns>true : ���[�v����, false : ���[�v���Ȃ�</returns>
	// ********************************************************************************
	bool hasLooped() const;

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�������I�����Ă��邩����(���[�v�t���O�������Ă���ΕK��false���Ԃ�)
	/// </summary>
	/// <returns>true : �A�j���[�V�����I��, false : �A�j���[�V������</returns>
	// ********************************************************************************
	bool hasEnded() const;

	// ********************************************************************************
	/// <summary>
	/// ���Ԏw��ɂ��p�^�[���ԍ��̎擾
	/// </summary>
	/// <param name="t">�擾����������</param>
	/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���ԍ�</returns>
	// ********************************************************************************
	std::int32_t patternNoByTime(double t) const;

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃p�^�[���ԍ��̎擾
	/// </summary>
	/// <returns>�Đ����̃p�^�[���ԍ�, -1 : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	std::int32_t currentPatternNo() const;

	// ********************************************************************************
	/// <summary>
	/// �p�^�[���ύX�p�^�C�}�[�̎擾
	/// </summary>
	/// <returns>�p�^�[�����̌o�ߎ���(�P�ʂ͕b)</returns>
	// ********************************************************************************
	double timer() const;

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����I���܂ł̍��v���Ԃ̎擾(���[�v�֌W�Ȃ��z��̍��v�`�掞�Ԃ��Ԃ�)
	/// </summary>
	/// <returns>�A�j���[�V�����I���܂ł̍��v����(�P�ʂ͕b)</returns>
	// ********************************************************************************
	double totalTime() const;

	// ********************************************************************************
	/// <summary>
	/// operator= ������Z
	/// </summary>
	/// <param name="copy">�R�s�[�f�[�^</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimation& operator=(const SpriteAnimation& copy);

	// ********************************************************************************
	/// <summary>
	/// operator= ������Z
	/// </summary>
	/// <param name="move">���[�u�f�[�^</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimation& operator=(SpriteAnimation&& move);

	// ********************************************************************************
	/// <summary>
	/// operator== ������r���Z
	/// </summary>
	/// <param name="animation">��r�Ώ�</param>
	/// <returns>true : �A�j���[�V�����f�[�^��v, false : ��v���Ȃ�</returns>
	// ********************************************************************************
	bool operator==(const SpriteAnimation& animation) const;

	// ********************************************************************************
	/// <summary>
	/// operator!= ��r���Z
	/// </summary>
	/// <param name="animation">��r���Z</param>
	/// <returns>!(*this == animation)</returns>
	// ********************************************************************************
	bool operator!=(const SpriteAnimation& animation) const;

private:

	// ********************************************************************************
	/// <summary>
	/// �����ōĐ����̃p�^�[���ԍ����ۂ߂鏈��
	/// </summary>
	// ********************************************************************************
	void roundCurrentPatternNo();

	std::vector<Pattern>     m_PatternArray         {     0 };     //!< �p�^�[���z��
	bool                     m_hasLooped            { false };	   //!< ���[�v�t���O
	std::int32_t             m_CurrentPatternNo     {    -1 };	   //!< �Đ����̃p�^�[���ԍ�
	double                   m_Timer                {   0.0 };	   //!< �Đ����̃p�^�[���X�V�p�^�C�}�[
	double                   m_TotalTime            {   0.0 };	   //!< �A�j���[�V�����I���܂ł̍��v����

};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// �X�v���C�g�A�j���[�V�����Ǘ��N���X
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationController
{
public:

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	// ********************************************************************************
	explicit SpriteAnimationController() = default;

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="copy">�R�s�[�f�[�^</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const SpriteAnimationController& copy);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="move">���[�u�f�[�^</param>
	// ********************************************************************************
	explicit SpriteAnimationController(SpriteAnimationController&& move);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pFile">.sa�t�@�C���p�X</param>
	/// <param name="outTexturePathArray">�o�͐�摜�t�@�C���p�X�z��</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const char* pFile, std::vector<std::string>* outTexturePathArray);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pData">.sa�f�[�^</param>
	/// <param name="dataLen">�f�[�^��</param>
	/// <param name="outTexturePathArray">�o�͐�摜�t�@�C���p�X�z��</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const char* pData, std::size_t dataLen, std::vector<std::string>* outTexturePathArray);
	
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="animations">�A�j���[�V�����z��</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="animations">�A�j���[�V�����z��</param>
	// ********************************************************************************
	explicit SpriteAnimationController(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="animations">�A�j���[�V�����z��</param>
	/// <param name="count">�A�j���[�V������</param>
	// ********************************************************************************
	explicit SpriteAnimationController(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);
	
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationController();

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	/// <param name="deltaTime">�X�V����(�P�ʂ͕b)</param>
	/// <returns>true : �X�V����, false : �X�V�Ȃ�</returns>
	// ********************************************************************************
	bool update(const float deltaTime);
	
	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="name">�A�j���[�V������</param>
	/// <param name="animation">�A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(const std::string& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="name">�A�j���[�V������</param>
	/// <param name="animation">�A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(const std::string& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="name">�A�j���[�V������</param>
	/// <param name="animation">�A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(std::string&& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="name">�A�j���[�V������</param>
	/// <param name="animation">�A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(std::string&& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="animation">�A�j���[�V�����z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̒ǉ�
	/// </summary>
	/// <param name="animation">�A�j���[�V�����z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool addAnimation(std::pair<std::string, SpriteAnimation>&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�������̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimationName(std::size_t no, const std::string& name);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�������̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimationName(std::size_t no, std::string&& name);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::string& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::string& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::string&& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="name">�ύX��̖��O</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::string&& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̕ύX
	/// </summary>
	/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
	/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::pair<std::string, SpriteAnimation>&& animation);
	
	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̍폜
	/// </summary>
	/// <param name="no">�폜����A�j���[�V�����z��ԍ�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// ���O�w��ŃA�j���[�V�����f�[�^�̍폜(���ꖼ�͂��ׂč폜)
	/// </summary>
	/// <param name="name">�폜����A�j���[�V������</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(const std::string& name);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�w��ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
	/// </summary>
	/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// [key, data]�ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
	/// </summary>
	/// <param name="name">�폜����A�j���[�V������</param>
	/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(const std::string& name, SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�w��ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
	/// </summary>
	/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// �C�e���[�^�w��ŃA�j���[�V�����f�[�^�̍폜
	/// </summary>
	/// <param name="animation">�폜����A�j���[�V�����f�[�^�C�e���[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool removeAnimation(std::vector<std::pair<std::string, SpriteAnimation>>::const_iterator animation);
	
	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����f�[�^�̑S�폜
	/// </summary>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool clear();

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����z��̕ύX
	/// </summary>
	/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����z��̕ύX
	/// </summary>
	/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����z��̕ύX
	/// </summary>
	/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
	/// <param name="count">�ύX��̃A�j���[�V������</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool setAnimation(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);

	// ********************************************************************************
	/// <summary>
	/// �Đ��A�j���[�V�����̕ύX
	/// </summary>
	/// <param name="key">�ύX��̃A�j���[�V�����ԍ�</param>
	/// <param name="isSamed">�Đ����̃A�j���[�V�����Ɠ���ŏ㏑�����Ȃ��t���O(false�w��œ���A�j���[�V�����ł�0����Đ�)</param>
	/// <returns>true : �ύX����, false : �ύX�Ȃ�</returns>
	// ********************************************************************************
	bool changeAnimation(std::size_t key, bool isSamed = true);

	// ********************************************************************************
	/// <summary>
	/// ���O�w��ōĐ��A�j���[�V�����̕ύX(���ꖼ����������ꍇ�ŏ��̃A�j���[�V�����ɂȂ�)
	/// </summary>
	/// <param name="key">�ύX��̃A�j���[�V������</param>
	/// <param name="isSamed">�Đ����̃A�j���[�V�����Ɠ���ŏ㏑�����Ȃ��t���O(false�w��œ���A�j���[�V�����ł�0����Đ�)</param>
	/// <returns>true : �ύX����, false : �ύX�Ȃ�</returns>
	// ********************************************************************************
	bool changeAnimation(const std::string& key, bool isSamed = true);

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����z��̎擾
	/// </summary>
	/// <returns>�A�j���[�V�����z��, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray() const;

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����z��̎擾
	/// </summary>
	/// <returns>�A�j���[�V�����z��, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray();

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃A�j���[�V�����f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃A�j���[�V�����f�[�^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const SpriteAnimation* const currentAnimation() const;

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃A�j���[�V�����f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃A�j���[�V�����f�[�^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	SpriteAnimation* const currentAnimation();

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃p�^�[���f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃p�^�[���f�[�^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const currentPattern() const;

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃p�^�[���f�[�^�̎擾
	/// </summary>
	/// <returns>�Đ����̃p�^�[���f�[�^, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const currentPattern();

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃A�j���[�V�������̎擾
	/// </summary>
	/// <returns>�Đ����̃A�j���[�V������, nullptr : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	const std::string* const currentAnimationName() const;

	// ********************************************************************************
	/// <summary>
	/// �Đ����̃A�j���[�V�����ԍ��̎擾
	/// </summary>
	/// <returns>�Đ����̃A�j���[�V�����ԍ�, -1 : �f�[�^�Ȃ�</returns>
	// ********************************************************************************
	std::int32_t currentAnimationNo() const;

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�������̎擾
	/// </summary>
	/// <returns>�A�j���[�V������</returns>
	// ********************************************************************************
	std::size_t animationCount() const;

	// ********************************************************************************
	/// <summary>
	/// operator= ������Z
	/// </summary>
	/// <param name="copy">�R�s�[�f�[�^</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimationController& operator=(const SpriteAnimationController& copy);

	// ********************************************************************************
	/// <summary>
	/// operator= ������Z
	/// </summary>
	/// <param name="move">���[�u�f�[�^</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimationController& operator=(SpriteAnimationController&& move);

	// ********************************************************************************
	/// <summary>
	/// operator== ������r���Z
	/// </summary>
	/// <param name="controller">��r�Ώ�</param>
	/// <returns>true : ��v, false : ��v���Ȃ�</returns>
	// ********************************************************************************
	bool operator==(const SpriteAnimationController& controller) const;

	// ********************************************************************************
	/// <summary>
	/// operator!= ��r���Z
	/// </summary>
	/// <param name="controller">��r�Ώ�</param>
	/// <returns>!(*this == controller)</returns>
	// ********************************************************************************
	bool operator!=(const SpriteAnimationController& controller) const;

private:

	// ********************************************************************************
	/// <summary>
	/// �����ōĐ����̃A�j���[�V�����ԍ����ۂ߂鏈��
	/// </summary>
	// ********************************************************************************
	void roundCurrentAnimationNo();

	std::vector<std::pair<std::string, SpriteAnimation>>     m_AnimationArray         {  0 };     //!< �A�j���[�V�����z��
	std::int32_t                                             m_CurrentAnimationNo     { -1 };     //!< �Đ����̃A�j���[�V�����ԍ�
};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// .sa�f�[�^����A�j���[�V�����Ǘ��N���X,�摜�p�X�z��ɕ�������N���X
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationDataParser
{
public:

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pData">�f�[�^</param>
	/// <param name="dataLen">�f�[�^��</param>
	// ********************************************************************************
	explicit SpriteAnimationDataParser(const char* pData, std::size_t dataLen);

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationDataParser();

	// ********************************************************************************
	/// <summary>
	/// ��́A����
	/// </summary>
	/// <param name="outAnimation">�o�͐�</param>
	/// <param name="outTexturePathArray">�o�͐�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool parseFromSA(SpriteAnimationController* outAnimation, std::vector<std::string>* outTexturePathArray);

private:

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�������̉�́A����
	/// </summary>
	/// <param name="out">�o�͐�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool animationParse(SpriteAnimationController* out);

	// ********************************************************************************
	/// <summary>
	/// �p�^�[�����̉�́A����
	/// </summary>
	/// <param name="out">�o�͐�</param>
	/// <param name="index">�A�j���[�V�������f�[�^�C���f�b�N�X</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool patternParse(SpriteAnimationController * out, std::int32_t& index);

	// ********************************************************************************
	/// <summary>
	/// �摜�p�X�z����̉�́A����
	/// </summary>
	/// <param name="out">�o�͐�</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool texturePathArrayParse(std::vector<std::string>* out);

	// ********************************************************************************
	/// <summary>
	/// �f�[�^�z��̐擪����4�o�C�g����4�o�C�g�f�[�^�ɕϊ�
	/// </summary>
	/// <param name="pData">�f�[�^�z��</param>
	/// <returns>4�o�C�g�f�[�^</returns>
	// ********************************************************************************
	std::int32_t charToNum(const char* pData);

	const char*     m_pData            ;     //!< .sa�f�[�^
	std::size_t     m_DataLen     { 0 };     //!< �f�[�^��
	std::size_t     m_Index       { 0 };     //!< ����C���f�b�N�X
};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// .sa�t�@�C���ɏo�͂���N���X
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationDataExporter
{
public:

	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pName">�o�̓t�@�C���p�X</param>
	// ********************************************************************************
	explicit SpriteAnimationDataExporter(const char* pName);

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationDataExporter();

	// ********************************************************************************
	/// <summary>
	/// .sa�f�[�^�ɏo��
	/// </summary>
	/// <param name="expoortController">�o�͂���A�j���[�V�����f�[�^</param>
	/// <param name="exportTexturePathArray">�o�͂���摜�p�X�z��f�[�^</param>
	/// <returns>true : ����, false : ���s</returns>
	// ********************************************************************************
	bool exportToSA(SpriteAnimationController* expoortController, std::vector<std::string>* exportTexturePathArray);

private:

	const char*     m_pFileName;     //!< �o�̓t�@�C���p�X
};

#endif // !SPRITEANIMATION_H_
