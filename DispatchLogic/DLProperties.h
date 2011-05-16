//
//  DLProperties.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#pragma mark Property (nonatomic, retain)

#define EPL_GCD_OBJ_NAR_GETTER(getterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_OBJ_NAR_SETTER(setterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_OBJ_NAR_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAR_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAR_SETTER(setterName, ivarType, ivarName, queue)

#pragma mark Property (nonatomic, copy)

#define EPL_GCD_OBJ_NAC_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAR_GETTER(getterName, ivarType, ivarName, queue)

#define EPL_GCD_OBJ_NAC_SETTER(setterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_OBJ_NAC_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAC_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAC_SETTER(setterName, ivarType, ivarName, queue)

#pragma mark Property (nonatomic, assign)

#define EPL_GCD_OBJ_NAA_GETTER(getterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_OBJ_NAA_SETTER(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                ivarName = value; \
            }); \
        } \
    }

#define EPL_GCD_OBJ_NAA_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAA_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_OBJ_NAA_SETTER(setterName, ivarType, ivarName, queue)

#pragma mark Property (nonatomic, assign)

#define EPL_GCD_SIMPLE_NAA_GETTER(getterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_SIMPLE_NAA_SETTER(setterName, ivarType, ivarName, queue) \
    - (void)setterName:(ivarType)value { \
        if (queue == NULL || dispatch_get_current_queue() == queue) { \
            ivarName = value; \
        } else { \
            dispatch_async(queue, ^{ \
                ivarName = value; \
            }); \
        } \
    }

#define EPL_GCD_SIMPLE_NAA_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_SIMPLE_NAA_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_SIMPLE_NAA_SETTER(setterName, ivarType, ivarName, queue)

#pragma mark dispatch_*_t Property (nonatomic, retain)

#define EPL_GCD_DISPATCH_T_NAR_GETTER(getterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_DISPATCH_T_NAR_SETTER(setterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_DISPATCH_T_NAR_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_DISPATCH_T_NAR_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_DISPATCH_T_NAR_SETTER(setterName, ivarType, ivarName, queue)

#pragma mark GCD Block Property (nonatomic, retain)

#define EPL_GCD_BLOCK_GETTER(getterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_BLOCK_SETTER(setterName, ivarType, ivarName, queue) \
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

#define EPL_GCD_BLOCK_PROPERTY(getterName, setterName, ivarType, ivarName, queue) \
    EPL_GCD_BLOCK_GETTER(getterName, ivarType, ivarName, queue) \
    EPL_GCD_BLOCK_SETTER(setterName, ivarType, ivarName, queue)
