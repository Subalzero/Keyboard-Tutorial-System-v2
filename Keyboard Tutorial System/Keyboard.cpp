#include "stdafx.h"
#include "Keyboard.h"

bool rescan::Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

std::optional<rescan::Keyboard::Event> rescan::Keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0)
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	return {};
}

bool rescan::Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

void rescan::Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

std::optional<char> rescan::Keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	return {};
}

bool rescan::Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void rescan::Keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void rescan::Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void rescan::Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void rescan::Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool rescan::Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void rescan::Keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
	TrimBuffer(keybuffer);
}

void rescan::Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void rescan::Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void rescan::Keyboard::ClearState() noexcept
{
	keystates.reset();
}
