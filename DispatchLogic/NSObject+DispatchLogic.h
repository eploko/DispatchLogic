//
//  NSObject+DispatchLogic.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSObject (DispatchLogic)

- (void)enqueue:(dispatch_queue_t *)queue async:(dispatch_block_t *)block;

@end
