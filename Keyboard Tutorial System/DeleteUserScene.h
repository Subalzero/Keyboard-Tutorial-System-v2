#pragma once

#include "Scene.h"
#include "TextToSpeech.h"
#include "UserList.h"
#include <wrl/client.h>

namespace rescan
{
	class DeleteUserScene : public Scene
	{
	public:
		enum Type
		{
			DeleteUserScene_CANCEL,
			DeleteUserScene_OK
		};
		struct DeleteUserSceneContext
		{
			int returnType;
			User user;
		};

		DeleteUserScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts);
		virtual ~DeleteUserScene();

		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void Begin() override;
		void SetUser(User user);

	private:
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pTextBrush = nullptr;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pSelectedTextBrush = nullptr;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat = nullptr;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> pSelectedTextFormat = nullptr;

		bool isOKSelected = false;

		TextToSpeech* tts;
		User user;
	};
}
