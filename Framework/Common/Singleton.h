#pragma once

namespace Sample {

	/**
	 * Singleton用テンプレート
	 */
	template< typename T >
	class Singleton
	{
	private:
		Singleton(const Singleton& obj) = delete;
		Singleton(Singleton&& obj) = delete;

		static T* instance;
	protected:
		Singleton() { }
		virtual ~Singleton() { }

		/**
		 * シングルトン用のインスタンスの生成
		 */
		static void Create()
		{
			assert(!instance);
			if (instance)
			{
				return;
			}
			instance = new T();
		}
	public:
		/**
		 * シングルトン用のアクセスポイントの定義
		 * この関数内でインスタンス化され、外部から参照できる
		 */
		static constexpr T& GetInstance()
		{
			if (instance == nullptr)
			{
				Create();
			}
			return *instance;
		}

		/**
		 * シングルトン用のインスタンスの破棄
		 */
		static void Release()
		{
			assert(instance);
			if (instance)
			{
				delete instance;
				instance = nullptr;
				return;
			}
		}
	};
	template< typename T > T* Singleton<T>::instance = nullptr;

}