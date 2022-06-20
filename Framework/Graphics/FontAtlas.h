#pragma once

#include	"Font.h"
#include	"Texture.h"

namespace Sample {

	/**
	 * @brief		フォントを扱うためのクラス
	 */
	class FontAtlas : public ResourceBase
	{
	protected:
		/** 利用するフォント */
		FontPtr			font_;

		/** 利用するテクスチャ */
		TexturePtr		texture_;

		/** 書き込みオフセット位置 */
		int				destOffsetX;
		/** 書き込みオフセット位置 */
		int				destOffsetY;

		/** 切り抜きマップ */
		using SliceMap = std::map<std::string, RectangleF>;
		SliceMap		slices_;

		/**
		 * @brief		コードの文字成否判断
		 * @return		true		OK
		 *				false		NO
		 */
		bool IsCodeValid(const char s) {
			return !(s == ' ' || s == '\t' || s == '\n' || s == '\r' || s == '\0');
		}
	public:
		/**
		 * @brief		コンストラクタ
		 */
		FontAtlas()
			: ResourceBase()
			, font_()
			, texture_()
			, destOffsetX(0)
			, destOffsetY(0) {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~FontAtlas() {
		}

		/**
		 * @brief		生成
		 * @param[in]	fontface	読み込むフォントファイル名
		 * @param[in]	fontsize	フォントサイズ
		 * @param[in]	texsize		テクスチャサイズ
		 * @return		true		生成成功
		 *				false		生成失敗
		 */
		bool Create(const char* fontface, const uint32_t fontsize, const int texsize) {
			//フォント生成
			font_ = std::make_shared<Sample::Font>();
			if (!font_->Create(fontface, fontsize))
			{
				return false;
			}
			//テクスチャ生成
			texture_ = std::make_shared<Sample::Texture>();
			if (!texture_->Create(texsize, texsize, Texture::FormatType::R8G8B8A8))
			{
				return false;
			}
			return true;
		}

		/**
		 * @brief		アトラスの追加
		 * @param[in]	str			追加する文字列
		 * @return		true		生成成功
		 *				false		生成失敗
		 */
		bool Add(const char* str)
		{
			size_t len = strlen(str);
			for (size_t i = 0; i < len; i++)
			{
				char text[3] = { 0 };
				uint32_t t = 0;
				if (IsDBCSLeadByte(str[i]))
				{
					wchar_t wstr[2];
					MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &str[i], 2, wstr, 2);
					t = wstr[0];
					text[0] = str[i]; text[1] = str[i + 1];
					i++;
				}
				else
				{
					//半角スペース、タブ、改行などの文字はアトラスには無視
					if (!IsCodeValid(str[i]))
					{
						continue;
					}
					t = str[i];
					text[0] = str[i];
				}
				if (destOffsetX + (std::int32_t)font_->Size() >= texture_->Width())
				{
					destOffsetX = 0;
					destOffsetY += font_->Size();
					if (destOffsetY + (std::int32_t)font_->Size() >= texture_->Height())
					{
						ERROR_LOG("Atlas Size Over!!");
						return false;
					}
				}
				//Fontから取得
				auto img = font_->CreateCodeBitmap(t);
				if (img == nullptr)
				{
					continue;
				}
				//データをRGPAの形式に変更
				uint8_t* b4Pixels = new uint8_t[img->width * img->height * 4];
				for (int y = 0; y < img->height; y++)
				{
					for (int x = 0; x < img->width; x++)
					{
						b4Pixels[(y * img->width + x) * 4 + 0] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 1] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 2] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 3] = img->pixels[y * img->width + x];
					}
				}
				//テクスチャに転送
				texture_->SubData(destOffsetX + img->offsetX, destOffsetY + img->offsetY, img->width, img->height, b4Pixels);
				//マップに登録
				slices_[text] = RectangleF((float)destOffsetX, (float)destOffsetY, (float)destOffsetX + img->offsetX + img->width, (float)destOffsetY + img->offsetY + img->height);
				delete[] b4Pixels;
				//次の書き込み場所へ
				destOffsetX += font_->Size();
			}
			return true;
		}

		/**
		 * @brief		Font_へのAccessor
		 * @return		フォント
		 */
		const FontPtr Font(void) const { return font_; }

		/**
		 * @brief		Texture_へのAccessor
		 * @return		テクスチャ
		 */
		const TexturePtr Texture(void) const { return texture_; }

		/**
		 * @brief		Slices_へのAccessor
		 * @return		切り抜きマップ
		 */
		const SliceMap& Slices(void) const { return slices_; }
	};
	using FontAtlasPtr = std::shared_ptr< FontAtlas >;

}