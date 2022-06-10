#pragma once

#include	"../Common/Common.h"

namespace Sample {

	template < typename T >
	class Vector4 {
	public:
		//-------------------------------------------------
		//�v���p�e�B
		//-------------------------------------------------
		union {
			struct {
				T	x;
				T	y;
				T	z;
				T	w;
			};
			struct {
				T	r;
				T	g;
				T	b;
				T	a;
			};
			T		Value[4];
		};

		//----------------------------------------------------------------------------
		//�R���X�g���N�^�E�f�X�g���N�^
		//----------------------------------------------------------------------------
		Vector4()
			: x(0)
			, y(0)
			, z(0)
			, w(0) {
		}
		Vector4(const T vx, const T vy, const T vz, const T vw)
			: x(vx)
			, y(vy)
			, z(vz)
			, w(vw) {
		}
		Vector4(T v[4])
			: x(v[0])
			, y(v[1])
			, z(v[2])
			, w(v[3]) {
		}
		Vector4(const Vector4< T >& v)
			: x(v.x)
			, y(v.y)
			, z(v.z)
			, w(v.w) {
		}
		~Vector4() = default;

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
		operator const Vector4<float> () const {
			return Vector4<float>(
				static_cast<float>(x),
				static_cast<float>(y),
				static_cast<float>(z),
				static_cast<float>(w));
		}

		//���
		Vector4< T >& operator = (const Vector4< T >& v) {
			x = v.x;		y = v.y;		z = v.z;		w = v.w;
			return *this;
		}

		//�P�����Z�q -�i�t�����̃x�N�g���j
		Vector4< T > operator - () const {
			return Vector4< T >(x, y, z, w);
		}

		//�Z�p���Z�q +�@-�@*�@/
		Vector4< T > operator + (const Vector4< T >& v) const {
			return Vector4< T >(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		Vector4< T > operator - (const Vector4< T >& v) const {
			return Vector4< T >(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		Vector4< T > operator * (const Vector4< T >& v) const {
			return Vector4< T >(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		Vector4< T > operator * (const T& v) const {
			return Vector4< T >(x * v, y * v, z * v, w * v);
		}
		Vector4< T > operator / (const Vector4< T >& v) const {
			return Vector4< T >(x / v.x, y / v.y, z / v.z, w / v.w);
		}
		Vector4< T > operator / (const T& v) const {
			return Vector4< T >(x / v, y / v, z / v, w / v);
		}

		//����������Z�q +=�@-=�@*=�@/=
		Vector4< T >& operator += (const Vector4< T >& v) {
			x += v.x;		y += v.y;		z += v.z;		w += v.w;
			return *this;
		}
		Vector4< T >& operator -= (const Vector4< T >& v) {
			x -= v.x;		y -= v.y;		z -= v.z;		w -= v.w;
			return *this;
		}
		Vector4< T >& operator *= (const Vector4< T >& v) {
			x *= v.x;		y *= v.y;		z *= v.z;		w *= v.w;
			return *this;
		}
		Vector4< T >& operator *= (const T& v) {
			x *= v;			y *= v;			z *= v;			w *= v;
			return *this;
		}
		Vector4< T >& operator /= (const Vector4< T >& v) {
			x /= v.x;		y /= v.y;		z /= v.z;		w /= v.w;
			return *this;
		}
		Vector4< T >& operator /= (const T& v) {
			x /= v;			y /= v;			z /= v;			w /= v;
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
		bool operator == (const Vector4< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(x - v.x) <= e) && (std::abs(y - v.y) <= e) && (std::abs(z - v.z) <= e) && (std::abs(w - v.w) <= e);
		}
		bool operator != (const Vector4< T >& v) const {
			constexpr T e = std::numeric_limits<T>::epsilon();
			return (std::abs(x - v.x) > e) || (std::abs(y - v.y) > e) || (std::abs(z - v.z) > e) || (std::abs(w - v.w) > e);
		}

		//----------------------------------------------------------------------------
		//���\�b�h
		//----------------------------------------------------------------------------
		//�����i�m�����j�v�Z ��Unity��magnitude�ɑΉ�
		static double Length(const Vector4< T >& v) {
			return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
		}
		//�����i�m�����j�v�Z ��Unity��sqrmagnitude�ɑΉ�
		static double SqrLength(const Vector4< T >& v) {
			return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
		}
		//�����v�Z ��Unity��Distance�ɑΉ�
		static double Distance(const Vector4< T >& v1, const Vector4< T >& v2) {
			Vector4< T > sub = v1 - v2;
			return Length(sub);
		}

		//���K���@��Unity��Normalize�ɑΉ�
		static Vector4< T > Normalize(const Vector4< T >& v) {
			double d = Length(v);
			constexpr double e = std::numeric_limits<double>::epsilon();
			if (d <= e)
			{
				return Vector4< T >(0, 0, 0, 0);
			}
			double rd = 1 / d;
			return Vector4< T >(v.x * rd, v.y * rd, v.z * rd, v.w * rd);
		}

		//���`��� ��Unity��Lerp�ɑΉ�
		static Vector4< T > Lerp(const Vector4< T >& v1, const Vector4< T >& v2, const double t) {
			if (t <= 0) { return v1; }
			else if (t >= 1) { return v2; }
			return Vector4< T >(
				v1.x + (v2.x - v1.x) * t,
				v1.y + (v2.y - v1.y) * t,
				v1.z + (v2.z - v1.z) * t,
				v1.w + (v2.w - v1.w) * t);
		}

		//�ړ� ��Unity��MoveTowards�ɑΉ�
		static Vector4< T > MoveTowards(const Vector4< T >& v1, const Vector4< T >& v2, const double t) {
			if (t <= 0) { return v1; }
			double d = Distance(v1, v2);
			if (t >= d) { return v2; }
			Vector4< double > nv = Normalize(v2 - v1);
			return Vector4< T >(v1 + nv * t);
		}

		//������ւ̕ϊ�
		std::string ToString() const {
			std::ostringstream ss;
			ss << x << ", " << y << ", " << z << ", " << w;
			return ss.str();
		}
		//�����񂩂�̕ϊ�
		static Vector4< T > FromString(const char* str) {
			Vector4 < T > v;
			std::istringstream ss(str);
			ss >> v.x;
			ss.ignore();
			ss >> v.y;
			ss.ignore();
			ss >> v.z;
			ss.ignore();
			ss >> v.w;
			return v;
		}
		static Vector4< T > FromString(const std::string& str) {
			return FromString(str.c_str());
		}
	};

	//�^�u������
	using Vector4I = Vector4< int >;
	using Vector4F = Vector4< float >;
	using Vector4D = Vector4< double >;

}