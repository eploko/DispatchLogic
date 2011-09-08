//
//  DLProperties.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#pragma mark - Property (nonatomic, retain)

#define DLSynthesizeObjNARGetter(getterName, ivarType, ivarName, queue) \
    - (ivarType)getterName { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            return [[ivarName retain] autorelease]; \
        } else { \
            __block ivarType result = nil; \
            dispatch_sync(queue, ^{ \
                result = [[ivarName retain] autorelease]; \
            }); \
            return result; \
        } \
    }

#define DLSynthesizeObjNARSetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            [value retain]; \
            [ivarName release]; \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                [value retain]; \
                [ivarName release]; \
                ivarName = value; \
            }); \
        } \
    }

#define DLSynthesizeObjNARProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNARGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNARSetter(setterName, ivarType, ivarName, queue)

#pragma mark - Property (nonatomic, copy)

#define DLSynthesizeObjNACGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNARGetter(getterName, ivarType, ivarName, queue)

#define DLSynthesizeObjNACSetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            [ivarName release]; \
            ivarName = [value copy]; \
        } else { \
            dispatch_async(queue, ^{ \
                [ivarName release]; \
                ivarName = [value copy]; \
            }); \
        } \
    }

#define DLSynthesizeObjNACProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNACGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNACSetter(setterName, ivarType, ivarName, queue)

#pragma mark - Property (nonatomic, assign)

#define DLSynthesizeObjNAAGetter(getterName, ivarType, ivarName, queue) \
    - (ivarType)getterName { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            return ivarName; \
        } else { \
            __block ivarType result = nil; \
            dispatch_sync(queue, ^{ \
                result = ivarName; \
            }); \
            return result; \
        } \
    }

#define DLSynthesizeObjNAASetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                ivarName = value; \
            }); \
        } \
    }

#define DLSynthesizeObjNAAProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNAAGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeObjNAASetter(setterName, ivarType, ivarName, queue)

#pragma mark - Property (nonatomic, assign)

#define DLSynthesizeSimpleNAAGetter(getterName, ivarType, ivarName, queue) \
    - (ivarType)getterName { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            return ivarName; \
        } else { \
            __block ivarType result; \
            dispatch_sync(queue, ^{ \
                result = ivarName; \
            }); \
            return result; \
        } \
    }

#define DLSynthesizeSimpleNAASetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                ivarName = value; \
            }); \
        } \
    }

#define DLSynthesizeSimpleNAAProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeSimpleNAAGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeSimpleNAASetter(setterName, ivarType, ivarName, queue)

#pragma mark - dispatch_*_t Property (nonatomic, retain)

#define DLSynthesizeDispatchNARGetter(getterName, ivarType, ivarName, queue) \
    - (ivarType)getterName { \
	    if (dispatch_get_current_queue() == queue) { \
            return ivarName; \
	    } else { \
		    __block ivarType result; \
            dispatch_sync(queue, ^{ \
			    result = ivarName; \
	 	    }); \
		    return result; \
	    } \
    }

#define DLSynthesizeDispatchNARSetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
	    if (dispatch_get_current_queue() == queue) { \
		    if (value) dispatch_retain(value); \
            if (ivarName) dispatch_release(ivarName); \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                if (value) dispatch_retain(value); \
                if (ivarName) dispatch_release(ivarName); \
                ivarName = value; \
            }); \
        } \
    }

#define DLSynthesizeDispatchNARProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeDispatchNARGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeDispatchNARSetter(setterName, ivarType, ivarName, queue)

#pragma mark - GCD Block Property (nonatomic, retain)

#define DLSynthesizeBlockGetter(getterName, ivarType, ivarName, queue) \
    - (ivarType)getterName { \
	    if (dispatch_get_current_queue() == queue) { \
            return [[ivarName retain] autorelease]; \
	    } else { \
		    __block ivarType result; \
            dispatch_sync(queue, ^{ \
			    result = [[ivarName retain] autorelease]; \
	 	    }); \
		    return result; \
	    } \
    }

#define DLSynthesizeBlockSetter(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
	    if (dispatch_get_current_queue() == queue) { \
            ivarType myCopy = [value copy]; \
            [ivarName release]; \
            ivarName = myCopy; \
        } else { \
            dispatch_async(queue, ^{ \
                ivarType myCopy = [value copy]; \
                [ivarName release]; \
                ivarName = myCopy; \
            }); \
        } \
    }

#define DLSynthesizeBlockProperty(getterName, setterName, ivarType, ivarName, queue) \
    DLSynthesizeBlockGetter(getterName, ivarType, ivarName, queue) \
    DLSynthesizeBlockSetter(setterName, ivarType, ivarName, queue)
