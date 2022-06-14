#ifndef SPRITEANIMATIONCOMMON_H_
#define SPRITEANIMATIONCOMMON_H_

#define SPRITE_ANIMATION_HEADER         "SPRITE_ANIMATION_HEADER"
#define SPRITE_ANIMATION_HEADER_LEN     strlen(SPRITE_ANIMATION_HEADER)

enum class SpriteAnimationFileChunk : unsigned char
{
	Header             = 0x01,
	AnimationCount     = 0x02,
	AnimationData      = 0x03,
	TextureCount       = 0x04,
	TextureData        = 0x05,
	Eof                = 0xFF,
};

enum class SpriteAnimationDataChunk : unsigned char
{
	Name               = 0x01,
	Loop               = 0x02,
	PatternCount       = 0x03,
	PatternData        = 0x04,
};

enum class SpritePatternDataChunk : unsigned char
{
	ImageNo            = 0x01,
	OffsetX            = 0x02,
	OffsetY            = 0x03,
	Width              = 0x04,
	Height             = 0x05,
	RefreshTime        = 0x06,
	DrawOffsetX        = 0x07,
	DrawOffsetY        = 0x08,
};

enum class SpriteTextureDataChunk : unsigned char
{
	FullPath           = 0x01,
};

#endif // !SPRITEANIMATIONCOMMON_H_
