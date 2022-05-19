#pragma once

namespace Saturn
{
    typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define MOUSE_BUTTON_0      ::Saturn::Mouse::Button0
#define MOUSE_BUTTON_1      ::Saturn::Mouse::Button1
#define MOUSE_BUTTON_2      ::Saturn::Mouse::Button2
#define MOUSE_BUTTON_3      ::Saturn::Mouse::Button3
#define MOUSE_BUTTON_4      ::Saturn::Mouse::Button4
#define MOUSE_BUTTON_5      ::Saturn::Mouse::Button5
#define MOUSE_BUTTON_6      ::Saturn::Mouse::Button6
#define MOUSE_BUTTON_7      ::Saturn::Mouse::Button7
#define MOUSE_BUTTON_LAST   ::Saturn::Mouse::ButtonLast
#define MOUSE_BUTTON_LEFT   ::Saturn::Mouse::ButtonLeft
#define MOUSE_BUTTON_RIGHT  ::Saturn::Mouse::ButtonRight
#define MOUSE_BUTTON_MIDDLE ::Saturn::Mouse::ButtonMiddle