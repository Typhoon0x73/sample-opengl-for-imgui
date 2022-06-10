#pragma once

#include	"../Common/Common.h"

namespace Sample {

	template < typename T >
	class Vector3 {
	public:
		//-------------------------------------------------
		//プロパティ
		//-------------------------------------------------
		union {
			struct {
				T	x;
				T	y;
				T	z;
			};
			T		Value[3];
		};

		//----------------------------------------------------------------------------
		//コンストラクタ・デストラクタ
		//----------------------------------------------------------------------------
		Vector3()
			: x(0)
			, y(0)
			, z(0) {
		}
		Vector3(const T vx, const T vy, const T vz)
			: x(vx)
			, y(vy)
			, z(vz) {
		}
		Vector3(T v[3])
			: x(v[0])
			, y(v[1])
			, z(v[2]) {
		}
		Vector3(const Vector3< T >& v)
			: x(v.x)
			, y(v.y)
			, z(v.z) {
		}
		~Vector3() = default;

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
		operator const Vector3<float> () const {
			return Vector3<float>(
				static_cast<float>(x),
				static_cast<float>(y),
				static_cast<float>(z));
		}

		//代入
		Vector3< T >& operator = (const Vector3< T >& v) {
			x = v.x;		y = v.y;		z = v.z;
			return *this;
		}

		//単項演算子 -（逆方向のベクトル）
		Vector3< T > operator - () const {
			return Vector3< T >(x, y, z);
		}

		//算術演算子 +　-　*　/
		Vector3< T > operator + (const Vector3< T >& v) const {
			return Vector3< T >(x + v.x, y + v.y, z + v.z);
		}
		Vector3< T > operator - (const Vector3< T >& v) const {
			return Vector3< T >(x - v.x, y - v.y, z - v.z);
		}
		Vector3< T > operator * (const Vector3< T >& v) const {
			return Vector3< T >(x * v.x, y * v.y, z * v.z);
		}
		Vector3< T > operator * (const T& v) const {
			return Vector3< T >(x * v, y * v, z * v);
		}
		Vector3< T > operator / (const Vector3< T >& v) const {
			return Vector3< T >(x / v.x, y / v.y, z / v.z);
		}
		Vector3< T > operator / (const T& v) const {
			return Vector3< T >(x / v, y / v, z / v);
		}

		//複合代入演算子 +=　-=　*=　/=
		Vector3< T >& operator += (const Vector3< T >& v) {
			x += v.x;		y += v.y;		z += v.z;
			return *this;
		}
		Vector3< T >& operator -= (const Vector3< T >& v) {
			x -= v.x;		y -= v.y;		z -= v.z;
			return *this;
		}
		Vector3< T >& operator *= (const Vector3< T >& v) {
			x *= v.x;		y *= v.y;		z *= v.z;
			return *this;
		}
		Vector3< T >& operator *= (const T& v) {
			x *= v;			y *= v;			z *= v;
			return *this;
		}
		Vector3< T >& operator /= (const Vector3< T >& v) {
			x /= v.x;		y /= v.y;		z /= v.z;
			return *this;
		}
		Vector3< T >& operator /= (const T& v) {
			x /= v;			y /= v;			z /= v;
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
		bool operator == (const Vector3< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(x - v.x) <= e) && (std::abs(y - v.y) <= e) && (std::abs(z - v.z) <= e);
		}
		bool operator != (const Vector3< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(x - v.x) > e) || (std::abs(y - v.y) > e) || (std::abs(z - v.z) > e);
		}

		//----------------------------------------------------------------------------
		//メソッド
		//----------------------------------------------------------------------------
		//長さ（ノルム）計算 ※Unityのmagnitudeに対応
		static double Length(const Vector3< T >& v) {
			return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		}
		//長さ（ノルム）計算 ※Unityのsqrmagnitudeに対応
		static double SqrLength(const Vector3< T >& v) {
			return v.x * v.x + v.y * v.y + v.z * v.z;
		}
		//距離計算 ※UnityのDistanceに対応
		static double Distance(const Vector3< T >& v1, const Vector3< T >& v2) {
			Vector3< T > sub = v1 - v2;
			return Length(sub);
		}

