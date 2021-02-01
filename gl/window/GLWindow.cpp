#include "GLWindow.h"

namespace GLM {
    int screen_w, screen_h, screen_exit = 0;
    int screen_mx = 0, screen_my = 0, screen_mb = 0;
    KeyState screen_keys[512];    // 当前键盘按下状态
    LRESULT GLWindow::screen_events(HWND hWnd, UINT msg,
                                    WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_CLOSE:
                screen_exit = 1;
                break;
            case WM_KEYDOWN:
                screen_keys[wParam & 511] = KEY_DOWN;
                break;
            case WM_KEYUP:
                screen_keys[wParam & 511] = KEY_UP;
                break;
            default:
                return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        return 0;
    }

    GLWindow::GLWindow() : screen_handle(NULL), screen_hb(NULL), screen_dc(NULL), screen_ob(NULL), screen_fb(NULL),
                           graphic(NULL) {
        onDraw = NULL;
    }

    GLWindow::~GLWindow() {

    }

    int GLWindow::create(int w, int h, const TCHAR *title) {
        WNDCLASS wc = {CS_BYTEALIGNCLIENT, (WNDPROC) screen_events, 0, 0, 0,
                       NULL, NULL, NULL, NULL, _T("SCREEN3.1415926")};
        BITMAPINFO bi = {{sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
                                 (DWORD) w * h * 4, 0, 0, 0, 0}};
        RECT rect = {0, 0, w, h};
        int wx, wy, sx, sy;
        LPVOID ptr;
        HDC hDC;

        close();

        wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        if (!RegisterClass(&wc))
            return -1;

        screen_handle = CreateWindow(_T("SCREEN3.1415926"), title,
                                     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                                     0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
        if (screen_handle == NULL)
            return -2;

        screen_exit = 0;
        hDC = GetDC(screen_handle);
        screen_dc = CreateCompatibleDC(hDC);
        ReleaseDC(screen_handle, hDC);

        screen_hb = CreateDIBSection(screen_dc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
        if (screen_hb == NULL)
            return -3;

        screen_ob = (HBITMAP) SelectObject(screen_dc, screen_hb);
        screen_fb = (unsigned char *) ptr;
        screen_w = w;
        screen_h = h;
        screen_pitch = w * 4;

        AdjustWindowRect(&rect, GetWindowLong(screen_handle, GWL_STYLE), 0);
        wx = rect.right - rect.left;
        wy = rect.bottom - rect.top;
        sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
        sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
        if (sy < 0)
            sy = 0;
        SetWindowPos(screen_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
        SetForegroundWindow(screen_handle);

        ShowWindow(screen_handle, SW_NORMAL);
        dispatch();

        memset(screen_keys, 0, sizeof(int) * 512);
        memset(screen_fb, 0, w * h * 4);

        return 0;
    }

    int GLWindow::close() {
        if (screen_dc) {
            if (screen_ob) {
                SelectObject(screen_dc, screen_ob);
                screen_ob = NULL;
            }
            DeleteDC(screen_dc);
            screen_dc = NULL;
        }
        if (screen_hb) {
            DeleteObject(screen_hb);
            screen_hb = NULL;
        }
        if (screen_handle) {
            CloseWindow(screen_handle);
            screen_handle = NULL;
        }
        return 0;
    }

    void GLWindow::dispatch() {
        MSG msg;
        while (1) {
            if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
            if (!GetMessage(&msg, NULL, 0, 0)) break;
            DispatchMessage(&msg);
        }
    }

    void GLWindow::update() {
        HDC hDC = GetDC(screen_handle);
        BitBlt(hDC, 0, 0, screen_w, screen_h, screen_dc, 0, 0, SRCCOPY);
        ReleaseDC(screen_handle, hDC);
        dispatch();
    }

    void GLWindow::loop() {
        int states[] = {RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME};
        int indicator = 0;
        int kbhit = 0;
        float alpha = 1;
        float pos = 3.5;
        Texture texture;

        device.init(screen_w, screen_h, screen_fb);
        camera.atZero(device, 3, 0, 0);

        texture.init();
        texture.bind(device);

        device.render_state = RENDER_STATE_TEXTURE;

        while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0) {
            dispatch();
            device.clear(1);
            camera.atZero(device, pos, 0, 0);

            if (screen_keys[VK_UP]) pos -= 0.01f;
            if (screen_keys[VK_DOWN]) pos += 0.01f;

            if (screen_keys[VK_SPACE]) {
                if (kbhit == 0) {
                    kbhit = 1;
                    if (++indicator >= 3) indicator = 0;
                    device.render_state = states[indicator];
                }
            } else {
                kbhit = 0;
            }
            if (onDraw != NULL) {
                onDraw(*this);
            }
            update();
            Sleep(1);
        }

    }

    Graphic &GLWindow::createGraphic() {

        if (graphic == NULL) {
            graphic = new Graphic(&device);
        }
        return *graphic;
    }

    KeyState GLWindow::getKeyState(int VK) {
        return screen_keys[VK];
    }
} // namespace GLM