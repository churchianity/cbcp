

// @TODO
int copy(const char* stuff, int length) {
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, length);
    memcpy(GlobalLock(hMem), output, length);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return 0;
}

