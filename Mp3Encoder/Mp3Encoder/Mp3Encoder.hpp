//
//  Mp3Encoder.hpp
//  Mp3Encoder
//
//  Created by zhangzb on 2018/9/16.
//  Copyright © 2018年 zhangzb. All rights reserved.
//

#ifndef Mp3Encoder_hpp
#define Mp3Encoder_hpp

#include <stdio.h>
#include "lame.h"

class Mp3Encoder {
private:
    FILE* pcmFile;
    FILE* mp3File;
    lame_t lameClient;
public:
    Mp3Encoder();
    ~Mp3Encoder();
    
    /**
     pcm to Mp3

     @param pcmFilePath  pcmFilePath
     @param mp3FilePath mp3FilePath
     @param sampleRate sampleRate
     @param channels channels
     @param bitRate bitRate
     @return result
     */
    int Init(const char* pcmFilePath,const char *mp3FilePath,int sampleRate,int channels,int bitRate);
    
    
    /**
     encode local file
     */
    void EncodeFile();
    
    /**
     encode stream to file
     */
    void EncodeStreamToFile();
    
    //Destory
    void Destory();
};

#endif /* Mp3Encoder_hpp */
