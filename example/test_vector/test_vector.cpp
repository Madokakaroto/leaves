#include <leaves\math\vector.hpp>
#include <iostream>
void main()
{
	using float4 = leaves::math::vector<float, 4>;
	using float3 = leaves::math::vector<float, 3>;

	// aggregate initialization
	{
		float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		float3 v2 = { 3.0f, 2.0f, 1.0f };
	}
	
	
	// uniform initialization
	{
		float4 v1 = float4{ 1.0f };
		float3 v2{ 0.0f };
	}
	
	// copy initialization
	{
		float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		float4 v2 = v1;
	}
	
	// vector proxy using place hodler
	{
		using namespace leaves::math::placeholders;
		
		float4 v1 = { 2.0f, 1.0f, 3.0f, 4.0f };
		v1(_r, _g, _b);
	
		// 然并卵
		// this proxy dose nothing unless it is assigned to another same-sized vector
		float3 v2 = v1(_r, _g, _b);
	}
	
	//// unary operator and function
	//{
	//	float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//
	//	float4 v2 = -v1;
	//	v2 = +v1;
	//	v2 = abs(v1);
	//	v2 = square(v1);
	//	v2 = inverse(v1);
	//}
	//
	//// operator + - * /
	//{
	//	float4 v1 = { 1.0f, 1.0f, 2.0f, 2.0f };
	//	float4 v2 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//
	//	float4 v3 = v1 + v2;
	//	v3 = v1 - v2;
	//	v3 = v1 * v2;
	//	v3 = v1 / v2;
	//}
	//
	//// operator assign
	//{
	//	float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//	v1 *= 2.0f;
	//	v1 /= 3.0f;
	//
	//	float4 v2 = { 2.0f, 2.0f, 2.0f, 2.0f };
	//	v2 += v1;
	//	v2 -= v1;
	//	v2 *= v1;
	//	v2 /= v1;
	//}
	//
	//// binary operator with scalar
	//{
	//	//float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//	//float4 v2 = v1 * 2.0f;
	//	//float4 v3 = v1 / 2.5f;
	//	//float4 v4 = 2.0f * v1;
	//}
	//
	//// this library uses template expression to do lazy evaluation until assignment
	//{
	//	float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//	float4 v2 = { 2.0f, 2.0f, 2.0f, 2.0f };
	//
	//	// this line of code dose nothing but create a template expression object
	//	auto expr = v1 + v2;
	//
	//	// this is where the actual evalution happens
	//	float4 v3 = expr;
	//}
	//
	//// proxy sugar
	//{
	//	using namespace leaves::math::placeholders;
	//
	//	float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//	float4 v2 = { 2.0f, 2.0f, 2.0f, 2.0f };
	//	float3 v3 = (v1 + v2(_b, _g, _r, _w))(_r, _b, _g);
	//}
	//
	//// dot product
	//{
	//	float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//	float4 v2 = { 2.0f, 2.0f, 2.0f, 2.0f };
	//	//auto dot_prod = dot(v1, v2);				// ADL 
	//}
}