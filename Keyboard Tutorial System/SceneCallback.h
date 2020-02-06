#pragma once

namespace rescan
{
	class Scene;

	struct SceneCallback
	{
		virtual void SceneHasBegun(Scene* sender, void* context) = 0;
		virtual void SceneHasEnded(Scene* sender, void* context) = 0;
	};
}
