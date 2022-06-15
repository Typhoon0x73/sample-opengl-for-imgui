#include "SpriteAnimation.h"
#include <algorithm>
#include <cmath>

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
// ********************************************************************************
SpriteAnimation::Pattern::Pattern(const Pattern & copy)
{
	*this = copy;
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
// ********************************************************************************
SpriteAnimation::Pattern::Pattern(Pattern && move)
{
	*this = std::move(move);
}

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
SpriteAnimation::Pattern::Pattern(std::int32_t n, std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, double t, std::int32_t ox, std::int32_t oy)
	: m_ImageNo{ n }
	, m_OffsetX{ x }
	, m_OffsetY{ y }
	, m_Width{ w }
	, m_Height{ h }
	, m_RefreshTime{ t }
	, m_DrawOffsetX{ ox }
	, m_DrawOffsetY{ oy }
{
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimation::Pattern & SpriteAnimation::Pattern::operator=(const Pattern & copy)
{
	m_ImageNo     = copy.m_ImageNo    ;
	m_OffsetX     = copy.m_OffsetX    ;
	m_OffsetY     = copy.m_OffsetY    ;
	m_Width       = copy.m_Width      ;
	m_Height      = copy.m_Height     ;
	m_RefreshTime = copy.m_RefreshTime;
	m_DrawOffsetX = copy.m_DrawOffsetX;
	m_DrawOffsetY = copy.m_DrawOffsetY;
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimation::Pattern & SpriteAnimation::Pattern::operator=(SpriteAnimation::Pattern && move)
{
	m_ImageNo     = std::move(move.m_ImageNo    );
	m_OffsetX     = std::move(move.m_OffsetX    );
	m_OffsetY     = std::move(move.m_OffsetY    );
	m_Width       = std::move(move.m_Width      );
	m_Height      = std::move(move.m_Height     );
	m_RefreshTime = std::move(move.m_RefreshTime);
	m_DrawOffsetX = std::move(move.m_DrawOffsetX);
	m_DrawOffsetY = std::move(move.m_DrawOffsetY);
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator== ������r���Z
/// </summary>
/// <param name="pattern">��r�Ώ�</param>
/// <returns>true : �p�^�[���f�[�^��v, false : ��v���Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimation::Pattern::operator==(const SpriteAnimation::Pattern & pattern) const
{
	if (m_ImageNo     != pattern.m_ImageNo    ) return false;
	if (m_OffsetX     != pattern.m_OffsetX    ) return false;
	if (m_OffsetY     != pattern.m_OffsetY    ) return false;
	if (m_Width       != pattern.m_Width      ) return false;
	if (m_Height      != pattern.m_Height     ) return false;
	if (m_RefreshTime != pattern.m_RefreshTime) return false;
	if (m_DrawOffsetX != pattern.m_DrawOffsetX) return false;
	if (m_DrawOffsetY != pattern.m_DrawOffsetY) return false;
	return true;
}

// ********************************************************************************
/// <summary>
/// operator!= ��r���Z
/// </summary>
/// <param name="pattern">��r�Ώ�</param>
/// <returns>!(*this == pattern)</returns>
// ********************************************************************************
bool SpriteAnimation::Pattern::operator!=(const SpriteAnimation::Pattern & pattern) const
{
	return !(operator==(pattern));
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
// ********************************************************************************
SpriteAnimation::SpriteAnimation(const SpriteAnimation & copy)
{
	*this = copy;
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
// ********************************************************************************
SpriteAnimation::SpriteAnimation(SpriteAnimation && move)
{
	*this = std::move(move);
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="patterns">�p�^�[���z��</param>
/// <param name="hasLooped">���[�v�t���O</param>
// ********************************************************************************
SpriteAnimation::SpriteAnimation(const std::vector<SpriteAnimation::Pattern>& patterns, bool hasLooped)
	: m_PatternArray{ patterns }
	, m_hasLooped{ hasLooped }
	, m_CurrentPatternNo{ -1 }
	, m_Timer{ 0.0 }
	, m_TotalTime{ 0.0 }
{
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="patterns">�p�^�[���z��(���[�u)</param>
/// <param name="hasLooped">���[�v�t���O</param>
// ********************************************************************************
SpriteAnimation::SpriteAnimation(std::vector<SpriteAnimation::Pattern>&& patterns, bool hasLooped)
	: m_PatternArray{ std::move(patterns) }
	, m_hasLooped{ hasLooped }
	, m_CurrentPatternNo{ -1 }
	, m_Timer{ 0.0 }
	, m_TotalTime{ 0.0 }
{
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="patterns">�p�^�[���z��</param>
/// <param name="count">�p�^�[���o�^��</param>
/// <param name="hasLooped">���[�v�t���O</param>
// ********************************************************************************
SpriteAnimation::SpriteAnimation(SpriteAnimation::Pattern * patterns, std::size_t count, bool hasLooped)
	: m_PatternArray{ patterns, patterns + count }
	, m_hasLooped{ hasLooped }
	, m_CurrentPatternNo{ -1 }
	, m_Timer{ 0.0 }
	, m_TotalTime{ 0.0 }
{
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ********************************************************************************
SpriteAnimation::~SpriteAnimation()
{
	clear();
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����̍X�V
/// </summary>
/// <param name="deltaTime">�X�V����(�P�ʂ͕b)</param>
/// <returns>true : �X�V����, false : �X�V�Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimation::update(const float deltaTime)
{
	if (m_CurrentPatternNo < 0 || m_CurrentPatternNo >= (std::int32_t)m_PatternArray.size())
	{
		return false;
	}
	m_Timer += deltaTime;
	if (m_PatternArray[m_CurrentPatternNo].m_RefreshTime <= m_Timer)
	{
		m_Timer = 0.0;
		m_CurrentPatternNo++;
		const std::int32_t size = (std::int32_t)m_PatternArray.size();
		if (m_CurrentPatternNo >= size && m_hasLooped)
		{
			m_CurrentPatternNo = 0;
		}
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̒ǉ�
/// </summary>
/// <param name="pattern">�ǉ�����p�^�[���f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::addPattern(const SpriteAnimation::Pattern & pattern)
{
	m_PatternArray.push_back(pattern);
	m_TotalTime += pattern.m_RefreshTime;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̒ǉ�
/// </summary>
/// <param name="pattern">�ǉ�����p�^�[���f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::addPattern(SpriteAnimation::Pattern && pattern)
{
	m_TotalTime += pattern.m_RefreshTime;
	m_PatternArray.emplace_back(std::move(pattern));
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����z��ԍ�</param>
/// <param name="pattern">�ύX��̃p�^�[���f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setPattern(std::size_t no, const SpriteAnimation::Pattern & pattern)
{
	if (m_PatternArray.size() >= no)
	{
		return false;
	}
	m_TotalTime -= m_PatternArray[no].m_RefreshTime;
	m_PatternArray[no] = pattern;
	m_TotalTime += m_PatternArray[no].m_RefreshTime;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����z��ԍ�</param>
/// <param name="pattern">�ύX��̃p�^�[���f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setPattern(std::size_t no, SpriteAnimation::Pattern && pattern)
{
	if (m_PatternArray.size() >= no)
	{
		return false;
	}
	m_TotalTime -= m_PatternArray[no].m_RefreshTime;
	m_PatternArray[no] = std::move(pattern);
	m_TotalTime += m_PatternArray[no].m_RefreshTime;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̍폜
/// </summary>
/// <param name="no">�폜����z��ԍ�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::removePattern(std::size_t no)
{
	if (m_PatternArray.size() >= no)
	{
		return false;
	}
	m_TotalTime -= m_PatternArray[no].m_RefreshTime;
	m_PatternArray.erase(m_PatternArray.begin() + no);
	roundCurrentPatternNo();
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̍폜
/// </summary>
/// <param name="pattern">�폜����p�^�[���f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::removePattern(const SpriteAnimation::Pattern & pattern)
{
	auto size = m_PatternArray.size();
	m_PatternArray.erase(
		std::remove_if(
			m_PatternArray.begin(), m_PatternArray.end(),
			[&](const auto& it) { return (it == pattern); }),
		m_PatternArray.end()
	);
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
	roundCurrentPatternNo();
	return (size != m_PatternArray.size());
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̍폜
/// </summary>
/// <param name="pattern">�폜����p�^�[���f�[�^�̃C�e���[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::removePattern(std::vector<SpriteAnimation::Pattern>::const_iterator pattern)
{
	m_TotalTime -= pattern->m_RefreshTime;
	m_PatternArray.erase(pattern);
	roundCurrentPatternNo();
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̑S�폜
/// </summary>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::clear()
{
	m_PatternArray.clear();
	m_CurrentPatternNo =  -1;
	m_TotalTime        = 0.0;
	m_Timer            = 0.0;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���z��̕ύX
/// </summary>
/// <param name="patterns">�ύX��̃p�^�[���z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setPatternArray(const std::vector<SpriteAnimation::Pattern>& patterns)
{
	m_PatternArray = patterns;
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���z��̕ύX
/// </summary>
/// <param name="patterns">�ύX��̃p�^�[���z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setPatternArray(std::vector<SpriteAnimation::Pattern>&& patterns)
{
	m_PatternArray = std::move(patterns);
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���z��̕ύX
/// </summary>
/// <param name="patterns">�ύX��̃p�^�[���z��</param>
/// <param name="count">�ύX��̃p�^�[����</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setPatternArray(SpriteAnimation::Pattern* patterns, std::size_t count)
{
	m_PatternArray = std::vector<SpriteAnimation::Pattern>(patterns, patterns + count);
	for (const auto& pattern : m_PatternArray)
	{
		m_TotalTime += pattern.m_RefreshTime;
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����̃��[�v�ݒ�
/// </summary>
/// <param name="hasLooped">true : ���[�v����, false : ���[�v���Ȃ�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setLoop(bool hasLooped)
{
	m_hasLooped = hasLooped;
	return true;
}

// ********************************************************************************
/// <summary>
/// �Đ����p�^�[���ԍ��̕ύX
/// </summary>
/// <param name="no">�ύX��̃p�^�[���ԍ�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setCurrentPatternNo(std::int32_t no)
{
	if ((std::int32_t)m_PatternArray.size() <= no || no < 0)
	{
		m_CurrentPatternNo = -1;
		return false;
	}
	m_CurrentPatternNo = no;
	return true;
}

// ********************************************************************************
/// <summary>
/// ���Ԏw��ɂ��Đ����p�^�[���ԍ��̕ύX
/// </summary>
/// <param name="t">�Đ��������A�j���[�V�����o�ߎ���(�P�ʂ͕b)</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::setCurrentPatternNoByTime(double t)
{
	if (m_PatternArray.size() <= 0)
	{
		m_CurrentPatternNo = -1;
		return false;
	}
	m_CurrentPatternNo = patternNoByTime(t);
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���A�j���[�V�����̍Đ�
/// </summary>
/// <param name="no">�Đ��J�n�p�^�[���ԍ�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::play(std::size_t no)
{
	if (m_PatternArray.size() <= no)
	{
		m_CurrentPatternNo = -1;
		return false;
	}
    m_CurrentPatternNo = static_cast<std::int32_t>(no);
	m_Timer            = 0.0;
	return true;
}

// ********************************************************************************
/// <summary>
/// �J�n���Ԏw��ɂ��p�^�[���A�j���[�V�����̍Đ�
/// </summary>
/// <param name="t">�Đ��J�n�A�j���[�V��������(�P�ʂ͕b)</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimation::playByTime(double t)
{
	if (m_PatternArray.size() <= 0)
	{
		m_CurrentPatternNo = -1;
		return false;
	}
	m_CurrentPatternNo = patternNoByTime(t);
	m_Timer            = t;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���z��̎擾
/// </summary>
/// <returns>�p�^�[���z��|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const std::vector<SpriteAnimation::Pattern>* const SpriteAnimation::patternArray() const
{
	return &m_PatternArray;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���z��̎擾
/// </summary>
/// <returns>�p�^�[���z��|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
std::vector<SpriteAnimation::Pattern>* const SpriteAnimation::patternArray()
{
	return &m_PatternArray;
}

// ********************************************************************************
/// <summary>
/// ���Ԏw��ɂ��p�^�[���f�[�^�̎擾
/// </summary>
/// <param name="t">�擾�������A�j���[�V��������(�P�ʂ͕b)</param>
/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const SpriteAnimation::Pattern * const SpriteAnimation::patternByTime(double t) const
{
	if (m_PatternArray.size() <= 0)
	{
		return nullptr;
	}
	return &(m_PatternArray[patternNoByTime(t)]);
}

// ********************************************************************************
/// <summary>
/// ���Ԏw��ɂ��p�^�[���f�[�^�̎擾
/// </summary>
/// <param name="t">�擾�������A�j���[�V��������(�P�ʂ͕b)</param>
/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
SpriteAnimation::Pattern * const SpriteAnimation::patternByTime(double t)
{
	if (m_PatternArray.size() <= 0)
	{
		return nullptr;
	}
	return &(m_PatternArray[patternNoByTime(t)]);
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̎擾
/// </summary>
/// <param name="no">�擾�������z��ԍ�</param>
/// <returns>�p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const SpriteAnimation::Pattern * const SpriteAnimation::patternByArrayNo(std::size_t no) const
{
	if (m_PatternArray.size() >= no)
	{
		return nullptr;
	}
	return &(m_PatternArray[no]);
}

// ********************************************************************************
/// <summary>
/// �p�^�[���f�[�^�̎擾
/// </summary>
/// <param name="no">�擾�������z��ԍ�</param>
/// <returns>�p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
SpriteAnimation::Pattern * const SpriteAnimation::patternByArrayNo(std::size_t no)
{
	if (m_PatternArray.size() >= no)
	{
		return nullptr;
	}
	return &(m_PatternArray[no]);
}

// ********************************************************************************
/// <summary>
/// �Đ����̃p�^�[���f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const SpriteAnimation::Pattern * const SpriteAnimation::currentPattern() const
{
	if (m_CurrentPatternNo < 0 || m_PatternArray.size() <= 0)
	{
		return nullptr;
	}
	if (hasEnded())
	{
		return &(m_PatternArray[m_CurrentPatternNo - 1]);
	}
	return &(m_PatternArray[m_CurrentPatternNo]);
}

// ********************************************************************************
/// <summary>
/// �Đ����̃p�^�[���f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃p�^�[���f�[�^�|�C���^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
SpriteAnimation::Pattern * const SpriteAnimation::currentPattern()
{
	if (m_CurrentPatternNo < 0 || m_PatternArray.size() <= 0)
	{
		return nullptr;
	}
	if (hasEnded())
	{
		return &(m_PatternArray[m_CurrentPatternNo - 1]);
	}
	return &(m_PatternArray[m_CurrentPatternNo]);
}

// ********************************************************************************
/// <summary>
/// ���[�v�ݒ�̊m�F
/// </summary>
/// <returns>true : ���[�v����, false : ���[�v���Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimation::hasLooped() const
{
	return m_hasLooped;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�������I�����Ă��邩����(���[�v�t���O�������Ă���ΕK��false���Ԃ�)
/// </summary>
/// <returns>true : �A�j���[�V�����I��, false : �A�j���[�V������</returns>
// ********************************************************************************
bool SpriteAnimation::hasEnded() const
{
	if (m_hasLooped) return false;
	return (m_CurrentPatternNo >= (std::int32_t)m_PatternArray.size());
}

// ********************************************************************************
/// <summary>
/// ���Ԏw��ɂ��p�^�[���ԍ��̎擾
/// </summary>
/// <param name="t">�擾����������</param>
/// <returns>�w�肳�ꂽ���ԂɍĐ������p�^�[���ԍ�</returns>
// ********************************************************************************
std::int32_t SpriteAnimation::patternNoByTime(double t) const
{
	if (t == 0.0)
	{
		return 0;
	}
	const std::int32_t sign = (std::signbit(t) ? -1 : 1);
	if (!m_hasLooped)
	{
		if (t < 0.0)
		{
			return 0;
		}
		if (t >= m_TotalTime)
		{
			return static_cast<std::int32_t>(m_PatternArray.size()) - 1;
		}
	}
	else
	{
		while (std::abs(t) > m_TotalTime)
		{
			t -= m_TotalTime * sign;
		}
	}
	double countTimer = 0.0;
	const std::int32_t size = static_cast<std::int32_t>(m_PatternArray.size());
	for (int i = 0; i < size; i++)
	{
		int no = ((sign > 0) ? i : size - i - 1);
		countTimer += m_PatternArray[no].m_RefreshTime * sign;
		if (( std::signbit(t) && t <  countTimer) ||
			(!std::signbit(t) && t >= countTimer))
		{
			continue;
		}
		return no;
	}
	return 0;
}

// ********************************************************************************
/// <summary>
/// �Đ����̃p�^�[���ԍ��̎擾
/// </summary>
/// <returns>�Đ����̃p�^�[���ԍ�, -1 : �f�[�^�Ȃ�</returns>
// ********************************************************************************
std::int32_t SpriteAnimation::currentPatternNo() const
{
	return m_CurrentPatternNo;
}

// ********************************************************************************
/// <summary>
/// �p�^�[���ύX�p�^�C�}�[�̎擾
/// </summary>
/// <returns>�p�^�[�����̌o�ߎ���(�P�ʂ͕b)</returns>
// ********************************************************************************
double SpriteAnimation::timer() const
{
	return m_Timer;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����I���܂ł̍��v���Ԃ̎擾(���[�v�֌W�Ȃ��z��̍��v�`�掞�Ԃ��Ԃ�)
/// </summary>
/// <returns>�A�j���[�V�����I���܂ł̍��v����(�P�ʂ͕b)</returns>
// ********************************************************************************
double SpriteAnimation::totalTime() const
{
	return m_TotalTime;
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimation & SpriteAnimation::operator=(const SpriteAnimation & copy)
{
	m_PatternArray     = copy.m_PatternArray;
	m_hasLooped        = copy.m_hasLooped;
	m_CurrentPatternNo = copy.m_CurrentPatternNo;
	m_Timer            = copy.m_Timer;
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimation & SpriteAnimation::operator=(SpriteAnimation && move)
{
	m_PatternArray     = std::move(move.m_PatternArray);
	m_hasLooped        = move.m_hasLooped;
	m_CurrentPatternNo = move.m_CurrentPatternNo;
	m_Timer            = move.m_Timer;
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator== ������r���Z
/// </summary>
/// <param name="animation">��r�Ώ�</param>
/// <returns>true : �A�j���[�V�����f�[�^��v, false : ��v���Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimation::operator==(const SpriteAnimation & animation) const
{
    std::size_t size = m_PatternArray.size();
	if (size               != animation.m_PatternArray.size()) return false;
	if (m_hasLooped        != animation.m_hasLooped          ) return false;
	for (std::int32_t i = 0; i < size; i++)
	{
		if (m_PatternArray[i].m_ImageNo     != animation.m_PatternArray[i].m_ImageNo    ) return false;
		if (m_PatternArray[i].m_OffsetX     != animation.m_PatternArray[i].m_OffsetX    ) return false;
		if (m_PatternArray[i].m_OffsetY     != animation.m_PatternArray[i].m_OffsetY    ) return false;
		if (m_PatternArray[i].m_Width       != animation.m_PatternArray[i].m_Width      ) return false;
		if (m_PatternArray[i].m_Height      != animation.m_PatternArray[i].m_Height     ) return false;
		if (m_PatternArray[i].m_RefreshTime != animation.m_PatternArray[i].m_RefreshTime) return false;
		if (m_PatternArray[i].m_DrawOffsetX != animation.m_PatternArray[i].m_DrawOffsetX) return false;
		if (m_PatternArray[i].m_DrawOffsetY != animation.m_PatternArray[i].m_DrawOffsetY) return false;
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// operator!= ��r���Z
/// </summary>
/// <param name="animation">��r���Z</param>
/// <returns>!(*this == animation)</returns>
// ********************************************************************************
bool SpriteAnimation::operator!=(const SpriteAnimation & animation) const
{
	return !(operator==(animation));
}

// ********************************************************************************
/// <summary>
/// �����ōĐ����̃p�^�[���ԍ����ۂ߂鏈��
/// </summary>
// ********************************************************************************
void SpriteAnimation::roundCurrentPatternNo()
{
	if (m_CurrentPatternNo < 0)
	{
		return;
	}
	m_CurrentPatternNo = std::clamp(m_CurrentPatternNo, (std::int32_t)-1, (std::int32_t)m_PatternArray.size() - 1);
}

//--------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(const SpriteAnimationController & copy)
	: m_CurrentAnimationNo{ -1 }
{
	*this = copy;
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(SpriteAnimationController && move)
	: m_CurrentAnimationNo{ -1 }
{
	*this = std::move(move);
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pFile">.sa�t�@�C���p�X</param>
/// <param name="outTexturePathArray">�o�͐�摜�t�@�C���p�X�z��</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(const char * pFile, std::vector<std::string>* outTexturePathArray)
{
	std::ifstream ifs(pFile, std::ios::binary);
	if (ifs)
	{
		std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		SpriteAnimationDataParser parser(data.c_str(), data.length());
		parser.parseFromSA(this, outTexturePathArray);
	}
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pData">.sa�f�[�^</param>
/// <param name="dataLen">�f�[�^��</param>
/// <param name="outTexturePathArray">�o�͐�摜�t�@�C���p�X�z��</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(const char * pData, std::size_t dataLen, std::vector<std::string>* outTexturePathArray)
	: m_CurrentAnimationNo{ -1 }
{
	SpriteAnimationDataParser parser(pData, dataLen);
	parser.parseFromSA(this, outTexturePathArray);
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="animations">�A�j���[�V�����z��</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(const std::vector<std::pair<std::string, SpriteAnimation>>& animations)
	: m_AnimationArray{ animations }
	, m_CurrentAnimationNo{ -1 }
{
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="animations">�A�j���[�V�����z��</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(std::vector<std::pair<std::string, SpriteAnimation>>&& animations)
	: m_AnimationArray{ std::move(animations) }
	, m_CurrentAnimationNo{ -1 }
{
}

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="animations">�A�j���[�V�����z��</param>
/// <param name="count">�A�j���[�V������</param>
// ********************************************************************************
SpriteAnimationController::SpriteAnimationController(std::pair<std::string, SpriteAnimation>* animations, std::size_t count)
	: m_AnimationArray{ animations, animations + count }
	, m_CurrentAnimationNo{ -1 }
{
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ********************************************************************************
SpriteAnimationController::~SpriteAnimationController()
{
	clear();
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����̍X�V
/// </summary>
/// <param name="deltaTime">�X�V����(�P�ʂ͕b)</param>
/// <returns>true : �X�V����, false : �X�V�Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimationController::update(const float deltaTime)
{
	if (m_CurrentAnimationNo < 0 || (std::int32_t)m_AnimationArray.size() <= m_CurrentAnimationNo)
	{
		return false;
	}
	return m_AnimationArray[m_CurrentAnimationNo].second.update(deltaTime);
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="name">�A�j���[�V������</param>
/// <param name="animation">�A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(const std::string & name, const SpriteAnimation & animation)
{
	m_AnimationArray.push_back(std::make_pair(name, animation));
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="name">�A�j���[�V������</param>
/// <param name="animation">�A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(const std::string & name, SpriteAnimation && animation)
{
	m_AnimationArray.push_back(std::make_pair(name, std::move(animation)));
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="name">�A�j���[�V������</param>
/// <param name="animation">�A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(std::string && name, const SpriteAnimation & animation)
{
	m_AnimationArray.push_back(std::make_pair(std::move(name), animation));
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="name">�A�j���[�V������</param>
/// <param name="animation">�A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(std::string && name, SpriteAnimation && animation)
{
	m_AnimationArray.emplace_back(std::move(name), std::move(animation));
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="animation">�A�j���[�V�����z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(const std::pair<std::string, SpriteAnimation>& animation)
{
	m_AnimationArray.push_back(animation);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̒ǉ�
/// </summary>
/// <param name="animation">�A�j���[�V�����z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::addAnimation(std::pair<std::string, SpriteAnimation>&& animation)
{
	m_AnimationArray.emplace_back(std::move(animation));
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�������̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimationName(std::size_t no, const std::string & name)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first = name;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�������̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimationName(std::size_t no, std::string && name)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first = std::move(name);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, const SpriteAnimation & animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].second = animation;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, SpriteAnimation && animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].second = std::move(animation);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, const std::string & name, const SpriteAnimation & animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first  = name;
	m_AnimationArray[no].second = animation;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, const std::string & name, SpriteAnimation && animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first  = name;
	m_AnimationArray[no].second = std::move(animation);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, std::string && name, const SpriteAnimation & animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first  = std::move(name);
	m_AnimationArray[no].second = animation;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="name">�ύX��̖��O</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, std::string && name, SpriteAnimation && animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no].first  = std::move(name);
	m_AnimationArray[no].second = std::move(animation);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, const std::pair<std::string, SpriteAnimation>& animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no] = animation;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̕ύX
/// </summary>
/// <param name="no">�ύX����A�j���[�V�����z��ԍ�</param>
/// <param name="animation">�ύX��̃A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::size_t no, std::pair<std::string, SpriteAnimation>&& animation)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray[no] = std::move(animation);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̍폜
/// </summary>
/// <param name="no">�폜����A�j���[�V�����z��ԍ�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(std::size_t no)
{
	if (no >= m_AnimationArray.size())
	{
		return false;
	}
	m_AnimationArray.erase(m_AnimationArray.begin() + no);
	roundCurrentAnimationNo();
	return true;
}

// ********************************************************************************
/// <summary>
/// ���O�w��ŃA�j���[�V�����f�[�^�̍폜(���ꖼ�͂��ׂč폜)
/// </summary>
/// <param name="name">�폜����A�j���[�V������</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(const std::string & name)
{
	auto size = m_AnimationArray.size();
	m_AnimationArray.erase(
		std::remove_if(
			m_AnimationArray.begin(), m_AnimationArray.end(),
			[&](const auto& it) { return (it.first.compare(name) == 0); }
		), m_AnimationArray.end()
	);
	roundCurrentAnimationNo();
	return (size != m_AnimationArray.size());
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�w��ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
/// </summary>
/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(const SpriteAnimation & animation)
{
	auto size = m_AnimationArray.size();
	m_AnimationArray.erase(
		std::remove_if(
			m_AnimationArray.begin(), m_AnimationArray.end(),
			[&](const auto& it) { return (it.second == animation); }
		), m_AnimationArray.end()
	);
	roundCurrentAnimationNo();
	return (size != m_AnimationArray.size());
}

// ********************************************************************************
/// <summary>
/// [key, data]�ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
/// </summary>
/// <param name="name">�폜����A�j���[�V������</param>
/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(const std::string & name, SpriteAnimation & animation)
{
	auto size = m_AnimationArray.size();
	m_AnimationArray.erase(
		std::remove_if(
			m_AnimationArray.begin(), m_AnimationArray.end(),
			[&](const auto& it) { return ((it.first.compare(name) == 0) && (it.second == animation)); }
		), m_AnimationArray.end()
	);
	roundCurrentAnimationNo();
	return (size != m_AnimationArray.size());
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�w��ŃA�j���[�V�����f�[�^�̍폜(����f�[�^�͂��ׂč폜)
/// </summary>
/// <param name="animation">�폜����A�j���[�V�����f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(const std::pair<std::string, SpriteAnimation> & animation)
{
	auto size = m_AnimationArray.size();
	m_AnimationArray.erase(
		std::remove_if(
			m_AnimationArray.begin(), m_AnimationArray.end(),
			[&](const auto& it) { return (it == animation); }
		), m_AnimationArray.end()
	);
	roundCurrentAnimationNo();
	return (size != m_AnimationArray.size());
}

// ********************************************************************************
/// <summary>
/// �C�e���[�^�w��ŃA�j���[�V�����f�[�^�̍폜
/// </summary>
/// <param name="animation">�폜����A�j���[�V�����f�[�^�C�e���[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::removeAnimation(std::vector<std::pair<std::string, SpriteAnimation>>::const_iterator animation)
{
	m_AnimationArray.erase(animation);
	roundCurrentAnimationNo();
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����f�[�^�̑S�폜
/// </summary>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::clear()
{
	m_AnimationArray.clear();
	m_CurrentAnimationNo = -1;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����z��̕ύX
/// </summary>
/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(const std::vector<std::pair<std::string, SpriteAnimation>>& animations)
{
	m_AnimationArray = animations;
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����z��̕ύX
/// </summary>
/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::vector<std::pair<std::string, SpriteAnimation>>&& animations)
{
	m_AnimationArray = std::move(animations);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����z��̕ύX
/// </summary>
/// <param name="animations">�ύX��̃A�j���[�V�����z��</param>
/// <param name="count">�ύX��̃A�j���[�V������</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationController::setAnimation(std::pair<std::string, SpriteAnimation>* animations, std::size_t count)
{
	m_AnimationArray = std::vector<std::pair<std::string, SpriteAnimation>>(animations, animations + count);
	return true;
}

// ********************************************************************************
/// <summary>
/// �Đ��A�j���[�V�����̕ύX
/// </summary>
/// <param name="key">�ύX��̃A�j���[�V�����ԍ�</param>
/// <param name="isSamed">�Đ����̃A�j���[�V�����Ɠ���ŏ㏑�����Ȃ��t���O(false�w��œ���A�j���[�V�����ł�0����Đ�)</param>
/// <returns>true : �ύX����, false : �ύX�Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimationController::changeAnimation(std::size_t key, bool isSamed)
{
	if (key >= m_AnimationArray.size())
	{
		return false;
	}
	if (m_CurrentAnimationNo == key && isSamed)
	{
		return false;
	}
    m_CurrentAnimationNo = static_cast<std::int32_t>(key);
	m_AnimationArray[m_CurrentAnimationNo].second.play();
	return true;
}

// ********************************************************************************
/// <summary>
/// ���O�w��ōĐ��A�j���[�V�����̕ύX(���ꖼ����������ꍇ�ŏ��̃A�j���[�V�����ɂȂ�)
/// </summary>
/// <param name="key">�ύX��̃A�j���[�V������</param>
/// <param name="isSamed">�Đ����̃A�j���[�V�����Ɠ���ŏ㏑�����Ȃ��t���O(false�w��œ���A�j���[�V�����ł�0����Đ�)</param>
/// <returns>true : �ύX����, false : �ύX�Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimationController::changeAnimation(const std::string & key, bool isSamed)
{
	if (m_CurrentAnimationNo >= 0 &&
		m_AnimationArray[m_CurrentAnimationNo].first.compare(key) == 0 && isSamed)
	{
		return false;
	}
	auto size      = m_AnimationArray.size();
	bool hasFinded = false;
	for (std::size_t i = 0; i < size; ++i)
	{
		if (m_AnimationArray[i].first.compare(key) != 0)
		{
			continue;
		}
        m_CurrentAnimationNo = static_cast<std::int32_t>(i);
		hasFinded            = true;
		break;
	}
	if (!hasFinded)
	{
		return false;
	}
	m_AnimationArray[m_CurrentAnimationNo].second.play();
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����z��̎擾
/// </summary>
/// <returns>�A�j���[�V�����z��, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const std::vector<std::pair<std::string, SpriteAnimation>>* const SpriteAnimationController::animationArray() const
{
	return &m_AnimationArray;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�����z��̎擾
/// </summary>
/// <returns>�A�j���[�V�����z��, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
std::vector<std::pair<std::string, SpriteAnimation>>* const SpriteAnimationController::animationArray()
{
	return &m_AnimationArray;
}

// ********************************************************************************
/// <summary>
/// �Đ����̃A�j���[�V�����f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃A�j���[�V�����f�[�^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const SpriteAnimation * const SpriteAnimationController::currentAnimation() const
{
	if (m_CurrentAnimationNo < 0)
	{
		return nullptr;
	}
	return &(m_AnimationArray[m_CurrentAnimationNo].second);
}

// ********************************************************************************
/// <summary>
/// �Đ����̃A�j���[�V�����f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃A�j���[�V�����f�[�^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
SpriteAnimation * const SpriteAnimationController::currentAnimation()
{
	if (m_CurrentAnimationNo < 0)
	{
		return nullptr;
	}
	return &(m_AnimationArray[m_CurrentAnimationNo].second);
}

// ********************************************************************************
/// <summary>
/// �Đ����̃p�^�[���f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃p�^�[���f�[�^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const SpriteAnimation::Pattern * const SpriteAnimationController::currentPattern() const
{
	if (m_CurrentAnimationNo < 0)
	{
		return nullptr;
	}
	return m_AnimationArray[m_CurrentAnimationNo].second.currentPattern();
}

// ********************************************************************************
/// <summary>
/// �Đ����̃p�^�[���f�[�^�̎擾
/// </summary>
/// <returns>�Đ����̃p�^�[���f�[�^, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
SpriteAnimation::Pattern * const SpriteAnimationController::currentPattern()
{
	if (m_CurrentAnimationNo < 0)
	{
		return nullptr;
	}
	return m_AnimationArray[m_CurrentAnimationNo].second.currentPattern();
}

// ********************************************************************************
/// <summary>
/// �Đ����̃A�j���[�V�������̎擾
/// </summary>
/// <returns>�Đ����̃A�j���[�V������, nullptr : �f�[�^�Ȃ�</returns>
// ********************************************************************************
const std::string * const SpriteAnimationController::currentAnimationName() const
{
	if (m_CurrentAnimationNo < 0)
	{
		return nullptr;
	}
	return &(m_AnimationArray[m_CurrentAnimationNo].first);
}

// ********************************************************************************
/// <summary>
/// �Đ����̃A�j���[�V�����ԍ��̎擾
/// </summary>
/// <returns>�Đ����̃A�j���[�V�����ԍ�, -1 : �f�[�^�Ȃ�</returns>
// ********************************************************************************
std::int32_t SpriteAnimationController::currentAnimationNo() const
{
	return m_CurrentAnimationNo;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�������̎擾
/// </summary>
/// <returns>�A�j���[�V������</returns>
// ********************************************************************************
std::size_t SpriteAnimationController::animationCount() const
{
	return m_AnimationArray.size();
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="copy">�R�s�[�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimationController & SpriteAnimationController::operator=(const SpriteAnimationController & copy)
{
	m_AnimationArray     = copy.m_AnimationArray;
	m_CurrentAnimationNo = copy.m_CurrentAnimationNo;
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator= ������Z
/// </summary>
/// <param name="move">���[�u�f�[�^</param>
/// <returns>*this</returns>
// ********************************************************************************
SpriteAnimationController & SpriteAnimationController::operator=(SpriteAnimationController && move)
{
	m_AnimationArray     = std::move(move.m_AnimationArray);
	m_CurrentAnimationNo = std::move(move.m_CurrentAnimationNo);
	return *this;
}

// ********************************************************************************
/// <summary>
/// operator== ������r���Z
/// </summary>
/// <param name="controller">��r�Ώ�</param>
/// <returns>true : ��v, false : ��v���Ȃ�</returns>
// ********************************************************************************
bool SpriteAnimationController::operator==(const SpriteAnimationController & controller) const
{
	const std::size_t size = controller.m_AnimationArray.size();
	if (m_AnimationArray.size() != size)
	{
		return false;
	}
	for (std::size_t i = 0; i < size; ++i)
	{
		if (m_AnimationArray[i].first.compare(controller.m_AnimationArray[i].first) != 0)
		{
			return false;
		}
		if (m_AnimationArray[i].second != controller.m_AnimationArray[i].second)
		{
			return false;
		}
	}
	return true;
}

// ********************************************************************************
/// <summary>
/// operator!= ��r���Z
/// </summary>
/// <param name="controller">��r�Ώ�</param>
/// <returns>!(*this == controller)</returns>
// ********************************************************************************
bool SpriteAnimationController::operator!=(const SpriteAnimationController & controller) const
{
	return !(operator==(controller));
}

// ********************************************************************************
/// <summary>
/// �����ōĐ����̃A�j���[�V�����ԍ����ۂ߂鏈��
/// </summary>
// ********************************************************************************
void SpriteAnimationController::roundCurrentAnimationNo()
{
	if (m_CurrentAnimationNo < 0)
	{
		return;
	}
	m_CurrentAnimationNo = std::clamp(m_CurrentAnimationNo, (std::int32_t)-1, (std::int32_t)m_AnimationArray.size() - 1);
}

//--------------------------------------------------------------------------------------

#include "SpriteAnimationCommon.h"

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pData">�f�[�^</param>
/// <param name="dataLen">�f�[�^��</param>
// ********************************************************************************
SpriteAnimationDataParser::SpriteAnimationDataParser(const char * pData, std::size_t dataLen)
	: m_pData{ pData }
	, m_DataLen{ dataLen }
	, m_Index{ 0 }
{
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ********************************************************************************
SpriteAnimationDataParser::~SpriteAnimationDataParser()
{
}

// ********************************************************************************
/// <summary>
/// ��́A����
/// </summary>
/// <param name="outAnimation">�o�͐�</param>
/// <param name="outTexturePathArray">�o�͐�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationDataParser::parseFromSA(SpriteAnimationController * outAnimation, std::vector<std::string>* outTexturePathArray)
{
	if (outTexturePathArray == nullptr ||
		outAnimation        == nullptr ||
		m_pData             == nullptr ||
		m_DataLen           <= 0)
	{
		return false;
	}

	do
	{
		SpriteAnimationFileChunk chunk = static_cast<SpriteAnimationFileChunk>(m_pData[m_Index]);
		m_Index += sizeof(SpriteAnimationFileChunk);
		switch (chunk)
		{
		case SpriteAnimationFileChunk::Header:
		{
			std::int32_t size = charToNum(&(m_pData[m_Index]));
			if (size <= 0)
			{
				return false;
			}
			m_Index += sizeof(std::int32_t);
			char* header = new char[size + 1];
			memcpy_s(header, size + 1, &(m_pData[m_Index]), size);
			header[size] = '\0';
			delete[] header;
			m_Index += size;
			break;
		}
		case SpriteAnimationFileChunk::TextureCount:
		{
			std::int32_t textureCount = charToNum(&(m_pData[m_Index]));
			outTexturePathArray->resize(textureCount);
			m_Index += sizeof(std::int32_t);
			break;
		}
		case SpriteAnimationFileChunk::TextureData:
		{
			if (!texturePathArrayParse(outTexturePathArray))
			{
				return false;
			}
			break;
		}
		case SpriteAnimationFileChunk::AnimationCount:
		{
			std::int32_t animationCount = charToNum(&(m_pData[m_Index]));
			outAnimation->animationArray()->resize(animationCount);
			m_Index += sizeof(std::int32_t);
			break;
		}
		case SpriteAnimationFileChunk::AnimationData:
		{
			if (!animationParse(outAnimation))
			{
				return false;
			}
			break;
		}
		case SpriteAnimationFileChunk::Eof:
		{
			break;
		}
		default:
		{
			return false;
		}
		}
	} while (m_Index < m_DataLen);
	return true;
}

// ********************************************************************************
/// <summary>
/// �A�j���[�V�������̉�́A����
/// </summary>
/// <param name="out">�o�͐�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationDataParser::animationParse(SpriteAnimationController * out)
{
	std::int32_t dataSize = charToNum(&(m_pData[m_Index]));
	m_Index += sizeof(std::int32_t);
	for (std::int32_t index = 0; index < dataSize;)
	{
		SpriteAnimationDataChunk chunk = static_cast<SpriteAnimationDataChunk>(m_pData[m_Index + index]);
		index += sizeof(SpriteAnimationDataChunk);
		switch (chunk)
		{
		case SpriteAnimationDataChunk::Name:
		{
			std::int32_t no     = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			std::int32_t length = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			std::get<std::string>(out->animationArray()->at(no)).assign(&(m_pData[m_Index + index]), &(m_pData[m_Index + index + length]));
			index += length;
			break;
		}
		case SpriteAnimationDataChunk::Loop:
		{
			std::int32_t no   = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			bool         loop = (m_pData[m_Index + index] == 0x01);     index += sizeof(char);
			out->animationArray()->at(no).second.setLoop(loop);
			break;
		}
		case SpriteAnimationDataChunk::PatternCount:
		{
			std::int32_t no   = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			std::int32_t size = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(no).second.patternArray()->resize(size);
			break;
		}
		case SpriteAnimationDataChunk::PatternData:
		{
			std::int32_t animNo = charToNum(&(m_pData[m_Index])); index += sizeof(std::int32_t);
			if (!patternParse(out, index))
			{
				return false;
			}
			break;
		}
		default: return false;
		}
	}
	m_Index += dataSize;
	return true;
}

// ********************************************************************************
/// <summary>
/// �p�^�[�����̉�́A����
/// </summary>
/// <param name="out">�o�͐�</param>
/// <param name="index">�A�j���[�V�������f�[�^�C���f�b�N�X</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationDataParser::patternParse(SpriteAnimationController * out, std::int32_t& in)
{
	std::int32_t dataSize = charToNum(&(m_pData[m_Index + in]));
	in += sizeof(std::int32_t);
	for (std::int32_t index = 0; index < dataSize;)
	{
		SpritePatternDataChunk chunk = static_cast<SpritePatternDataChunk>(m_pData[m_Index + in + index]);
		index += sizeof(SpritePatternDataChunk);
		switch (chunk)
		{
		case SpritePatternDataChunk::ImageNo:
		{
			std::int32_t animNo    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t imageNo   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_ImageNo = imageNo;
			break;
		}
		case SpritePatternDataChunk::OffsetX:
		{
			std::int32_t animNo    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t offsetX   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_OffsetX = offsetX;
			break;
		}
		case SpritePatternDataChunk::OffsetY:
		{
			std::int32_t animNo    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t offsetY   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_OffsetY = offsetY;
			break;
		}
		case SpritePatternDataChunk::Width:
		{
			std::int32_t animNo    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t width     = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_Width = width;
			break;
		}
		case SpritePatternDataChunk::Height:
		{
			std::int32_t animNo    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t height    = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_Height = height;
			break;
		}
		case SpritePatternDataChunk::RefreshTime:
		{
			std::int32_t animNo      = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t refreshTime = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_RefreshTime = refreshTime * 0.001;
			break;
		}
		case SpritePatternDataChunk::DrawOffsetX:
		{
			std::int32_t animNo      = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t drawOffsetX = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_DrawOffsetX = drawOffsetX;
			break;
		}
		case SpritePatternDataChunk::DrawOffsetY:
		{
			std::int32_t animNo      = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t patternNo   = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			std::int32_t drawOffsetY = charToNum(&(m_pData[m_Index + in + index])); index += sizeof(std::int32_t);
			out->animationArray()->at(animNo).second.patternArray()->at(patternNo).m_DrawOffsetY = drawOffsetY;
			break;
		}
		default: return false;
		}
	}
	in += dataSize;
	return true;
}

// ********************************************************************************
/// <summary>
/// �摜�p�X�z����̉�́A����
/// </summary>
/// <param name="out">�o�͐�</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationDataParser::texturePathArrayParse(std::vector<std::string>* out)
{
	std::int32_t dataSize = charToNum(&(m_pData[m_Index]));
	m_Index += sizeof(std::int32_t);
	for (std::int32_t index = 0; index < dataSize;)
	{
		SpriteTextureDataChunk chunk = static_cast<SpriteTextureDataChunk>(m_pData[m_Index + index]);
		index += sizeof(SpriteTextureDataChunk);
		switch (chunk)
		{
		case SpriteTextureDataChunk::FullPath:
		{
			std::int32_t no     = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			std::int32_t length = charToNum(&(m_pData[m_Index + index])); index += sizeof(std::int32_t);
			out->at(no).assign(&(m_pData[m_Index + index]), &(m_pData[m_Index + index + length]));
			index += length;
			break;
		}
		default: return false;
		}
	}
	m_Index += dataSize;
	return true;
}

// ********************************************************************************
/// <summary>
/// �f�[�^�z��̐擪����4�o�C�g����4�o�C�g�f�[�^�ɕϊ�
/// </summary>
/// <param name="pData">�f�[�^�z��</param>
/// <returns>4�o�C�g�f�[�^</returns>
// ********************************************************************************
std::int32_t SpriteAnimationDataParser::charToNum(const char * pData)
{
	std::int32_t result = 0;
	result |= static_cast<unsigned char>(pData[0]) <<  0;
	result |= static_cast<unsigned char>(pData[1]) <<  8;
	result |= static_cast<unsigned char>(pData[2]) << 16;
	result |= static_cast<unsigned char>(pData[3]) << 24;
	return result;
}

//--------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "SpriteAnimationCommon.h"

// ********************************************************************************
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pName">�o�̓t�@�C���p�X</param>
// ********************************************************************************
SpriteAnimationDataExporter::SpriteAnimationDataExporter(const char * pName)
	: m_pFileName { pName }
{
}

// ********************************************************************************
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ********************************************************************************
SpriteAnimationDataExporter::~SpriteAnimationDataExporter()
{
}

// ********************************************************************************
/// <summary>
/// .sa�f�[�^�ɏo��
/// </summary>
/// <param name="expoortController">�o�͂���A�j���[�V�����f�[�^</param>
/// <param name="exportTexturePathArray">�o�͂���摜�p�X�z��f�[�^</param>
/// <returns>true : ����, false : ���s</returns>
// ********************************************************************************
bool SpriteAnimationDataExporter::exportToSA(SpriteAnimationController * expoortController, std::vector<std::string>* exportTexturePathArray)
{
	std::ofstream ofs(m_pFileName, std::ios::binary);
	if (!ofs)
	{
		return false;
	}

	SpriteAnimationFileChunk chunk  = SpriteAnimationFileChunk::Header;
	std::int32_t             size   = SPRITE_ANIMATION_HEADER_LEN;
	std::string              header = SPRITE_ANIMATION_HEADER;
	ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
	ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));
	ofs.write(header.c_str(), size);
	
	const std::size_t textureCount = exportTexturePathArray->size();
	chunk  = SpriteAnimationFileChunk::TextureCount;
	ofs.write(reinterpret_cast<const char*>(&chunk       ), sizeof(chunk       ));
	ofs.write(reinterpret_cast<const char*>(&textureCount), sizeof(textureCount));
	
	chunk  = SpriteAnimationFileChunk::TextureData;
	size   = 0;
	std::for_each(exportTexturePathArray->begin(), exportTexturePathArray->end(), [&](const std::string& path)
	{
		size += sizeof(SpriteTextureDataChunk::FullPath);
		size += sizeof(std::int32_t);
		size += sizeof(std::int32_t);
		size += path.length();
	});
	ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
	ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));
	for (std::int32_t i = 0; i < static_cast<std::int32_t>(textureCount); i++)
	{
		SpriteTextureDataChunk chunk = SpriteTextureDataChunk::FullPath;
		size = (*exportTexturePathArray)[i].length();
		ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
		ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
		ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));
		ofs.write((*exportTexturePathArray)[i].c_str(), size);
	}

	const auto&       animations = expoortController->animationArray();
	const std::size_t animCount  = animations->size();
	chunk = SpriteAnimationFileChunk::AnimationCount;
	ofs.write(reinterpret_cast<const char*>(&chunk    ), sizeof(chunk    ));
	ofs.write(reinterpret_cast<const char*>(&animCount), sizeof(animCount));

	chunk = SpriteAnimationFileChunk::AnimationData;
	size  = 0;
	std::for_each(animations->begin(), animations->end(), [&](const auto& anim)
	{
		size += sizeof(SpriteAnimationDataChunk::Name);
		size += sizeof(std::int32_t);
		size += sizeof(std::int32_t);
		size += anim.first.length();

		size += sizeof(SpriteAnimationDataChunk::Loop);
		size += sizeof(std::int32_t);
		size += sizeof(char);

		const std::size_t patternCount = anim.second.patternArray()->size();
		const std::size_t dataSize     = sizeof(std::int32_t) + sizeof(std::int32_t) + sizeof(std::int32_t);
		size +=  sizeof(SpriteAnimationDataChunk::PatternCount);
		size +=  sizeof(std::int32_t);
		size +=  sizeof(std::int32_t);
		size += (sizeof(SpriteAnimationDataChunk::PatternData) + sizeof(std::int32_t) + sizeof(std::int32_t));
		size += (sizeof(SpritePatternDataChunk::ImageNo      ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::OffsetX      ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::OffsetY      ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::Width        ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::Height       ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::RefreshTime  ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::DrawOffsetX  ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::DrawOffsetY  ) + dataSize) * patternCount;
	});
	ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
	ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));
	for (std::int32_t i = 0; i < static_cast<std::int32_t>(animCount); i++)
	{
		const auto& anim = animations->at(i);
		SpriteAnimationDataChunk chunk = SpriteAnimationDataChunk::Name;
		size = anim.first.length();
		ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
		ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
		ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));
		ofs.write(anim.first.c_str(), size);

		chunk = SpriteAnimationDataChunk::Loop;
		const char loop = (anim.second.hasLooped() ? 0x01 : 0x00);
		ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
		ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
		ofs.write(reinterpret_cast<const char*>(&loop ), sizeof(loop ));

		std::size_t patternCount = anim.second.patternArray()->size();
		chunk = SpriteAnimationDataChunk::PatternCount;
		ofs.write(reinterpret_cast<const char*>(&chunk       ), sizeof(chunk       ));
		ofs.write(reinterpret_cast<const char*>(&i           ), sizeof(i           ));
		ofs.write(reinterpret_cast<const char*>(&patternCount), sizeof(patternCount));

		const std::size_t dataSize = sizeof(std::int32_t) + sizeof(std::int32_t) + sizeof(std::int32_t);
		chunk = SpriteAnimationDataChunk::PatternData;
		size  = 0;
		size += (sizeof(SpritePatternDataChunk::ImageNo    ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::OffsetX    ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::OffsetY    ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::Width      ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::Height     ) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::RefreshTime) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::DrawOffsetX) + dataSize) * patternCount;
		size += (sizeof(SpritePatternDataChunk::DrawOffsetY) + dataSize) * patternCount;
		ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
		ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
		ofs.write(reinterpret_cast<const char*>(&size ), sizeof(size ));

		for(std::int32_t j = 0; j < static_cast<std::int32_t>(patternCount); j++)
		{
			const auto&            pattern  = anim.second.patternArray()->at(j);
			const std::size_t      dataSize = sizeof(std::int32_t);
			SpritePatternDataChunk chunk    = SpritePatternDataChunk::ImageNo;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_ImageNo)), dataSize);

			chunk = SpritePatternDataChunk::OffsetX;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_OffsetX)), dataSize);

			chunk = SpritePatternDataChunk::OffsetY;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_OffsetY)), dataSize);

			chunk = SpritePatternDataChunk::Width;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_Width)), dataSize);

			chunk = SpritePatternDataChunk::Height;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_Height)), dataSize);

			std::int32_t refreshTime = static_cast<std::int32_t>(pattern.m_RefreshTime * 1000);
			chunk = SpritePatternDataChunk::RefreshTime;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&refreshTime), dataSize);

			chunk = SpritePatternDataChunk::DrawOffsetX;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_DrawOffsetX)), dataSize);

			chunk = SpritePatternDataChunk::DrawOffsetY;
			ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
			ofs.write(reinterpret_cast<const char*>(&i    ), sizeof(i    ));
			ofs.write(reinterpret_cast<const char*>(&j    ), sizeof(j    ));
			ofs.write(reinterpret_cast<const char*>(&(pattern.m_DrawOffsetY)), dataSize);
		}
	}

	chunk = SpriteAnimationFileChunk::Eof;
	ofs.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
	return true;
}
