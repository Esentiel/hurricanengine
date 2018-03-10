#pragma once

#include <array>
#include <initializer_list>
#include <type_traits>

template <class T, typename U>
struct Vertex;

typedef Vertex<std::array<float, 3>, float> Vertex3f;
typedef Vertex<std::array<float, 2>, float> Vertex2f;

template <typename T, typename U>
struct Vertex
{
public:
	Vertex() : pos({ 0, 0, 0 }) {}
	Vertex(const T& pos) : pos(pos) {}

	Vertex(U x, U y, U z)
	{
		if (std::is_floating_point<U>::value)
			pos = std::move(T({ x, y, z }));
	}

	Vertex(U x, U y)
	{
		if (std::is_floating_point<U>::value)
			pos = std::move(T({ x, y }));
	}

	T& data() { return pos; }
	const T& data() const { return pos; }

	U x() { return pos[0]; }
	U y() { return pos[1]; }
	U z() { return pos[2]; }
private:
	T pos;
};


template<typename T>
T GetGLMVec(Vertex3f vec)
{
	return T(vec.data().at(0), vec.data().at(1), vec.data().at(2));
}

template<typename T>
T GetGLMVec(Vertex2f vec)
{
	return T(vec.data().at(0), vec.data().at(1));
}