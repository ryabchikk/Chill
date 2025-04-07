#pragma once

#include "Chill/Layer.h"
#include "Chill/Events/ApplicationEvent.h"
#include "Chill/Events/KeyEvent.h"
#include "Chill/Events/MouseEvent.h"

namespace Chill {

    class CHILL_API ImGuiLayer:public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };

}


