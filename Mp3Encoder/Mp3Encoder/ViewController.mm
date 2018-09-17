//
//  ViewController.m
//  Mp3Encoder
//
//  Created by zhangzb on 2018/9/16.
//  Copyright © 2018年 zhangzb. All rights reserved.
//

#import "ViewController.h"
#import "Mp3Encoder.hpp"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    

//    [self testEncoder];
    

}




#pragma mark ——— test
- (void)testEncoder{
    Mp3Encoder encoder;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    NSString *mp3Path = [documentDirectory stringByAppendingString:@"/test.mp3"];
    encoder.Init([@"/Users/zhangzb/Dev/Mp3Encoder/Mp3Encoder/apple.pcm" UTF8String], [mp3Path UTF8String], 8000, 2, 256);
    encoder.EncodeFile();
    encoder.Destory();
    NSLog(@"%@", mp3Path);
}

@end
