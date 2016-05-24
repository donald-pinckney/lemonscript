//
//  lemonscript_tests.m
//  lemonscript_tests
//
//  Created by Donald Pinckney on 5/23/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <lemonscript/lemonscript.h>
#include <lemonscript/LemonScriptCompiler.h>
#include <string>

#include "PlayTestsShared.h"

#define XCTFailString(s) XCTFail("%s", s.c_str())

using namespace lemonscript;

@interface lemonscript_tests : XCTestCase

@end

@implementation lemonscript_tests

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

- (std::string)auto_test_file_path:(NSString *)auto_name {
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *path = [bundle pathForResource:auto_name ofType:@"auto"];
    if(path == nil) {
        return "DID NOT LOAD FILE";
    }
    
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void)test_make_state {
    try {
        LemonScriptState *state = PlayTestsShared::play_tests_make_state();
        delete state;
    } catch (std::string err) {
        XCTFailString(err);
    }
}

- (void)test_compile_pointturn {
    try {
        LemonScriptState *state = PlayTestsShared::play_tests_make_state();
        
        std::string fileName = [self auto_test_file_path:@"pointturn"];
        
        lemonscript::LemonScriptCompiler *compiler = new lemonscript::LemonScriptCompiler(fileName, state);
        
        while (true) {
            bool isDone = compiler->PeriodicUpdate();
            if(isDone) { break; }
        }
        
        delete state;
        delete compiler;
    } catch (std::string err) {
        XCTFailString(err);
    }
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
