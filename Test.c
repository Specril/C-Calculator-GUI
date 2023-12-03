#include <windows.h>

// WinMain is the entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc; // Define a structure for window class
    HWND hwnd;     // Handle to the window
    MSG msg;       // Message structure for handling messages

    HWND hwndButton; // Declare a handle for the button control
    HWND hwndLabel;  // Declare a handle for the label control

    // Array for positions
    // Array for button handlers

    // Initialize the window class structure
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc; // Default window procedure
    wc.cbClsExtra = 0;              // Extra Bytes for allocation
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;                        // Current instance handle
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // Load the default icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Load the arrow cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);   // Background color brush for the window
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MyWindow";                     // Class name for the window
    wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION); // Load the small icon

    // Register the window class with the operating system
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the main application window
    hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindow", "Calculator GUI", WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 400, 600,
                          NULL, NULL, hInstance, NULL);

    // Check if window creation failed
    if (!hwnd)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Show and update the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    RECT rcClient;
    GetClientRect(hwnd, &rcClient); // Get the client area of the window

    int labelWidth = 350;
    int xPosition = (rcClient.right - rcClient.left - labelWidth) / 2;
    char *labelText = "";

    hwndLabel = CreateWindow(
        "STATIC",                      // Class name
        labelText,                     // Text
        WS_VISIBLE | WS_CHILD,         // Styles
        xPosition, 10, labelWidth, 50, // Position and size
        hwnd,                          // Parent window handle
        (HMENU)2,                      // Label identifier (used for handling messages)
        hInstance,                     // Application instance handle
        NULL                           // Additional data (usually NULL)
    );

    hwndButton = CreateWindow(
        "BUTTON",                                              // Class name
        "Click Me",                                            // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        10, 80, 100, 20,                                       // Position and size
        hwnd,                                                  // Parent window handle
        (HMENU)1,                                              // Button identifier (used for handling messages)
        hInstance,                                             // Application instance handle
        NULL                                                   // Additional data (usually NULL)
    );

    // Enter the message loop to handle window messages
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg); // Translate virtual-key messages into character messages
        DispatchMessage(&msg);  // Dispatch the message to the window procedure

        // Handle WM_COMMAND messages
        switch (msg.message)
        {
        case WM_COMMAND:
            if (LOWORD(msg.wParam) == 1)
            {
                // Button was clicked, perform your action here
                MessageBox(hwnd, "Button Clicked!", "Button Clicked", MB_ICONINFORMATION | MB_OK);

                // Retrieve the handle of the label control by its identifier
                HWND hwndLabel = GetDlgItem(hwnd, 2);

                // Update the label's text
                SetWindowText(hwndLabel, "1");

                // Trigger a repaint of the window to reflect the updated label text
                RedrawWindow(hwndLabel, NULL, NULL, RDW_INVALIDATE);
            }
            break;
        }
    }

    // Return the wParam of the Quit message to terminate the application
    return msg.wParam;
}
