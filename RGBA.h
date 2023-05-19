#pragma once

struct MYRGBA final {
	unsigned char r, g, b, a; //
	MYRGBA() = default;
	constexpr MYRGBA(const unsigned char r_, const unsigned char g_, const unsigned char b_, const unsigned char a_) :r(r_), g(g_), b(b_), a(a_) {}
};