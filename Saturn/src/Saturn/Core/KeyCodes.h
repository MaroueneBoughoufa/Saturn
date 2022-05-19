#pragma once

namespace Saturn
{
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space               = 32,
        Apostrophe          = 39, /* ' */
        Comma               = 44, /* , */
        Minus               = 45, /* - */
        Period              = 46, /* . */
        Slash               = 47, /* / */

        D0                  = 48, /* 0 */
        D1                  = 49, /* 1 */
        D2                  = 50, /* 2 */
        D3                  = 51, /* 3 */
        D4                  = 52, /* 4 */
        D5                  = 53, /* 5 */
        D6                  = 54, /* 6 */
        D7                  = 55, /* 7 */
        D8                  = 56, /* 8 */
        D9                  = 57, /* 9 */

        Semicolon           = 59, /* ; */
        Equal               = 61, /* = */

        A                   = 65,
        B                   = 66,
        C                   = 67,
        D                   = 68,
        E                   = 69,
        F                   = 70,
        G                   = 71,
        H                   = 72,
        I                   = 73,
        J                   = 74,
        K                   = 75,
        L                   = 76,
        M                   = 77,
        N                   = 78,
        O                   = 79,
        P                   = 80,
        Q                   = 81,
        R                   = 82,
        S                   = 83,
        T                   = 84,
        U                   = 85,
        V                   = 86,
        W                   = 87,
        X                   = 88,
        Y                   = 89,
        Z                   = 90,
        LeftBracket         = 91,  /* [ */
        Backslash           = 92,  /* \ */
        RightBracket        = 93,  /* ] */
        GraveAccent         = 96,  /* ` */

        World1              = 161, /* non-US #1 */
        World2              = 162, /* non-US #2 */

        /* Function keys */
        Escape              = 256,
        Enter               = 257,
        Tab                 = 258,
        Backspace           = 259,
        Insert              = 260,
        Delete              = 261,
        Right               = 262,
        Left                = 263,
        Down                = 264,
        Up                  = 265,
        PageUp              = 266,
        PageDown            = 267,
        Home                = 268,
        End                 = 269,
        CapsLock            = 280,
        ScrollLock          = 281,
        NumLock             = 282,
        PrintScreen         = 283,
        Pause               = 284,
        F1                  = 290,
        F2                  = 291,
        F3                  = 292,
        F4                  = 293,
        F5                  = 294,
        F6                  = 295,
        F7                  = 296,
        F8                  = 297,
        F9                  = 298,
        F10                 = 299,
        F11                 = 300,
        F12                 = 301,
        F13                 = 302,
        F14                 = 303,
        F15                 = 304,
        F16                 = 305,
        F17                 = 306,
        F18                 = 307,
        F19                 = 308,
        F20                 = 309,
        F21                 = 310,
        F22                 = 311,
        F23                 = 312,
        F24                 = 313,
        F25                 = 314,
        /* Keypad */
        KP0                 = 320,
        KP1                 = 321,
        KP2                 = 322,
        KP3                 = 323,
        KP4                 = 324,
        KP5                 = 325,
        KP6                 = 326,
        KP7                 = 327,
        KP8                 = 328,
        KP9                 = 329,
        KPDecimal           = 330,
        KPDivide            = 331,
        KPMultiply          = 332,
        KPSubtract          = 333,
        KPAdd               = 334,
        KPEnter             = 335,
        KPEqual             = 336,
        LeftShift           = 340,
        LeftControl         = 341,
        LeftAlt             = 342,
        LeftSuper           = 343,
        RightShift          = 344,
        RightControl        = 345,
        RightAlt            = 346,
        RightSuper          = 347,
        Menu                = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keycode)
    {
        os << static_cast<uint32_t>(keycode);
        return os;
    }
}

