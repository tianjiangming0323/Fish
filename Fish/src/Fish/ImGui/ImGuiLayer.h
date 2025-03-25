#pragma once

#include "Fish/Layer.h"
#include "Fish/Events/ApplicationEvent.h"
#include "Fish/Events/KeyEvent.h"
#include "Fish/Events/MouseEvent.h"

namespace Fish
{
	class FISH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	//  virtual void OnUpdate();
	//	void OnEvent(Event& event);

		void Begin();
		void End();

	//private:
	//	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	//	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	//	bool OnMouseMovedEvent(MouseMovedEvent& e);
	//	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	//	bool OnKeyPressedEvent(KeyPressedEvent& e);
	//	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	//	bool OnKeyTypedEvent(KeyTypedEvent& e);
	//	bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};

}