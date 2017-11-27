#include "TileLayer.h"

TileLayer::TileLayer(Sparky::Graphics::Shader * shader) :
	Sparky::Graphics::Layer(new Sparky::Graphics::BatchRenderer2D(), shader, Sparky::Maths::Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{}

TileLayer::~TileLayer()
{
}