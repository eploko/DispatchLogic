//
//  DLTimer.m
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import "DLTimer.h"


@implementation DLTimer

#pragma mark - Life-cycle management

- (id)initWithTimeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue block:(DLSimpleBlock)block {
    if ((self = [super init])) {
        // create our timer source
        _timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
        
        // set the time to fire (we're only going to fire once, so just fill in the initial time).
        dispatch_source_set_timer(_timer, dispatch_time(DISPATCH_TIME_NOW, timeout), DISPATCH_TIME_FOREVER, 0);        
        
        // Hey, let's actually do something when the timer fires!
        dispatch_source_set_event_handler(_timer, ^{
            block();
            @synchronized (self) {
                dispatch_source_cancel(_timer);                                
            }
        });        
        dispatch_source_set_cancel_handler(_timer, ^{
            @synchronized (self) {
                dispatch_release(_timer), _timer = NULL;                                
            }
        });        
        dispatch_resume(_timer);            
    }
    return self;
}

- (void)dealloc {
    if (_timer) {
        dispatch_source_cancel(_timer);  
        dispatch_release(_timer), _timer = NULL;        
    }
    [super dealloc];
}

#pragma mark - Public methods

- (void)invalidate {
    @synchronized (self) {
        if (_timer) {
            dispatch_source_cancel(_timer);        
        }        
    }
}

@end
