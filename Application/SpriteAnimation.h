#ifndef SPRITEANIMATION_H_
#define SPRITEANIMATION_H_

#include <vector>
#include <string>
#include <utility>
#include <cstdint>

class SpriteAnimation
{
public:

	struct Pattern
	{
		std::int32_t        m_ImageNo         {  -1 };
		std::int32_t        m_OffsetX         {   0 };
		std::int32_t        m_OffsetY         {   0 };
		std::int32_t        m_Width           {   0 };
		std::int32_t        m_Height          {   0 };
		double              m_RefreshTime     { 0.0 };
		std::int32_t        m_DrawOffsetX     {   0 };
		std::int32_t        m_DrawOffsetY     {   0 };

		explicit Pattern() = default;
		explicit Pattern(const Pattern& copy);
		explicit Pattern(Pattern&& move);
		explicit Pattern(std::int32_t n, std::int32_t x, std::int32_t y,
			std::int32_t w, std::int32_t h, double t, std::int32_t ox, std::int32_t oy);

		SpriteAnimation::Pattern& operator=(const SpriteAnimation::Pattern& copy);
		SpriteAnimation::Pattern& operator=(SpriteAnimation::Pattern&& move);
		bool operator==(const SpriteAnimation::Pattern& pattern) const;
		bool operator!=(const SpriteAnimation::Pattern& pattern) const;
	};

public:

	explicit SpriteAnimation() = default;
	explicit SpriteAnimation(const SpriteAnimation& copy);
	explicit SpriteAnimation(SpriteAnimation&& move);
	explicit SpriteAnimation(const std::vector<SpriteAnimation::Pattern>& patterns, bool hasLooped);
	explicit SpriteAnimation(std::vector<SpriteAnimation::Pattern>&& patterns, bool hasLooped);
	explicit SpriteAnimation(SpriteAnimation::Pattern* patterns, std::size_t count, bool hasLooped);
	virtual ~SpriteAnimation();

	bool update(const float deltaTime);

	bool addPattern(const SpriteAnimation::Pattern& pattern);
	bool addPattern(SpriteAnimation::Pattern&& pattern);
	bool setPattern(std::size_t no, const SpriteAnimation::Pattern& pattern);
	bool setPattern(std::size_t no, SpriteAnimation::Pattern&& pattern);
	bool removePattern(std::size_t no);
	bool removePattern(const SpriteAnimation::Pattern& pattern);
	bool removePattern(std::vector<SpriteAnimation::Pattern>::const_iterator pattern);
	bool clear();

	bool setPatternArray(const std::vector<SpriteAnimation::Pattern>& patterns);
	bool setPatternArray(std::vector<SpriteAnimation::Pattern>&& patterns);
	bool setPatternArray(SpriteAnimation::Pattern* patterns, std::size_t count);
	bool setLoop(bool hasLooped);
	bool setCurrentPatternNo(std::int32_t no);
	bool setCurrentPatternNoByTime(double t);
	bool play(std::size_t no = 0);
	
	const std::vector<SpriteAnimation::Pattern>* const patternArray() const;
	std::vector<SpriteAnimation::Pattern>* const patternArray();
	const SpriteAnimation::Pattern* const patternByTime(double t) const;
	SpriteAnimation::Pattern* const patternByTime(double t);
	const SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no) const;
	SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no);
	const SpriteAnimation::Pattern* const currentPattern() const;
	SpriteAnimation::Pattern* const currentPattern();
	bool hasLooped() const;
	bool hasEnded() const;
	std::int32_t patternNoByTime(double t) const;
	std::int32_t currentPatternNo() const;
	double timer() const;
	double totalTime() const;

	SpriteAnimation& operator=(const SpriteAnimation& copy);
	SpriteAnimation& operator=(SpriteAnimation&& move);
	bool operator==(const SpriteAnimation& animation) const;
	bool operator!=(const SpriteAnimation& animation) const;

private:

	void roundCurrentPatternNo();

	std::vector<Pattern>     m_PatternArray         {     0 };
	bool                     m_hasLooped            { false };
	std::int32_t             m_CurrentPatternNo     {    -1 };
	double                   m_Timer                {   0.0 };
	double                   m_TotalTime            {   0.0 };

};

//--------------------------------------------------------------------------------------

class SpriteAnimationController
{
public:

