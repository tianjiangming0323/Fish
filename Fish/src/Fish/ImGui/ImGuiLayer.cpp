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


    //��ʼ�� ImGui �����ġ���ʽ������󶨺���Ⱦ���
	void ImGuiLayer::OnAttach()
	{
        //s022�޸���������
        // 
        //ImGui::CreateContext();
        ////����ImGui�������ģ�����ʹ��ImGui�ı�Ҫ���裬ÿ��ImGuiʵ����Ҫһ�����������洢״̬
        //ImGui::StyleColorsDark();
        ////����ImGui�İ�ɫ���⣬��Ӱ��UI�����

        //ImGuiIO& io = ImGui::GetIO();
        ////ImGui������������ýṹ
        //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        ////����io.BackendFlags��������������������λ�õı�־��������㽫�����������

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
        ////ImGui���������ӳ�䵽GLFW��������롣���磬ImGuiKey_Tab��ӦGLFW_KEY_TAB

        //ImGui_ImplOpenGL3_Init("#version 410");
        ////��ʼ��OpenGL3����Ⱦ��ˣ�ָ��GLSL�汾Ϊ410

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
        //�رղ�����������
	}

    void ImGuiLayer::Begin()
    {
        //��OnUpdate������ĵ�����
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
 //       //��ȡImGuiIO& io��Ӧ�ó���ʵ����������ʾ�ߴ�Ϊ���ڵĿ�Ⱥ͸߶ȣ���ȷ��ImGui֪����ǰ���ڵĴ�С����ȷ����UIԪ��

 //       float time = (float)glfwGetTime();
 //       io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
 //       m_Time = time;
 //       //����ʱ���DeltaTime��ImGui��Ҫ���ֵ���������ͽ���

 //       ImGui_ImplOpenGL3_NewFrame();
 //       ImGui::NewFrame();
 //       //��ʼһ���µ�ImGui֡��׼������UIָ��

 //       static bool show = true;
 //       ImGui::ShowDemoWindow(&show);
 //       //��ʾһ����ʾ����ImGui::ShowDemoWindow(&show),��ͨ�����������Ժ�չʾImGui���ܵ�һ�����ڣ��û�����ͨ����������˽�ImGui�ĸ��ֿؼ�

 //       ImGui::Render();
 //       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 //       //�����ȾImGui�����ݣ�ImGui::Render()
 //       //���ɻ������ݣ�Ȼ��ImGui_ImplOpenGL3_RenderDrawData����Щ������OpenGL3��Ⱦ����
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
 //       //�������¼�ʱ������ false ͨ����ʾ�¼�û�б������ѡ�������δ��ȫ��������������£����ǿ���ϣ�������ط�Ҳ�л��������������¼�������������� true�����ʾ�¼��Ѿ��������ˣ�����Ҫ��һ��������
 //       //��ˣ�����δ����У����� false ��Ϊ���������ط�Ҳ�л��ᴦ����갴�������¼�

 //       /*�ڴ򿪵��̳�ҳ���У��ڵ�����Ʒ֮�󣬴�ͼ�㲢������ʧ�����ǵȴ���һ����ť�����򡱱�������ͼ��Ż���ʧ��
 //       1.�����Ʒʱ�������¼���û�д�����
 //       2.Ϊ�˹���ť���¼��ܹ����������ǽ�ǰһ���¼����Ϊδ������ɣ������һ������
 //       3, ֱ������ť�������������¼����*/

 //       //�����ķ���ֵbool�ᴫ�ݸ��¼�e��e.Handled
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
 //       //�����ӿڣ�Viewport��������ָ�� OpenGL ��Ⱦ��Ŀ��������֡�������е�λ�úʹ�С
 //       //void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
 //       //x��ָ���ӿڵ����½� X ����
 //       //y��ָ���ӿڵ����½� Y ����
 //       //width��ָ���ӿڵĿ��
 //       //height��ָ���ӿڵĸ߶�

 //       return false;
 //   }
}