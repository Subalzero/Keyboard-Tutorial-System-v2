#include "stdafx.h"
#include "Scene.h"

rescan::Scene::Scene(Rect rect, Graphics2D* graphics)  :
	View(rect, graphics),
	callback(nullptr)
{
}

rescan::Scene::~Scene()
{
}

void rescan::Scene::KeyboardEvents(const Keyboard::Event& ev)
{
}

void rescan::Scene::MouseEvents(const Mouse::Event& ev)
{
}

void rescan::Scene::Draw()
{
}

void rescan::Scene::Update(double deltaTime)
{
}

void rescan::Scene::Begin()
{
}

void rescan::Scene::End()
{
}
