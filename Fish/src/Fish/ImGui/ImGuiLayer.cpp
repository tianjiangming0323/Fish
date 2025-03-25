#include "fishpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
//#include "Platform//OpenGL/ImGuiOpenGLRenderer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "Fish/Application.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

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
        //s022修改以下内容
        // 
        //ImGui::CreateContext();
        ////创建ImGui的上下文，这是使用ImGui的必要步骤，每个ImGui实例需要一个上下文来存储状态
        //ImGui::StyleColorsDark();
        ////设置ImGui的暗色主题，这影响UI的外观

        //ImGuiIO& io = ImGui::GetIO();
        ////ImGui的输入输出配置结构
        //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        ////设置io.BackendFlags，添加了鼠标光标和设置鼠标位置的标志，这表明层将处理鼠标输入

        //// TEMPORARY: should eventually use Fish key codes
        //io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        //io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        //io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        //io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        //io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        //io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        //io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        //io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        //io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        //io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        //io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        //io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        //io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        //io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        //io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        //io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        //io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        //io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        //io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        //io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        //io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
        ////ImGui的虚拟键码映射到GLFW的物理键码。例如，ImGuiKey_Tab对应GLFW_KEY_TAB

        //ImGui_ImplOpenGL3_Init("#version 410");
        ////初始化OpenGL3的渲染后端，指定GLSL版本为410

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    //Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        //关闭并消除上下文
	}

    void ImGuiLayer::Begin()
    {
        //见OnUpdate函数里的第三段
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

	//void ImGuiLayer::OnUpdate()
	//{
 //       ImGuiIO& io = ImGui::GetIO();
 //       Application& app = Application::Get();
 //       io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
 //       //获取ImGuiIO& io和应用程序实例，设置显示尺寸为窗口的宽度和高度，这确保ImGui知道当前窗口的大小，正确布局UI元素

 //       float time = (float)glfwGetTime();
 //       io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
 //       m_Time = time;
 //       //计算时间差DeltaTime，ImGui需要这个值来处理动画和交互

 //       ImGui_ImplOpenGL3_NewFrame();
 //       ImGui::NewFrame();
 //       //开始一个新的ImGui帧，准备接收UI指令

 //       static bool show = true;
 //       ImGui::ShowDemoWindow(&show);
 //       //显示一个演示窗口ImGui::ShowDemoWindow(&show),这通常是用来测试和展示ImGui功能的一个窗口，用户可以通过这个窗口了解ImGui的各种控件

 //       ImGui::Render();
 //       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 //       //最后渲染ImGui的数据，ImGui::Render()
 //       //生成绘制数据，然后ImGui_ImplOpenGL3_RenderDrawData将这些数据用OpenGL3渲染出来
	//}

	//void ImGuiLayer::OnEvent(Event& event)
	//{
 //       EventDispatcher dispatcher(event);
 //       dispatcher.Dispatch<MouseButtonPressedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
 //       dispatcher.Dispatch<MouseButtonReleasedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
 //       dispatcher.Dispatch<MouseMovedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
 //       dispatcher.Dispatch<MouseScrolledEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
 //       dispatcher.Dispatch<KeyPressedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
 //       dispatcher.Dispatch<KeyReleasedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
 //       dispatcher.Dispatch<KeyTypedEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
 //       dispatcher.Dispatch<WindowResizeEvent>(FISH_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

	//}

 //   bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.MouseDown[e.GetMouseButton()] = true;

 //       return false;
 //       //当处理事件时，返回 false 通常表示事件没有被“消费”，即并未完全处理。在这种情况下，我们可能希望其他地方也有机会继续处理这个事件。如果函数返回 true，则表示事件已经被处理了，不需要进一步传播。
 //       //因此，在这段代码中，返回 false 是为了让其他地方也有机会处理鼠标按键按下事件

 //       /*在打开的商城页面中，在点下商品之后，此图层并不会消失，而是等待另一个按钮“购买”被点击后该图层才会消失。
 //       1.点击商品时，整体事件并没有处理完
 //       2.为了购买按钮的事件能够触发，我们将前一个事件标记为未处理完成，将其进一步传播
 //       3, 直到购买按钮被触发，整个事件完成*/

 //       //函数的返回值bool会传递给事件e的e.Handled
 //   }


 //   bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.MouseDown[e.GetMouseButton()] = false;

 //       return false;
 //   }


 //   bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.MousePos = ImVec2(e.GetX(), e.GetY());

 //       return false;
 //   }


 //   bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.MouseWheelH += e.GetXOffset();
 //       io.MouseWheel += e.GetYOffset();

 //       return false;
 //   }


 //   bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.KeysDown[e.GetKeyCode()] = true;

 //       io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
 //       io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
 //       io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
 //       io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

 //       return false;
 //   }

 //   bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.KeysDown[e.GetKeyCode()] = false;

 //       return false;

 //   }


 //   bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       int keycode = e.GetKeyCode();
 //       if (keycode > 0 && keycode < 0x10000)
 //           io.AddInputCharacter((unsigned short)keycode);

 //       return false;

 //   }

 //   bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
 //   {
 //       ImGuiIO& io = ImGui::GetIO();
 //       io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
 //       io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
 //       glViewport(0, 0, e.GetWidth(), e.GetHeight());
 //       //设置视口（Viewport），用来指定 OpenGL 渲染的目标区域在帧缓冲区中的位置和大小
 //       //void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
 //       //x：指定视口的左下角 X 坐标
 //       //y：指定视口的左下角 Y 坐标
 //       //width：指定视口的宽度
 //       //height：指定视口的高度

 //       return false;
 //   }
}