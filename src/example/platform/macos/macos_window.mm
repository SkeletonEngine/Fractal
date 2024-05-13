#import "macos_window.hpp"
#import <fractal/base/common/base.hpp>

#import <Cocoa/Cocoa.h>

using namespace Fractal::Example;


@interface FlWindow : NSWindow {
}
@end
@implementation FlWindow
@end


@interface FlWindowDelegate : NSObject {
  CocoaWindow* cocoa_window;
}

- (instancetype)initWithCocoaWindow:(CocoaWindow*)initWindow;

@end

@implementation FlWindowDelegate

- (instancetype)initWithCocoaWindow:(CocoaWindow*)initWindow {
  self = [super init];
  if (self != nil)
    cocoa_window = initWindow;

  return self;
}

- (BOOL)windowShouldClose:(id)sender {
  cocoa_window->SetShouldClose();
  return NO;
}

@end


@interface FlContentView : NSView {
}
@end
@implementation FlContentView
@end


namespace Fractal::Example {

CocoaWindow::CocoaWindow() {
  @autoreleasepool {
    [NSApplication sharedApplication];
    
    NSUInteger windowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
    NSRect windowRect = NSMakeRect(0, 0, 640, 480);
    
    FlWindow* window =
      [[FlWindow alloc]
      initWithContentRect:windowRect
      styleMask:windowStyle
      backing:NSBackingStoreBuffered
      defer:NO];
    FL_ASSERT(window);
    [window center];
    
    id delegate = [[FlWindowDelegate alloc] initWithCocoaWindow:this];
    FL_ASSERT(delegate);
    [window setDelegate:delegate];
    
    FlContentView* view = [[FlContentView alloc] initWithFrame:windowRect];
    FL_ASSERT(view);
    [window setContentView:view];
    
    [window orderFrontRegardless];
    PollEvents();
    
    // Assign NSView to an id for use in C++ land
    nsview = view;
  }
}

CocoaWindow::~CocoaWindow() {
}

bool CocoaWindow::IsOpen() const {
  return !should_close;
}

void CocoaWindow::PollEvents() {
  @autoreleasepool {

    for (;;) {
      NSEvent* event =
        [NSApp nextEventMatchingMask:NSEventMaskAny
        untilDate:[NSDate distantPast]
        inMode:NSDefaultRunLoopMode
        dequeue:YES];
      
      if (event == nil) break;

      [NSApp sendEvent:event];
    }

  } // autoreleasepool
}

}
