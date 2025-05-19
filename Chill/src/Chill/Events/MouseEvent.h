#pragma once

#include "Chill/Events/Event.h"

namespace Chill {

	class MouseMovedEvent : public Event
	{
		public:
			MouseMovedEvent(float x, float y): mouseX(x), mouseY(y) {}

			inline float GetX() const { return mouseX; }
			inline float GetY() const { return mouseY; }

			std::string ToString() const override
			{
				std::stringstream stringStream;
				stringStream << "MouseMovedEvent: " << mouseX << ", " << mouseY;
				return stringStream.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private:
			float mouseX, mouseY;
	};

	class MouseScrolledEvent : public Event
	{
		public:
			MouseScrolledEvent(float xOffset, float yOffset): offsetX(xOffset), offsetY(yOffset) {}

			inline float GetXOffset() const { return offsetX; }
			inline float GetYOffset() const { return offsetY; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private:
			float offsetX, offsetY;
	};

	class MouseButtonEvent : public Event
	{
		public:
			inline int GetMouseButton() const { return button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		protected:
			MouseButtonEvent(int button): button(button) {}

		int button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
		public:
			MouseButtonPressedEvent(int button): MouseButtonEvent(button) {}

			std::string ToString() const override
			{
				std::stringstream stringStream;
				stringStream << "MouseButtonPressedEvent: " << button;
				return stringStream.str();
			}

			EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
		public:
			MouseButtonReleasedEvent(int button): MouseButtonEvent(button) {}

			std::string ToString() const override
			{
				std::stringstream stringStream;
				stringStream << "MouseButtonReleasedEvent: " << button;

				return stringStream.str();
			}

			EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
