#pragma once

#include <stdlib.h>
#include "SceneID.h"

class Scene {
public:
	Scene();
	virtual ~Scene();
	virtual void Update() = 0;
	virtual void Render() = 0;

private:

};
