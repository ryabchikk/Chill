#include "chpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Chill {

    namespace {
        GLenum ConvertShaderTypeToOpenGL(ShaderDataType type)
        {
            static const std::unordered_map<ShaderDataType, GLenum> type_mapping = {
                {ShaderDataType::Float,  GL_FLOAT},
                {ShaderDataType::Float2, GL_FLOAT},
                {ShaderDataType::Float3, GL_FLOAT},
                {ShaderDataType::Float4, GL_FLOAT},
                {ShaderDataType::Mat3,   GL_FLOAT},
                {ShaderDataType::Mat4,   GL_FLOAT},
                {ShaderDataType::Int,    GL_INT},
                {ShaderDataType::Int2,   GL_INT},
                {ShaderDataType::Int3,   GL_INT},
                {ShaderDataType::Int4,   GL_INT},
                {ShaderDataType::Bool,   GL_BOOL}
            };

            auto it = type_mapping.find(type);
            
            CH_CORE_ASSERT(it != type_mapping.end(), "Unsupported shader data type!");
            
            return it->second;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        CH_PROFILE_FUNCTION();
        
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        CH_PROFILE_FUNCTION();
        
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        CH_PROFILE_FUNCTION();
        
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        CH_PROFILE_FUNCTION();
        
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        CH_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ConvertShaderTypeToOpenGL(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        CH_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}
