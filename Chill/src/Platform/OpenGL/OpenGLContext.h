#pragma once

#include "Chill/Renderer/GraphicsContext.h"
#include <glad/glad.h>
#include <GL/GL.h>

struct GLFWwindow;

namespace Chill {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Initialize() override;
        virtual void SwapBuffers() override;
    
    private:
        GLFWwindow* m_WindowHandle;
    
    private:
        void AddContext();
        void LoadOpenGLLoader();
        void LogGraphicsInfo();
        void LogGraphicsProperty(const char* propertyName, GLenum glPropertyEnum);
    };

}