	explicit SpriteAnimationController() = default;
	explicit SpriteAnimationController(const SpriteAnimationController& copy);
	explicit SpriteAnimationController(SpriteAnimationController&& move);
	explicit SpriteAnimationController(const char* pFile, std::vector<std::string>* outTexturePathArray);
	explicit SpriteAnimationController(const char* pData, std::size_t dataLen, std::vector<std::string>* outTexturePathArray);
	explicit SpriteAnimationController(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);
	explicit SpriteAnimationController(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);
	explicit SpriteAnimationController(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);
	virtual ~SpriteAnimationController();

	bool update(const float deltaTime);

	bool addAnimation(const std::string& name, const SpriteAnimation& animation);
	bool addAnimation(const std::string& name, SpriteAnimation&& animation);
	bool addAnimation(std::string&& name, const SpriteAnimation& animation);
	bool addAnimation(std::string&& name, SpriteAnimation&& animation);
	bool addAnimation(const std::pair<std::string, SpriteAnimation>& animation);
	bool addAnimation(std::pair<std::string, SpriteAnimation>&& animation);
	bool setAnimation(std::size_t no, const std::string& name, const SpriteAnimation& animation);
	bool setAnimation(std::size_t no, const std::string& name, SpriteAnimation&& animation);
	bool setAnimation(std::size_t no, std::string&& name, const SpriteAnimation& animation);
	bool setAnimation(std::size_t no, std::string&& name, SpriteAnimation&& animation);
	bool setAnimation(std::size_t no, const std::pair<std::string, SpriteAnimation>& animation);
	bool setAnimation(std::size_t no, std::pair<std::string, SpriteAnimation>&& animation);
	bool removeAnimation(std::size_t no);
	bool removeAnimation(const std::string& name);
	bool removeAnimation(const SpriteAnimation& animation);
	bool removeAnimation(const std::string& name, SpriteAnimation& animation);
	bool removeAnimation(const std::pair<std::string, SpriteAnimation>& animation);
	bool removeAnimation(std::vector<std::pair<std::string, SpriteAnimation>>::const_iterator animation);
	bool clear();

	bool setAnimation(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);
	bool setAnimation(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);
	bool setAnimation(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);

	bool changeAnimation(std::size_t key, bool isSamed = true);
	bool changeAnimation(const std::string& key, bool isSamed = true);

	const std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray() const;
	std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray();
	const SpriteAnimation* const currentAnimation() const;
	SpriteAnimation* const currentAnimation();
	const SpriteAnimation::Pattern* const currentPattern() const;
	SpriteAnimation::Pattern* const currentPattern();
	const std::string* const currentAnimationName() const;
	std::int32_t currentAnimationNo() const;
	std::size_t animationCount() const;

	SpriteAnimationController& operator=(const SpriteAnimationController& copy);
	SpriteAnimationController& operator=(SpriteAnimationController&& move);
	bool operator==(const SpriteAnimationController& controller) const;
	bool operator!=(const SpriteAnimationController& controller) const;

private:

	void roundCurrentAnimationNo();

	std::vector<std::pair<std::string, SpriteAnimation>>     m_AnimationArray         {  0 };
	std::int32_t                                             m_CurrentAnimationNo     { -1 };
};

//--------------------------------------------------------------------------------------

class SpriteAnimationDataParser
{
public:

	explicit SpriteAnimationDataParser(const char* pData, std::size_t dataLen);
	virtual ~SpriteAnimationDataParser();

	bool parseFromSA(SpriteAnimationController* outAnimation, std::vector<std::string>* outTexturePathArray);

private:

	bool animationParse(SpriteAnimationController* out);
	bool patternParse(SpriteAnimationController * out);
	bool texturePathArrayParse(std::vector<std::string>* out);

	std::int32_t charToNum(const char* pData);

	const char*     m_pData            ;
	std::size_t     m_DataLen     { 0 };
	std::size_t     m_Index       { 0 };
};

//--------------------------------------------------------------------------------------

class SpriteAnimationDataExporter
{
public:

	explicit SpriteAnimationDataExporter(const char* pName);
	virtual ~SpriteAnimationDataExporter();

	bool exportToSA(SpriteAnimationController* expoortController, std::vector<std::string>* exportTexturePathArray);

private:

	const char*     m_pFileName;
};

#endif // !SPRITEANIMATION_H_
