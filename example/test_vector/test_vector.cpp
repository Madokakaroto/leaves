#include <leaves\math\vector.hpp>

void main()
{
	using float4 = leaves::math::vector<float, 4>;
	using float3 = leaves::math::vector<float, 3>;

	float4 v;

	// aggregate initialization
	//float4 v4_1 = { 1.0f, 2.0f, 3.0f, 4.0f };
	//float3 v3_1 = { 3.0f, 2.0f, 1.0f };
	//
	//// uniform initialization
	//float4 v4_2 = float4{ 1.0f };
	//
	//// copy initialization
	//float4 v4_3 = v4_1;
	//
	//// vector proxy using place hodler
	//using namespace leaves::math::placeholders;
	//v4_2(_r, _g, _b);
	//
	//// 然并卵
	//// this proxy dose nothing unless it is assigned to another same-sized vector
	//float3 v3_2 = v4_2(_r, _g, _b);
	//
	//// operator + - * /
	//v4_3 = v4_1 + v4_2;
	//v4_3 = v4_1 - v4_2;
	//v4_3 = v4_1 * v4_2;
	//v4_3 = v4_1 / v4_2;
	//
	//// this library uses template expression to do lazy evaluation until assignment
	//// this line of code dose nothing but create a expression object
	//auto ex_foo = v4_1 + v4_2;
	//
	//// this is where the actual evalution happens
	//float4 v4_4 = ex_foo;
	//
	//// using proxy to create some cookies
	//float3 v3_3 = (v4_4 + v4_1(_b, _g, _r, _w))(_r, _b, _g);
	//
	//// scalar multiplication
	//float4 v4_5 = v4_4 * 2.0f;
	//v4_5 = v4_5 / 2.0f;
	//
	//float4 v4_6 = 2.0f * v4_5;
}