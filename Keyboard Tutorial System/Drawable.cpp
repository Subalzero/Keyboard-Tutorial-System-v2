#include "stdafx.h"
#include "Drawable.h"

void rescan::Drawable::SetTarget(ID2D1HwndRenderTarget* target) noexcept
{
	m_renderTarget = target;
}

ID2D1HwndRenderTarget* rescan::Drawable::GetTarget() const noexcept
{
	return m_renderTarget;
}

rescan::Drawable::~Drawable()
{
}
