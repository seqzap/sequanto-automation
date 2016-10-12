//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
#include <UIAutomationClient.h>

#include <sequanto/automation.h>
#include "config.h"

static IUIAutomation * s_client = NULL;
static IUIAutomationElement * s_root = NULL;
static IUIAutomationCondition * s_trueCondition = NULL;

HRESULT InitializeUIAutomation(IUIAutomation **ppAutomation)
{
    return CoCreateInstance(CLSID_CUIAutomation, NULL,
        CLSCTX_INPROC_SERVER, IID_IUIAutomation,
        reinterpret_cast<void**>(ppAutomation));
}

extern "C"
{
    void windows_init_subsystem()
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        InitializeUIAutomation(&s_client);
        s_client->GetRootElement(&s_root);
        s_client->CreateTrueCondition(&s_trueCondition);
    }

    void windows_deinit_subsystem()
    {
        s_root->Release();
        s_root = NULL;
        s_trueCondition->Release();
        s_trueCondition = NULL;
        s_client->Release();
        s_client = NULL;
        CoUninitialize();
    }

    char * windows_bstr_to_utf8(BSTR _buffer)
    {
        int length;
        char * ret;

        if (_buffer == NULL)
        {
            return SQ_STRDUP_FUNCTION("");
        }

        length = WideCharToMultiByte(CP_UTF8, 0, _buffer, -1, NULL, 0, NULL, NULL);

        ret = (char*)malloc(length);

        WideCharToMultiByte(CP_UTF8, 0, _buffer, -1, ret, length, NULL, NULL);

        SysFreeString(_buffer);

        return ret;
    }

    IUIAutomationElement * windows_to_element(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element = NULL;
        if (_pointer->m_length == sizeof(IUIAutomationElement*))
        {
            memcpy(&element, _pointer->m_start, sizeof(IUIAutomationElement*));
        }
        return element;
    }

    SQByteArray * windows_from_element(const IUIAutomationElement * _element)
    {
        SQByteArray * ret = sq_byte_array_create_prealloc(sizeof(IUIAutomationElement*));
        memcpy(ret->m_start, &_element, sizeof(IUIAutomationElement*));
        return ret;
    }

    int windows_desktops(void)
    {
        return 1;
    }

    SQByteArray * windows_desktop(int _desktop)
    {
        return windows_from_element(s_root);
    }

    void windows_ref(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element = windows_to_element(_pointer);
        if (element != NULL)
        {
            element->AddRef();
        }
    }

    void windows_unref(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element = windows_to_element(_pointer);
        if (element != NULL)
        {
            element->Release();
        }
    }

    char * windows_name(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        BSTR buffer;

        element = windows_to_element(_pointer);

        if (element == NULL)
        {
            return SQ_STRDUP_FUNCTION("ERROR: Element no longer exists.");
        }
        element->get_CurrentName(&buffer);

        return windows_bstr_to_utf8(buffer);
    }

    char * windows_role(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        //VARIANT value;
        BSTR value;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return SQ_STRDUP_FUNCTION("ERROR: Element no longer exists.");
        }

        //if (SUCCEEDED(element->GetCurrentPropertyValue(UIA_LegacyIAccessibleRolePropertyId, &value)))
        if (SUCCEEDED(element->get_CurrentClassName(&value)))
        {
            /*
            char * valueName = (char*)malloc(100);
            GetRoleTextA(value.intVal, valueName, 100);
            return valueName;
            */
            return windows_bstr_to_utf8(value);
        }
        else
        {
            return SQ_STRDUP_FUNCTION("");
        }
    }

    int windows_process_id(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        int processId;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return -1;
        }

        if (SUCCEEDED(element->get_CurrentProcessId(&processId)))
        {
            return processId;
        }
        else
        {
            return -1;
        }
    }

    int windows_x(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        RECT rect;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return -1;
        }

        element->get_CurrentBoundingRectangle(&rect);

        return rect.left;
    }

    int windows_y(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        RECT rect;

        element = windows_to_element(_pointer);

        if (element == NULL)
        {
            return -1;
        }

        element->get_CurrentBoundingRectangle(&rect);

        return rect.top;
    }

    int windows_width(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        RECT rect;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return -1;
        }

        element->get_CurrentBoundingRectangle(&rect);

        return rect.right - rect.left;
    }

    int windows_height(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        RECT rect;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return -1;
        }

        element->get_CurrentBoundingRectangle(&rect);

        return rect.bottom - rect.top;
    }

    char * windows_text(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;
        VARIANT value;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return SQ_STRDUP_FUNCTION("ERROR: Element no longer exists.");
        }

        if (SUCCEEDED(element->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &value)))
        {
            return windows_bstr_to_utf8(value.bstrVal);
        }
        else if (SUCCEEDED(element->GetCurrentPropertyValue(UIA_LegacyIAccessibleValuePropertyId, &value)))
        {
            return windows_bstr_to_utf8(value.bstrVal);
        }
        else
        {
            return SQ_STRDUP_FUNCTION("");
        }
    }

    long windows_children(const SQByteArray * _pointer)
    {
        IUIAutomationElement * element;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return 0;
        }

        int length = 0;
        IUIAutomationElementArray * children;
        if (SUCCEEDED(element->FindAll(TreeScope_Children, s_trueCondition, &children)))
        {
            children->get_Length(&length);
            children->Release();
        }
        return length;
    }

    SQByteArray * windows_child(const SQByteArray * _pointer, long _child)
    {
        IUIAutomationElement * element;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return sq_byte_array_create_prealloc(0);
        }

        int length = 0;
        IUIAutomationElementArray * children;
        if (SUCCEEDED(element->FindAll(TreeScope_Children, s_trueCondition, &children)))
        {
            if (SUCCEEDED(children->get_Length(&length)))
            {
                if (_child < length)
                {
                    IUIAutomationElement * elementChild;
                    if (SUCCEEDED(children->GetElement(_child, &elementChild)))
                    {
                        children->Release();
                        return windows_from_element(elementChild);
                    }
                }
            }
            children->Release();
        }
        return sq_byte_array_create_prealloc(0);
    }

    int windows_actions(SQByteArray * _pointer)
    {
        IUIAutomationElement * element;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return 0;
        }

        IUIAutomationInvokePattern * invokePattern = NULL;
        if (SUCCEEDED(element->GetCurrentPatternAs(UIA_InvokePatternId, IID_IUIAutomationInvokePattern, reinterpret_cast<void**>((&invokePattern)))))
        {
            if (invokePattern != NULL)
            {
                invokePattern->Release();
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }

    char * windows_action_name(SQByteArray * _pointer, int _actionIndex)
    {
        IUIAutomationElement * element;

        element = windows_to_element(_pointer);
        if (element == NULL)
        {
            return SQ_STRDUP_FUNCTION("ERROR: Element no longer exists.");
        }

        return SQ_STRDUP_FUNCTION("invoke");
    }

    void windows_action_do(SQByteArray * _pointer, int _actionIndex)
    {
        IUIAutomationElement * element;

        element = windows_to_element(_pointer);
        if (element != NULL)
        {
            IUIAutomationInvokePattern * invokePattern = NULL;
            if (SUCCEEDED(element->GetCurrentPatternAs(UIA_InvokePatternId, IID_IUIAutomationInvokePattern, reinterpret_cast<void**>((&invokePattern)))))
            {
                if (invokePattern != NULL)
                {
                    invokePattern->Invoke();
                    invokePattern->Release();
                }
            }
        }
    }

    HBITMAP CopyScreenToBitmap(HDC displayDC, LPRECT lpRect)
    {
        HDC         hMemDC;         // screen DC and memory DC
        int         nX, nY, nX2, nY2;       // coordinates of rectangle to grab
        int         nWidth, nHeight;        // DIB width and height
        int         xScrn, yScrn;           // screen resolution

        HGDIOBJ     hOldBitmap, hBitmap;

        // check for an empty rectangle
        if (IsRectEmpty(lpRect))
            return NULL;
        // create a DC for the screen and create
        // a memory DC compatible to screen DC

        hMemDC = CreateCompatibleDC(displayDC);      // get points of rectangle to grab

        nX = lpRect->left;
        nY = lpRect->top;
        nX2 = lpRect->right;
        nY2 = lpRect->bottom;      // get screen resolution

        xScrn = GetDeviceCaps(displayDC, HORZRES);
        yScrn = GetDeviceCaps(displayDC, VERTRES);

        //make sure bitmap rectangle is visible

        if (nX < 0)
            nX = 0;

        if (nY < 0)
            nY = 0;

        if (nX2 > xScrn)
            nX2 = xScrn;

        if (nY2 > yScrn)
            nY2 = yScrn;

        nWidth = nX2 - nX;
        nHeight = nY2 - nY;

        // create a bitmap compatible with the screen DC

        hBitmap = CreateCompatibleBitmap(displayDC, nWidth, nHeight);

        // select new bitmap into memory DC

        hOldBitmap = SelectObject(hMemDC, hBitmap);

        // bitblt screen DC to memory DC

        BitBlt(hMemDC, 0, 0, nWidth, nHeight, displayDC, nX, nY, SRCCOPY);

        // select old bitmap back into memory DC and get handle to
        // bitmap of the screen

        hBitmap = SelectObject(hMemDC, hOldBitmap);

        DeleteDC(hMemDC);

        return (HBITMAP)hBitmap;
    }


    SQByteArray * SaveToByteArray(HDC displayDC, HBITMAP hBitmap)
    {
        int iBits;
        WORD wBitCount;
        DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
        BITMAP Bitmap;
        BITMAPFILEHEADER bmfHdr;
        BITMAPINFOHEADER bi;
        LPBITMAPINFOHEADER lpbi;
        HANDLE hDib, hPal, hOldPal = NULL;
        SQByteArray * ret;

        iBits = GetDeviceCaps(displayDC, BITSPIXEL) * GetDeviceCaps(displayDC, PLANES);
        DeleteDC(displayDC);

        if (iBits <= 1)
            wBitCount = 1;
        else if (iBits <= 4)
            wBitCount = 4;
        else if (iBits <= 8)
            wBitCount = 8;
        else
            wBitCount = 24;
        GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = Bitmap.bmWidth;
        bi.biHeight = Bitmap.bmHeight;
        bi.biPlanes = 1;
        bi.biBitCount = wBitCount;
        bi.biCompression = BI_RGB;
        bi.biSizeImage = 0;
        bi.biXPelsPerMeter = 0;
        bi.biYPelsPerMeter = 0;
        bi.biClrImportant = 0;
        bi.biClrUsed = 0;
        dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

        hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
        lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
        *lpbi = bi;

        hPal = GetStockObject(DEFAULT_PALETTE);
        if (hPal)
        {
            displayDC = GetDC(NULL);
            hOldPal = SelectPalette(displayDC, (HPALETTE)hPal, FALSE);
            RealizePalette(displayDC);
        }


        GetDIBits(displayDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
            + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

        if (hOldPal)
        {
            SelectPalette(displayDC, (HPALETTE)hOldPal, TRUE);
            RealizePalette(displayDC);
            ReleaseDC(NULL, displayDC);
        }

        bmfHdr.bfType = 0x4D42; // "BM"
        dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
        bmfHdr.bfSize = dwDIBSize;
        bmfHdr.bfReserved1 = 0;
        bmfHdr.bfReserved2 = 0;
        bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

        ret = sq_byte_array_create_prealloc(sizeof(BITMAPFILEHEADER) + dwDIBSize);
        memcpy(ret->m_start, &bmfHdr, sizeof(BITMAPFILEHEADER));
        memcpy(ret->m_start + sizeof(BITMAPFILEHEADER), lpbi, dwDIBSize);

        GlobalUnlock(hDib);
        GlobalFree(hDib);
        return ret;
    }

    SQByteArray * windows_capture_screen(int _desktopIndex)
    {
        HWND desktopWindow;
        RECT windowRect;
        HBITMAP bitmap;
        HDC displayDC;
        SQByteArray * ret;

        desktopWindow = GetDesktopWindow();
        GetWindowRect(desktopWindow, &windowRect);
        displayDC = CreateDC("DISPLAY", NULL, NULL, NULL);
        bitmap = CopyScreenToBitmap(displayDC, &windowRect);
        ret = SaveToByteArray(displayDC, bitmap);
        DeleteObject(bitmap);
        return ret;
    }
}
