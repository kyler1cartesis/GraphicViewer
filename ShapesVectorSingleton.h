#pragma once
#include <vector>
#include <memory>

#include "ContainerSingleton.h"
#include "FLTKGraphicsEngine.h"

struct Shape;

//using container_t = ;
class ShapesVectorSingleton :
	public ContainerSingleton<std::vector<std::unique_ptr<Shape>>> {

public:
	static void DrawShapes(Coordinates offset = { 0, 0 }) {
		for (const auto& shape_ptr : ShapesVectorSingleton::Get()) {
			FLTKGraphicsEngine::DrawShape(*shape_ptr, offset);
		}
	}
};