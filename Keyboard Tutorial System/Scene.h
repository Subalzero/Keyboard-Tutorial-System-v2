#pragma once

#include "stdafx.h"
#include "Drawable.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "View.h"
#include "SceneCallback.h"
#include "Graphics2D.h"

namespace rescan
{
	class Scene : public View
	{
	public:
		Scene(Rect rect, Graphics2D* graphics);
		~Scene();
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
		virtual void MouseEvents(const Mouse::Event& ev) override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void Begin();
		virtual void End();
	public:
		SceneCallback* callback;
	};
}