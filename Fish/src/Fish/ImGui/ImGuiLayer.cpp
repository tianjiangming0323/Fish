#include "fishpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform//OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Fish/Application.h"

namespace Fish
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}


    //初始化 ImGui 上下文、样式、输入绑定和渲染后端
	void ImGuiLayer::OnAttach()
	{
        ImGui::CreateContext();
        //创建ImGui的上下文，这是使用ImGui的必要步骤，每个ImGui实例需要一个上下文来存储状态
        ImGui::StyleColorsDark();
        //设置ImGui的暗色主题，这影响UI的外观

        ImGuiIO& io = ImGui::GetIO();
        //ImGui的输入输出配置结构
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        //设置io.BackendFlags，添加了鼠标光标和设置鼠标位置的标志，这表明层将处理鼠标输入

        // TEMPORARY: should eventually use Fish key codes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
        //ImGui的虚拟键码映射到GLFW的物理键码。例如，ImGuiKey_Tab对应GLFW_KEY_TAB

        ImGui_ImplOpenGL3_Init("#version 410");
        //初始化OpenGL3的渲染后端，指定GLSL版本为410
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        //获取ImGuiIO& io和应用程序实例，设置显示尺寸为窗口的宽度和高度，这确保ImGui知道当前窗口的大小，正确布局UI元素

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;
        //计算时间差DeltaTime，ImGui需要这个值来处理动画和交互

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        //开始一个新的ImGui帧，准备接收UI指令

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        //显示一个演示窗口ImGui::ShowDemoWindow(&show),这通常是用来测试和展示ImGui功能的一个窗口，用户可以通过这个窗口了解ImGui的各种控件

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //最后渲染ImGui的数据，ImGui::Render()
        //生成绘制数据，然后ImGui_ImplOpenGL3_RenderDrawData将这些数据用OpenGL3渲染出来
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}
}