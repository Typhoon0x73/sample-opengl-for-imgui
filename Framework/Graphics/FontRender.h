#pragma once

#include	"FontAtlas.h"
#include	"SpriteBatch.h"

namespace Sample {

	/**
	 * @brief		フォントを描画するためのクラス
	 */
	class FontRender
	{
	protected:
		/** 利用するスプライト */
		SpriteBatchPtr	sprite_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		FontRender()
			: sprite_() {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~FontRender() {
		}

		/**
		 * @brief		生成
		 * @param[in]	shader		描画用シェーダー
		 * @return		true		生成成功
		 *				false		生成失敗
		 */
		bool Create(ShaderPtr shader) {
			//スプライト生成
			sprite_ = std::make_shared<SpriteBatch>();
			sprite_->Create(shader);
			return true;
		}

		/**
		 * @brief		描画
		 * @param[in]	x			描画位置
		 * @param[in]	y			描画位置
		 * @param[in]	str			描画文字列
		 * @param[in]	font		描画用フォント
		 */
		bool Render(float x, float y, const Vector4F& color, const std::string& str, FontAtlasPtr& font) {
			//スライスマップ
			const auto& map = font->Slices();
			//テクスチャ
			auto tex = font->Texture();
			//描画座標
			float dx = x;
			float dy = y;

			//文字を分割して描画登録
			sprite_->Reset();
			for (size_t i = 0; i < str.size(); i++)
			{
				//描画文字
				char text[3] = { 0 };
				if (IsDBCSLeadByte(str[i]))
				{
					text[0] = str[i]; text[1] = str[i + 1];
					i++;
				}
				else
				{
					//改行文字は次の行へ字下げ
					if (str[i] == '\n')
					{
						dx = x;
						dy += font->Font()->Size();
						continue;
					}
					text[0] = str[i];
				}
				//マップから検索
				auto slice = map.find(text);
				if (slice == map.end())
				{
					if (!font->Add(text))
					{
						return false;
					}
					slice = map.find(text);
					if (slice == map.end())
					{
						return false;
					}
				}
				sprite_->RenderRegister(tex, Vector3F(dx, dy, 0), color, slice->second);
				dx += slice->second.Width();
			}
			sprite_->RefreshVertex();
			sprite_->Render();
			return true;
		}

	};
	using FontRenderPtr = std::shared_ptr< FontRender >;

}