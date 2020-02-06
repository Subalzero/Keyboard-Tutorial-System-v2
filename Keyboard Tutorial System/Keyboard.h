#pragma once

#include <queue>
#include <bitset>
#include <optional>

namespace rescan
{
	class Keyboard
	{
		friend class Window;
	public:
		class Event
		{
		public:

			enum class Type
			{
				Press,
				Release
			};
		private:

			Type type;
			unsigned char code;
		public:

			Event(Type type, unsigned char code) noexcept :
				type(type),
				code(code)
			{}

			bool IsPress() const noexcept
			{
				return type == Type::Press;
			}

			bool IsRelease() const noexcept
			{
				return type == Type::Release;
			}

			unsigned char GetCode() const noexcept
			{
				return code;
			}
		};
	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		// Key events
		bool KeyIsPressed(unsigned char keycode) const noexcept;
		std::optional<Keyboard::Event> ReadKey() noexcept;
		bool KeyIsEmpty() const noexcept;
		void FlushKey() noexcept;
		// Char events
		std::optional<char> ReadChar() noexcept;
		bool CharIsEmpty() const noexcept;
		void FlushChar() noexcept;
		void Flush() noexcept;
		// Autorepeat control
		void EnableAutorepeat() noexcept;
		void DisableAutorepeat() noexcept;
		bool AutorepeatIsEnabled() const noexcept;
	private:
		void OnKeyPressed(unsigned char keycode) noexcept;
		void OnKeyReleased(unsigned char keycode) noexcept;
		void OnChar(char character) noexcept;
		void ClearState() noexcept;
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;
	private:
		static constexpr unsigned int nKeys = 256u;
		static constexpr unsigned int bufferSize = 16u;
		bool autorepeatEnabled = false;
		std::bitset<nKeys> keystates;
		std::queue<Event> keybuffer;
		std::queue<char> charbuffer;
	};
	template<typename T>
	inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > bufferSize)
			buffer.pop();
	}
}

