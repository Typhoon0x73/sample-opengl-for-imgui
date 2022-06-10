#pragma once

namespace Sample {

	/**
	 * Singleton�p�e���v���[�g
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
		 * �V���O���g���p�̃C���X�^���X�̐���
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
		 * �V���O���g���p�̃A�N�Z�X�|�C���g�̒�`
		 * ���̊֐����ŃC���X�^���X������A�O������Q�Ƃł���
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
		 * �V���O���g���p�̃C���X�^���X�̔j��
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