#define KEY_SPACE           ::Saturn::Key::Space
#define KEY_APOSTROPHE      ::Saturn::Key::Apostrophe    /* ' */
#define KEY_COMMA           ::Saturn::Key::Comma         /* , */
#define KEY_MINUS           ::Saturn::Key::Minus         /* - */
#define KEY_PERIOD          ::Saturn::Key::Period        /* . */
#define KEY_SLASH           ::Saturn::Key::Slash         /* / */
#define KEY_0               ::Saturn::Key::D0
#define KEY_1               ::Saturn::Key::D1
#define KEY_2               ::Saturn::Key::D2
#define KEY_3               ::Saturn::Key::D3
#define KEY_4               ::Saturn::Key::D4
#define KEY_5               ::Saturn::Key::D5
#define KEY_6               ::Saturn::Key::D6
#define KEY_7               ::Saturn::Key::D7
#define KEY_8               ::Saturn::Key::D8
#define KEY_9               ::Saturn::Key::D9
#define KEY_SEMICOLON       ::Saturn::Key::Semicolon     /* ; */
#define KEY_EQUAL           ::Saturn::Key::Equal         /* = */
#define KEY_A               ::Saturn::Key::A
#define KEY_B               ::Saturn::Key::B
#define KEY_C               ::Saturn::Key::C
#define KEY_D               ::Saturn::Key::D
#define KEY_E               ::Saturn::Key::E
#define KEY_F               ::Saturn::Key::F
#define KEY_G               ::Saturn::Key::G
#define KEY_H               ::Saturn::Key::H
#define KEY_I               ::Saturn::Key::I
#define KEY_J               ::Saturn::Key::J
#define KEY_K               ::Saturn::Key::K
#define KEY_L               ::Saturn::Key::L
#define KEY_M               ::Saturn::Key::M
#define KEY_N               ::Saturn::Key::N
#define KEY_O               ::Saturn::Key::O
#define KEY_P               ::Saturn::Key::P
#define KEY_Q               ::Saturn::Key::Q
#define KEY_R               ::Saturn::Key::R
#define KEY_S               ::Saturn::Key::S
#define KEY_T               ::Saturn::Key::T
#define KEY_U               ::Saturn::Key::U
#define KEY_V               ::Saturn::Key::V
#define KEY_W               ::Saturn::Key::W
#define KEY_X               ::Saturn::Key::X
#define KEY_Y               ::Saturn::Key::Y
#define KEY_Z               ::Saturn::Key::Z
#define KEY_LEFT_BRACKET    ::Saturn::Key::LeftBracket   /* [ */
#define KEY_BACKSLASH       ::Saturn::Key::Backslash     /* \ */
#define KEY_RIGHT_BRACKET   ::Saturn::Key::RightBracket  /* ] */
#define KEY_GRAVE_ACCENT    ::Saturn::Key::GraveAccent   /* ` */
#define KEY_WORLD_1         ::Saturn::Key::World1        /* non-US #1 */
#define KEY_WORLD_2         ::Saturn::Key::World2        /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE          ::Saturn::Key::Escape
#define KEY_ENTER           ::Saturn::Key::Enter
#define KEY_TAB             ::Saturn::Key::Tab
#define KEY_BACKSPACE       ::Saturn::Key::Backspace
#define KEY_INSERT          ::Saturn::Key::Insert
#define KEY_DELETE          ::Saturn::Key::Delete
#define KEY_RIGHT           ::Saturn::Key::Right
#define KEY_LEFT            ::Saturn::Key::Left
#define KEY_DOWN            ::Saturn::Key::Down
#define KEY_UP              ::Saturn::Key::Up
#define KEY_PAGE_UP         ::Saturn::Key::PageUp
#define KEY_PAGE_DOWN       ::Saturn::Key::PageDown
#define KEY_HOME            ::Saturn::Key::Home
#define KEY_END             ::Saturn::Key::End
#define KEY_CAPS_LOCK       ::Saturn::Key::CapsLock
#define KEY_SCROLL_LOCK     ::Saturn::Key::ScrollLock
#define KEY_NUM_LOCK        ::Saturn::Key::NumLock
#define KEY_PRINT_SCREEN    ::Saturn::Key::PrintScreen
#define KEY_PAUSE           ::Saturn::Key::Pause
#define KEY_F1              ::Saturn::Key::F1
#define KEY_F2              ::Saturn::Key::F2
#define KEY_F3              ::Saturn::Key::F3
#define KEY_F4              ::Saturn::Key::F4
#define KEY_F5              ::Saturn::Key::F5
#define KEY_F6              ::Saturn::Key::F6
#define KEY_F7              ::Saturn::Key::F7
#define KEY_F8              ::Saturn::Key::F8
#define KEY_F9              ::Saturn::Key::F9
#define KEY_F10             ::Saturn::Key::F10
#define KEY_F11             ::Saturn::Key::F11
#define KEY_F12             ::Saturn::Key::F12
#define KEY_F13             ::Saturn::Key::F13
#define KEY_F14             ::Saturn::Key::F14
#define KEY_F15             ::Saturn::Key::F15
#define KEY_F16             ::Saturn::Key::F16
#define KEY_F17             ::Saturn::Key::F17
#define KEY_F18             ::Saturn::Key::F18
#define KEY_F19             ::Saturn::Key::F19
#define KEY_F20             ::Saturn::Key::F20
#define KEY_F21             ::Saturn::Key::F21
#define KEY_F22             ::Saturn::Key::F22
#define KEY_F23             ::Saturn::Key::F23
#define KEY_F24             ::Saturn::Key::F24
#define KEY_F25             ::Saturn::Key::F25

/* Keypad */
#define KEY_KP_0            ::Saturn::Key::KP0
#define KEY_KP_1            ::Saturn::Key::KP1
#define KEY_KP_2            ::Saturn::Key::KP2
#define KEY_KP_3            ::Saturn::Key::KP3
#define KEY_KP_4            ::Saturn::Key::KP4
#define KEY_KP_5            ::Saturn::Key::KP5
#define KEY_KP_6            ::Saturn::Key::KP6
#define KEY_KP_7            ::Saturn::Key::KP7
#define KEY_KP_8            ::Saturn::Key::KP8
#define KEY_KP_9            ::Saturn::Key::KP9
#define KEY_KP_DECIMAL      ::Saturn::Key::KPDecimal
#define KEY_KP_DIVIDE       ::Saturn::Key::KPDivide
#define KEY_KP_MULTIPLY     ::Saturn::Key::KPMultiply
#define KEY_KP_SUBTRACT     ::Saturn::Key::KPSubtract
#define KEY_KP_ADD          ::Saturn::Key::KPAdd
#define KEY_KP_ENTER        ::Saturn::Key::KPEnter
#define KEY_KP_EQUAL        ::Saturn::Key::KPEqual

#define KEY_LEFT_SHIFT      ::Saturn::Key::LeftShift
#define KEY_LEFT_CONTROL    ::Saturn::Key::LeftControl
#define KEY_LEFT_ALT        ::Saturn::Key::LeftAlt
#define KEY_LEFT_SUPER      ::Saturn::Key::LeftSuper
#define KEY_RIGHT_SHIFT     ::Saturn::Key::RightShift
#define KEY_RIGHT_CONTROL   ::Saturn::Key::RightControl
#define KEY_RIGHT_ALT       ::Saturn::Key::RightAlt
#define KEY_RIGHT_SUPER     ::Saturn::Key::RightSuper
#define KEY_MENU            ::Saturn::Key::Menu