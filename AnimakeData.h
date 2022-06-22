#ifndef ANIMAKEDATA_H_
#define ANIMAKEDATA_H_

#include "Framework/Framework/Framework.h"
#include "Application/SpriteAnimation.h"

struct AnimakeData
{
	spa::SpriteAnimationController  m_SpriteAnimation{};
	std::vector<Sample::TexturePtr> m_SampleTextures{};
	std::vector<std::string>        m_TexturePathArray{};
	std::int32_t                    m_EditAnimNo{ 0 };
	std::int32_t                    m_EditPatternNo{ 0 };
	std::int32_t                    m_EditPatternLayerNo{ 0 };
	std::int32_t                    m_SelectTextureNo{ -1 };
};

using AnimakeDataPtr = std::shared_ptr<AnimakeData>;

#endif // !ANIMAKEDATA_H_