		//正規化　※UnityのNormalizeに対応
		static Vector3< T > Normalize(const Vector3< T >& v) {
			double d = Length(v);
			constexpr double e = std::numeric_limits<double>::epsilon();
			if (d <= e)
			{
				return Vector3< T >(0, 0, 0);
			}
			double rd = 1 / d;
			return Vector3< T >(v.x * rd, v.y * rd, v.z * rd);
		}

		//内積　※UnityのDotに対応
		static double Dot(const Vector3< T >& v1, const Vector3< T >& v2) {
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		//内積から角を求める　※UnityのAngleに対応
		static double RadianAngle(const Vector3< T >& v1, const Vector3< T >& v2) {
			double l = Length(v1) * Length(v2);
			constexpr T e = std::numeric_limits<double>::epsilon();
			if (l <= e)
			{
				return 0;
			}
			double d = Dot(v1, v2) / l;
			if (d < -1) { d = -1; }
			else if (d > 1) { d = 1; }
			return std::acos(d);
		}
		static double Angle(const Vector3< T >& v1, const Vector3< T >& v2) {
			constexpr double pi = 3.141592653589;
			return RadianAngle(v1, v2) / pi * 180;
		}

		//外積　※UnityのCrossに対応
		static Vector3< double > Cross(const Vector3< T >& v1, const Vector3< T >& v2) {
			return Vector3< double >(
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x);
		}

		//線形補間 ※UnityのLerpに対応
		static Vector3< T > Lerp(const Vector3< T >& v1, const Vector3< T >& v2, const double t) {
			if (t <= 0) { return v1; }
			else if (t >= 1) { return v2; }
			return Vector3< T >(
				v1.x + (v2.x - v1.x) * t,
				v1.y + (v2.y - v1.y) * t,
				v1.z + (v2.z - v1.z) * t);
		}

		//移動 ※UnityのMoveTowardsに対応
		static Vector3< T > MoveTowards(const Vector3< T >& v1, const Vector3< T >& v2, const double t) {
			if (t <= 0) { return v1; }
			double d = Distance(v1, v2);
			if (t >= d) { return v2; }
			Vector3< double > nv = Normalize(v2 - v1);
			return Vector3< T >(v1 + nv * t);
		}

		//X軸への回転
		static Vector3< T > RotationX(const Vector3< T >& v, const double ang) {
			double sina = std::sin(ang);
			double cosa = std::cos(ang);
			return Vector3< T >(
				v.x,
				(T)(v.y * cosa + v.z * -sina),
				(T)(v.y * sina + v.z * cosa));
		}

		//Y軸への回転
		static Vector3< T > RotationY(const Vector3< T >& v, const double ang) {
			double sina = std::sin(ang);
			double cosa = std::cos(ang);
			return Vector3< T >(
				(T)(v.x * cosa + v.z * sina),
				v.y,
				(T)(v.x * -sina + v.z * cosa));
		}

		//Z軸への回転
		static Vector3< T > RotationZ(const Vector3< T >& v, const double ang) {
			double sina = std::sin(ang);
			double cosa = std::cos(ang);
			return Vector3< T >(
				(T)(v.x * cosa + v.y * -sina),
				(T)(v.x * sina + v.y * cosa),
				v.z);
		}

		//文字列への変換
		std::string ToString() const {
			std::ostringstream ss;
			ss << x << ", " << y << ", " << z;
			return ss.str();
		}
		//文字列からの変換
		static Vector3< T > FromString(const char* str) {
			Vector3 < T > v;
			std::istringstream ss(str);
			ss >> v.x;
			ss.ignore();
			ss >> v.y;
			ss.ignore();
			ss >> v.z;
			return v;
		}
		static Vector3< T > FromString(const std::string& str) {
			return FromString(str.c_str());
		}
	};

	//型置き換え
	using Vector3I = Vector3< int >;
	using Vector3F = Vector3< float >;
	using Vector3D = Vector3< double >;

}