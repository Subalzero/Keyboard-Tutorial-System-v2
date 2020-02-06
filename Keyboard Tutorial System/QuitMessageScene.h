#pragma once

#include "Scene.h"
#include "TextToSpeech.h"
#include <wrl/client.h>

namespace rescan
{
	class QuitMessageScene : public Scene
	{
	public:
		enum Type
		{
			QuitMessageScene_CANCEL,
			QuitMessageScene_OK
		};
		struct QuitMessageSceneContext
		{
			int returnType;
		};

		QuitMessageScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts);
		virtual ~QuitMessageScene();

		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void Begin() override;

	private:
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pTextBrush = nullptr;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pSelectedTextBrush = nullptr;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat = nullptr;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> pSelectedTextFormat = nullptr;
		
		bool isOKSelected = false;

		TextToSpeech* tts;
	};
}

