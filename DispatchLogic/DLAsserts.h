//
//  DLAsserts.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#define DL_ASSERT_QUEUE(queue) NSAssert(dispatch_get_current_queue() == queue, @"The block is called on an invalid queue!")
#define DL_ASSERT_MAIN_QUEUE() DL_ASSERT_QUEUE(dispatch_get_main_queue())
