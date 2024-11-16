#include <Strype.h>
#include <Strype/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Strype {

	class HazelEditor : public Application
	{
	public:
		HazelEditor()
			: Application("Strype Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HazelEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}

}