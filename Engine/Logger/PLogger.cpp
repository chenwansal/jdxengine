#include "./PLogger.h"
#include <comdef.h>

void PLogger::ConsoleLog(string message) {
    OutputDebugStringA(message.c_str());
}

void PLogger::PopupError(string message) {
    string error_message = "Error: " + message;
    MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void PLogger::PopupErrorWithResult(HRESULT hr, string message) {
    PopupErrorWithResult(hr, StringConverter::StringToWide(message));
}

void PLogger::PopupErrorWithResult(HRESULT hr, wstring message) {
    _com_error error(hr);
    wstring error_message = L"Error: " +
                            message + L"\r\n" +
                            error.ErrorMessage();
    MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void PLogger::PopupException(COMException &ex) {
    wstring error_message = ex.what();
    MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
