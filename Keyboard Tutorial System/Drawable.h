#pragma once

#include "Object.h"
#include "Utils.h"

namespace rescan
{
	struct Drawable : public rescan::Object
	{
		virtual void Draw() = 0;
		virtual void Update(double deltaTime) = 0;

		virtual void SetTarget(ID2D1HwndRenderTarget* target) noexcept;
		virtual ID2D1HwndRenderTarget* GetTarget() const noexcept;

		virtual ~Drawable();

	protected:
		ID2D1HwndRenderTarget* m_renderTarget;
	};
}
