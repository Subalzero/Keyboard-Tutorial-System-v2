#pragma once

#include "Drawable.h"
#include "Utils.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics2D.h"

namespace rescan
{
	class View : public Drawable
	{
	public:
		View(Rect frame, Graphics2D* graphics) noexcept :
			frame(frame), bounds({ { 0, 0 }, { frame.size.height, frame.size.width } }),
			pGraphics(graphics)
		{}
		virtual ~View() {}

		virtual void AddSubview(const std::shared_ptr<View> view) noexcept
		{
			view->SetTarget(GetTarget());
			view->SetParentView(view);
			subviews.push_back(view);
		}

		virtual void SetFrame(Rect rect) noexcept
		{
			frame = rect;
			bounds.size = rect.size;
		}

		virtual Rect GetFrame() const noexcept
		{
			return frame; 
		}

		virtual void SetBounds(Rect rect) noexcept
		{
			bounds = rect;
			frame.size = rect.size;
			frame.origin.x = parentView.lock()->frame.origin.x + bounds.origin.x;
			frame.origin.y = parentView.lock()->frame.origin.y + bounds.origin.y;
		}

		virtual Rect GetBounds() const noexcept
		{
			return bounds;
		}

		virtual void SetTarget(ID2D1HwndRenderTarget* target) noexcept override
		{
			for (size_t i = 0; i < subviews.size(); ++i)
				subviews[i]->m_renderTarget = m_renderTarget;
		}

		virtual void Draw() override
		{}

		virtual void Update(double deltaTime) override
		{}

		virtual void KeyboardEvents(const Keyboard::Event& ev) {}
		virtual void MouseEvents(const Mouse::Event& ev) {}

	protected:
		virtual void SetParentView(const std::weak_ptr<View> view) noexcept
		{
			parentView = view;
		}
	protected:
		Rect frame;
		Rect bounds;
		std::vector<std::shared_ptr<View>> subviews;
		std::weak_ptr<View> parentView;
		Graphics2D* pGraphics;
	};
}
