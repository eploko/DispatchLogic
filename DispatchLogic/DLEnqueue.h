//
//  DLEnqueue.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#define DL_SAFELY_SYNC_BLOCK_ON_QUEUE(block, queue) \
    if (dispatch_get_current_queue() == queue) { \
        block(); \
    } else { \
        dispatch_sync(queue, block);\
    }

#define DL_INLINE_ASYNC_BLOCK_ON_QUEUE(block, queue) \
    if (dispatch_get_current_queue() == queue) { \
        block(); \
    } else { \
        dispatch_async(queue, block);\
    }
