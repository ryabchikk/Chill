#include "chpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Chill {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): m_WindowHandle(windowHandle)
    {
        CH_CORE_ASSERT(windowHandle != nullptr, "Invalid window handle provided");
    }

    void OpenGLContext::Initialize()
    {
        CH_PROFILE_FUNCTION();

        AddContext();
        LoadOpenGLLoader();
        LogGraphicsInfo();
    }

    void OpenGLContext::AddContext()
    {
        glfwMakeContextCurrent(m_WindowHandle);
    }
    
    void OpenGLContext::LoadOpenGLLoader()
    {
        const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        CH_CORE_ASSERT(gladStatus, "GLAD initialization failed");
    }

    void OpenGLContext::LogGraphicsInfo()
    {
        CH_CORE_INFO("OpenGL Graphics Information:");

        LogGraphicsProperty("Vendor", GL_VENDOR);
        LogGraphicsProperty("Renderer", GL_RENDERER);
        LogGraphicsProperty("Version", GL_VERSION);
    }

    void OpenGLContext::LogGraphicsProperty(const char* propertyName, GLenum glPropertyEnum) 
    {
        const char* propertyValue = reinterpret_cast<const char*>(glGetString(glPropertyEnum));

        CH_CORE_INFO("  {0}: {1}", propertyName, propertyValue);
    }

    void OpenGLContext::SwapBuffers()
    {
        CH_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }

}