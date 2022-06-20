#ifndef ANIMAKEDATA_H_
#define ANIMAKEDATA_H_

#include "Framework/Framework/Framework.h"
#include "Application/SpriteAnimation.h"

struct AnimakeData
{
	spa::SpriteAnimationController  m_SpriteAnimation{};
	std::vector<Sample::TexturePtr> m_SampleTextures{ 0 };
	std::vector<std::string>        m_TexturePathArray{ 0 };
	int                             m_EditAnimNo{ 0 };
	int                             m_EditPatternNo{ 0 };
	int                             m_EditPatternLayerNo{ 0 };
	int                             m_SelectTextureNo{ -1 };

	explicit AnimakeData() = default;
};

using AnimakeDataPtr = std::shared_ptr<AnimakeData>;

#endif // !ANIMAKEDATA_H_
