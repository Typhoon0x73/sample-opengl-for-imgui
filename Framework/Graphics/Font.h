#pragma once

#include	"../Resource/ResourceBase.h"
#include	"FreeTypeLibrary.h"

namespace Sample {

	/**
	 * @brief		フォントを扱うためのクラス
	 */
	class Font : public ResourceBase
	{
	public:
		/** フォント画像 */
		struct Image {
			int			offsetX;
			int			offsetY;
			int			width;
			int			height;
			uint8_t*	pixels;
		};
		using ImagePtr = std::shared_ptr< Image >;
	protected:
		/** 利用するフォントサイズ */
		uint32_t		size_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Font()
			: ResourceBase()
			, size_(0) {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Font() {
		}

		/**
		 * @brief		読み込み
		 * @param[in]	name	読み込むフォントファイル名
		 * @param[in]	size	フォントサイズ
		 * @return		true	読み込み成功
		 *				false	読み込み失敗
		 */
		bool Create(const char* name, const uint32_t size) {
			if (!FreeTypeLibrary::GetInstance().CreteFace(name, size))
			{
				return false;
			}
			name_ = name;
			size_ = size;
			INFO_LOG("フォント" << name << "を読み込み...");
			return true;
		}

		/**
		 * @brief		指定されたコードのBMP生成
		 * @param[in]	code	文字コード
		 * @return		生成したイメージ
		 */
		ImagePtr CreateCodeBitmap(uint32_t code) {
			FT_GlyphSlot slot = FreeTypeLibrary::GetInstance().CreateChar(name_.c_str(), size_, code);
			if (slot == nullptr)
			{
				return ImagePtr();
			}
			ImagePtr re = std::make_shared<Image>();
			re->offsetX = slot->bitmap_left;
			re->offsetY = size_ - slot->bitmap_top;
			re->width = slot->bitmap.width;
			re->height = slot->bitmap.rows;
			re->pixels = slot->bitmap.buffer;
			return re;
		}

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const uint32_t Size() const noexcept { return size_; }
	};
	using FontPtr = std::shared_ptr< Font >;

}