#pragma once

#include	"Vector3.h"

namespace Sample {

	template < typename T >
	class Rectangle {
	public:
		//-------------------------------------------------
		//プロパティ
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
		//コンストラクタ・デストラクタ
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
		//成分のポインタへのキャスト
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

		//代入
		Rectangle< T >& operator = (const Rectangle< T >& v) {
			Left = v.Left;		Top = v.Top;		Right = v.Right;	Bottom = v.Bottom;
			return *this;
		}

		//算術演算子 +　-　*　/
		Rectangle< T > operator + (const Vector3F& v) const {
			return Rectangle< T >(Left + v.x, Top + v.y, Right + v.x, Bottom + v.y);
		}

		//複合代入演算子 +=　-=　*=　/=
		Rectangle< T >& operator += (const Vector3F& v) {
			Left += v.x;		Top += v.y;		Right += v.x;		Bottom += v.y;
			return *this;
		}

		//添字演算子 []
		T& operator [] (int i) {
			return Value[i];
		}
		const T& operator [] (int i) const {
			return Value[i];
		}

		//比較演算子 == !=
		bool operator == (const Rectangle< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(Left - v.Left) <= e) && (std::abs(Top - v.Top) <= e) && (std::abs(Right - v.Right) <= e) && (std::abs(Bottom - v.Bottom) <= e);
		}
		bool operator != (const Rectangle< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(Left - v.Left) > e) || (std::abs(Top - v.Top) > e) || (std::abs(Right - v.Right) > e) || (std::abs(Bottom - v.Bottom) > e);
		}

		//----------------------------------------------------------------------------
		//メソッド
		//----------------------------------------------------------------------------
		//幅取得
		const T Width() const {
			return Right - Left;
		}
		//高さ取得
		const T Height() const {
			return Bottom - Top;
		}
		//中心取得
		void Center(float& cx, float& cy) const {
			cx = (Left + Right) * 0.5f;
			cy = (Top + Bottom) * 0.5f;
		}
		//接触判定
		bool Collision(const float px, const float py) const {
			if (px >= Left && px <= Right && py >= Top && py <= Bottom)
			{
				return true;
			}
			return false;
		}
		//接触判定
		bool Collision(const Rectangle< T >& r) const {
			if (r.Right >= Left && r.Left <= Right && r.Bottom >= Top && r.Top <= Bottom)
			{
				return true;
			}
			return false;
		}

		//文字列への変換
		std::string ToString() const {
			std::ostringstream ss;
			ss << Left << ", " << Top << ", " << Right << ", " << Bottom;
			return ss.str();
		}
		//文字列からの変換
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

	//型置き換え
	using RectangleI = Rectangle< int >;
	using RectangleF = Rectangle< float >;
	using RectangleD = Rectangle< double >;

}