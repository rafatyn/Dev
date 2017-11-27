#pragma once

#include "src/graphics/layers/Layer.h"
#include "src/graphics/BatchRenderer2D.h"

class TileLayer : public Sparky::Graphics::Layer {
public:
	TileLayer(Sparky::Graphics::Shader* shader);
	~TileLayer();
};