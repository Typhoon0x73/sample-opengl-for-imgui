#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		テクスチャサンプラを扱うためのクラス
	 */
	class Sampler
	{
	public:
		enum class Wrap {
			Clamp,
			Repeat,
			Mirror,
		};

		enum class Filter {
			Nearest,
			Linear,
		};

	protected:
		/** サンプラID */
		GLuint			id_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Sampler()
			: id_(0) {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Sampler() {
			Release();
		}

		/**
		 * @brief		生成
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Create() {
			glCreateSamplers(1, &id_);
			GL_ERROR_RETURN("サンプラの生成に失敗...", false);
			return true;
		}

		/**
		 * @brief		ラップモードの設定
		 * @param[in]	mode	モード
		 * @return		true	成功
		 *				false	失敗
		 */
		bool WrapMode(Wrap mode) {
			switch (mode)
			{
			case Wrap::Clamp:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;

			case Wrap::Repeat:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;

			case Wrap::Mirror:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			}
			GL_ERROR_RETURN("ラップモードの設定に失敗...", false);
			return true;
		}

		/**
		 * @brief		フィルターモードの設定
		 * @param[in]	min		縮小モード
		 * @param[in]	mag		拡大モード
		 * @return		true	成功
		 *				false	失敗
		 */
		bool FilterMode(Filter min, Filter mag) {
			switch (min)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("フィルタの設定に失敗...", false);

			switch (mag)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("フィルタの設定に失敗...", false);
			return true;
		}

		/**
		 * @brief		フィルターモードの設定
		 * @param[in]	min		縮小モード
		 * @param[in]	mag		拡大モード
		 * @param[in]	mip		ミップマップモード
		 * @return		true	成功
		 *				false	失敗
		 */
		bool FilterMode(Filter min, Filter mag, Filter mip) {
			switch (min)
			{
			case Filter::Nearest:
				switch (mip)
				{
				case Filter::Nearest:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
					break;

				case Filter::Linear:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
					break;
				}
				break;

			case Filter::Linear:
				switch (mip)
				{
				case Filter::Nearest:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
					break;

				case Filter::Linear:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					break;
				}
				break;
			}
			GL_ERROR_RETURN("フィルタの設定に失敗...", false);

			switch (mag)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("フィルタの設定に失敗...", false);
			return true;
		}

		/**
		 * @brief		解放処理
		 */
		void Release() {
			if (id_ == 0)
			{
				return;
			}
			glDeleteSamplers(1, &id_);
			id_ = 0;
		}

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const GLuint ID() const noexcept { return id_; }

	};
	using SamplerPtr = std::shared_ptr< Sampler >;

}