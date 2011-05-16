//
//  DLDelegate.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import "DLBlocks.h"
#import "DLProperties.h"

#define EPL_GCD_DELEGATE_IVARS(protocolName) \
    id<protocolName> _delegate; \
    dispatch_queue_t _delegateQueue;

#define EPL_GCD_DELEGATE_DECL(protocolName) \
    - (void)setDelegate:(id<protocolName>)delegate queue:(dispatch_queue_t)queue;

#define EPL_GCD_DELEGATE_PROPERTIES(protocolName) \
    @property (nonatomic, assign) id<protocolName> delegate; \
    @property (nonatomic, assign) dispatch_queue_t delegateQueue;

#define EPL_GCD_DELEGATE_IMPL(protocolName, queueIvar) \
    - (void)setDelegate:(id<protocolName>)delegate queue:(dispatch_queue_t)delegateQueue { \
        DLSimpleBlock block = ^{ \
            self.delegate = delegate; \
            self.delegateQueue = delegateQueue; \
        }; \
        \
        if (dispatch_get_current_queue() == queueIvar) { \
            block(); \
        } else { \
            dispatch_async(queueIvar, block); \
        } \
    } \
    \
    EPL_GCD_OBJ_NAA_PROPERTY(delegate, setDelegate, id<protocolName>, _delegate, queueIvar) \
    EPL_GCD_SIMPLE_NAA_PROPERTY(delegateQueue, setDelegateQueue, dispatch_queue_t, _delegateQueue, queueIvar)

#define EPL_GCD_DELEGATE_RESET \
    { \
        _delegate = nil; \
        if (_delegateQueue) { \
            _delegateQueue = NULL; \
        } \
    }
