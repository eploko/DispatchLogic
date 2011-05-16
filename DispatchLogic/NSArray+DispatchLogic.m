//
//  NSArray+DispatchLogic.m
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import "NSArray+DispatchLogic.h"


@implementation NSArray (DispatchLogic)

- (NSArray *)arrayByMappingUsingBlock:(id (^)(id obj, NSUInteger idx))block 
{
    NSMutableArray *result = [[NSMutableArray alloc] initWithCapacity:[self count]];
    [self enumerateObjectsUsingBlock:^ (id obj, NSUInteger idx, BOOL *stop) {
        [result addObject:block(obj, idx)];
    }];
    return [result autorelease];
}

@end
