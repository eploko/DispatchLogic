//
//  NSArray+DispatchLogic.h
//  DispatchLogic
//
//  Created by Andrey Subbotin on 5/15/11.
//  Copyright 2011 Plokodelika. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSArray (DispatchLogic)

- (NSArray *)arrayByMappingUsingBlock:(id (^)(id obj, NSUInteger idx))block;

@end
