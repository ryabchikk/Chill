#pragma once

namespace Chill {

    class GraphicsContext
    {
    public:
        virtual void Initialize() = 0;
        virtual void SwapBuffers() = 0;
        static Scope<GraphicsContext> Create(void* window);
    };

}
