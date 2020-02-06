#include "stdafx.h"
#include "Mouse.h"

std::pair<int, int> rescan::Mouse::GetPos() const noexcept
{
	return { x, y };
}

std::optional<rescan::Mouse::RawDelta> rescan::Mouse::ReadRawDelta() noexcept
{
	if (rawDeltaBuffer.empty())
		return std::nullopt;
	const RawDelta d = rawDeltaBuffer.front();
	rawDeltaBuffer.pop();
	return d;
}

int rescan::Mouse::GetPosX() const noexcept
{
	return x;
}

int rescan::Mouse::GetPosY() const noexcept
{
	return y;
}

bool rescan::Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool rescan::Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool rescan::Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

std::optional<rescan::Mouse::Event> rescan::Mouse::Read() noexcept
{
	if (buffer.size() > 0)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return {};
}

void rescan::Mouse::Flush() noexcept
{
	buffer = std::queue<Mouse::Event>();
}

void rescan::Mouse::EnableRaw() noexcept
{
	rawEnabled = true;
}

void rescan::Mouse::DisableRaw() noexcept
{
	rawEnabled = false;
}

bool rescan::Mouse::RawEnabled() const noexcept
{
	return rawEnabled;
}

void rescan::Mouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void rescan::Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void rescan::Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void rescan::Mouse::OnRawDelta(int dx, int dy) noexcept
{
	rawDeltaBuffer.push({ dx, dy });
	TrimRawInputBuffer();
}

void rescan::Mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void rescan::Mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void rescan::Mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	TrimBuffer();
}

void rescan::Mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void rescan::Mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void rescan::Mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void rescan::Mouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
		buffer.pop();
}

void rescan::Mouse::TrimRawInputBuffer() noexcept
{
	while (rawDeltaBuffer.size() > bufferSize)
		rawDeltaBuffer.pop();
}

void rescan::Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	// generates event for every 120
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}
