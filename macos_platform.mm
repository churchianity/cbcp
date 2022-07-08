
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>


int copy(const char* stuff) {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSInteger changeCount = [pasteboard clearContents];
    NSString *nsstring = [NSString stringWithUTF8String:stuff];
    NSArray *objectsToCopy = @[nsstring];
    BOOL OK = [pasteboard writeObjects:objectsToCopy];

    if (OK) {
        return 1;
    }

    return 0;
}

