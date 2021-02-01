#ifndef __GLWINDOW_H__
#define __GLWINDOW_H__
#include <windows.h>
#include <tchar.h>
#include "device.h"
#include "../base/camera.h"
#include "../base/Texture.h"
#include "Graphic.h"
namespace GLM{
    class GLWindow;
    typedef void(*__CALLBACK)(GLWindow&);

    typedef void(*__MOUSE_CALLBACK)(double, double);
    enum KeyState{KEY_UP,KEY_DOWN};
    class GLWindow{
    private:
        Graphic* graphic;
    public:


        
        Device device;
        HWND screen_handle;		// 主窗口 HWND
        HDC screen_dc;			// 配套的 HDC
        HBITMAP screen_hb;		// DIB
        HBITMAP screen_ob;		// 老的 BITMAP
        unsigned char *screen_fb;		// frame buffer
        long screen_pitch = 0;
        GLWindow();
        ~GLWindow();
        int create(int w,int h,const TCHAR* title);
        int close();
        void update();
        void dispatch();


        static LRESULT screen_events(HWND hWnd, UINT msg,
        WPARAM wParam, LPARAM lParam);
        KeyState getKeyState(int VK);

    public:
        void loop();
        void setView(Matrix4f& view);
        Graphic& createGraphic();

        __CALLBACK onDraw;
        static __MOUSE_CALLBACK onMouseMove;
    
    };
}
#endif