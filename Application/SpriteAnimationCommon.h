#ifndef SPRITEANIMATIONCOMMON_H_
#define SPRITEANIMATIONCOMMON_H_

/*! 独自ヘッダ */
#define SPRITE_ANIMATION_HEADER         "SPRITE_ANIMATION_HEADER"

/*! 独自ヘッダ長 */
#define SPRITE_ANIMATION_HEADER_LEN     strlen(SPRITE_ANIMATION_HEADER)

// --------------------------------------------------------------------------------
/// <summary>
/// .saファイルデータチャンク
/// </summary>
// --------------------------------------------------------------------------------
enum class SpriteAnimationFileChunk : unsigned char
{
	Header             = 0x01, // chunk(0x01), size(SPRITE_ANIMATION_HEADER_LEN), header(SPRITE_ANIMATION_HEADER)
	TextureCount       = 0x02, // chunk(0x02), textureCount, 
	TextureData        = 0x03, // chunk(0x03), size(data size), data,
	AnimationCount     = 0x04, // chunk(0x04), animCount,
	AnimationData      = 0x05, // chunk(0x05), size(data size), data,
	Eof                = 0xFF, // chunk(0xFF)
};

// --------------------------------------------------------------------------------
/// <summary>
/// .saアニメーションデータチャンク
/// </summary>
// --------------------------------------------------------------------------------
enum class SpriteAnimationDataChunk : unsigned char
{
	Name               = 0x40, // chunk(0x40), i(array no), size(length), name,
	Loop               = 0x41, // chunk(0x41), i(array no), loop(1 byte),
	PatternCount       = 0x42, // chunk(0x42), i(array no), patternCount,
	PatternData        = 0x43, // chunk(0x43), i(array no), size(data size), data,
};

// --------------------------------------------------------------------------------
/// <summary>
/// .saスプライトデータチャンク
/// </summary>
// --------------------------------------------------------------------------------
enum class SpritePatternDataChunk : unsigned char
{
	LayerCount         = 0x60, // chunk(0x60), i(array no), j(pattern no), layerCount,
	LayerData          = 0x61, // chunk(0x61), i(array no), j(pattern no), size(data size), data,
	RefreshTime        = 0x62, // chunk(0x62), i(array no), j(pattern no), refreshTime,
};

// --------------------------------------------------------------------------------
/// <summary>
/// .saスプライトレイヤーデータチャンク
/// </summary>
// --------------------------------------------------------------------------------
enum class SpritePatternLayerDataChunk : unsigned char
{
	LayerName          = 0x80, // chunk(0x80), i(array no), j(pattern no), k(layer no), size(length), name, 
	ImageNo            = 0x81, // chunk(0x81), i(array no), j(pattern no), k(layer no), image no,
	OffsetX            = 0x82, // chunk(0x82), i(array no), j(pattern no), k(layer no), offset x,
	OffsetY            = 0x83, // chunk(0x83), i(array no), j(pattern no), k(layer no), offset y,
	Width              = 0x84, // chunk(0x84), i(array no), j(pattern no), k(layer no), width,
	Height             = 0x85, // chunk(0x85), i(array no), j(pattern no), k(layer no), height,
	DrawOffsetX        = 0x86, // chunk(0x86), i(array no), j(pattern no), k(layer no), draw offset x,
	DrawOffsetY        = 0x87, // chunk(0x87), i(array no), j(pattern no), k(layer no), draw offset y,
};

// --------------------------------------------------------------------------------
/// <summary>
/// .sa画像データチャンク
/// </summary>
// --------------------------------------------------------------------------------
enum class SpriteTextureDataChunk : unsigned char
{
	FullPath           = 0x20, // chunk(0x20), i(array no), size(length), path,
};

#endif // !SPRITEANIMATIONCOMMON_H_
