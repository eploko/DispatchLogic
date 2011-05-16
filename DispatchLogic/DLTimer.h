//
//  DLTimer.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "DLBlocks.h"

@interface DLTimer : NSObject {
@private
    dispatch_source_t _timer;
}

- (id)initWithTimeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue block:(DLSimpleBlock)block;

- (void)invalidate;

@end
