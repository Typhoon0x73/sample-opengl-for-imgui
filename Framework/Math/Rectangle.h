#pragma once

#include	"Vector3.h"

namespace Sample {

	template < typename T >
	class Rectangle {
	public:
		//-------------------------------------------------
		//�v���p�e�B
		//-------------------------------------------------
		union {
			struct {
				T	Left;
				T	Top;
				T	Right;
				T	Bottom;
			};
			T		Value[4];
		};

		//----------------------------------------------------------------------------
		//�R���X�g���N�^�E�f�X�g���N�^
		//----------------------------------------------------------------------------
		Rectangle()
		: Left(0)
		, Top(0)
		, Right(0)
		, Bottom(0) {
		}
		Rectangle(const T l, const T t, const T r, const T b)
		: Left(l)
		, Top(t)
		, Right(r)
		, Bottom(b) {
		}
		Rectangle(T v[4])
		: Left(v[0])
		, Top(v[1])
		, Right(v[2])
		, Bottom(v[3]) {
		}
		Rectangle(const Rectangle< T >& v)
		: Left(v.Left)
		, Top(v.Top)
		, Right(v.Right)
		, Bottom(v.Bottom) {
		}
		~Rectangle() = default;

		//----------------------------------------------------------------------------
		//Operator
		//----------------------------------------------------------------------------
		//�����̃|�C���^�ւ̃L���X�g
		operator T* () {
			return Value;
		}
		operator const T* () const {
			return Value;
		}
		operator const Rectangle<float> () const {
			return Rectangle<float>(
				static_cast<float>(Left),
				static_cast<float>(Top),
				static_cast<float>(Right),
				static_cast<float>(Bottom));
		}

		//���
		Rectangle< T >& operator = (const Rectangle< T >& v) {
			Left = v.Left;		Top = v.Top;		Right = v.Right;	Bottom = v.Bottom;
			return *this;
		}

		//�Z�p���Z�q +�@-�@*�@/
		Rectangle< T > operator + (const Vector3F& v) const {
			return Rectangle< T >(Left + v.x, Top + v.y, Right + v.x, Bottom + v.y);
		}

		//����������Z�q +=�@-=�@*=�@/=
		Rectangle< T >& operator += (const Vector3F& v) {
			Left += v.x;		Top += v.y;		Right += v.x;		Bottom += v.y;
			return *this;
		}

		//�Y�����Z�q []
		T& operator [] (int i) {
			return Value[i];
		}
		const T& operator [] (int i) const {
			return Value[i];
		}

		//��r���Z�q == !=
		bool operator == (const Rectangle< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(Left - v.Left) <= e) && (std::abs(Top - v.Top) <= e) && (std::abs(Right - v.Right) <= e) && (std::abs(Bottom - v.Bottom) <= e);
		}
		bool operator != (const Rectangle< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(Left - v.Left) > e) || (std::abs(Top - v.Top) > e) || (std::abs(Right - v.Right) > e) || (std::abs(Bottom - v.Bottom) > e);
		}

		//----------------------------------------------------------------------------
		//���\�b�h
		//----------------------------------------------------------------------------
		//���擾
		const T Width() const {
			return Right - Left;
		}
		//�����擾
		const T Height() const {
			return Bottom - Top;
		}
		//���S�擾
		void Center(float& cx, float& cy) const {
			cx = (Left + Right) * 0.5f;
			cy = (Top + Bottom) * 0.5f;
		}
		//�ڐG����
		bool Collision(const float px, const float py) const {
			if (px >= Left && px <= Right && py >= Top && py <= Bottom)
			{
				return true;
			}
			return false;
		}
		//�ڐG����
		bool Collision(const Rectangle< T >& r) const {
			if (r.Right >= Left && r.Left <= Right && r.Bottom >= Top && r.Top <= Bottom)
			{
				return true;
			}
			return false;
		}

		//������ւ̕ϊ�
		std::string ToString() const {
			std::ostringstream ss;
			ss << Left << ", " << Top << ", " << Right << ", " << Bottom;
			return ss.str();
		}
		//�����񂩂�̕ϊ�
		static Rectangle< T > FromString(const char* str) {
			Rectangle < T > v;
			std::istringstream ss(str);
			ss >> v.Left;
			ss.ignore();
			ss >> v.Top;
			ss.ignore();
			ss >> v.Right;
			ss.ignore();
			ss >> v.Bottom;
			return v;
		}
		static Rectangle< T > FromString(const std::string& str) {
			return FromString(str.c_str());
		}
	};

	//�^�u������
	using RectangleI = Rectangle< int >;
	using RectangleF = Rectangle< float >;
	using RectangleD = Rectangle< double >;

}