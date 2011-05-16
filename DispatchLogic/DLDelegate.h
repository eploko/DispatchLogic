//
//  DLDelegate.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import "DLBlocks.h"
#import "DLProperties.h"

#define DLDelegateIvars(protocolName) \
    id<protocolName> _delegate; \
    dispatch_queue_t _delegateQueue;

#define DLDelegateMethodDeclarations(protocolName) \
    - (void)setDelegate:(id<protocolName>)delegate queue:(dispatch_queue_t)queue;

#define DLDelegatePropertyDeclarations(protocolName) \
    @property (nonatomic, assign) id<protocolName> delegate; \
    @property (nonatomic, assign) dispatch_queue_t delegateQueue;

#define DLDelegateImplementation(protocolName, queueIvar) \
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
    DLSynthesizeObjNAAProperty(delegate, setDelegate, id<protocolName>, _delegate, queueIvar) \
    DLSynthesizeSimpleNAAProperty(delegateQueue, setDelegateQueue, dispatch_queue_t, _delegateQueue, queueIvar)

#define DLDelegateReset() \
    { \
        _delegate = nil; \
        if (_delegateQueue) { \
            _delegateQueue = NULL; \
        } \
    }
