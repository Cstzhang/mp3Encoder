//
//  Mp3Encoder.cpp
//  Mp3Encoder
//
//  Created by zhangzb on 2018/9/16.
//  Copyright © 2018年 zhangzb. All rights reserved.
//

#include "Mp3Encoder.hpp"
#include  <stdlib.h>
#include  <stdio.h>
#include  <unistd.h>
Mp3Encoder::Mp3Encoder(){
    
}
int Mp3Encoder::Init(const char *pcmFilePath,
                     const char *mp3FilePath,
                     int sampleRate,
                     int channels,
                     int bitRate){
    int returnCode = -1;
    //read file stream
    pcmFile = fopen(pcmFilePath, "rb+");
    if (pcmFile) {
        mp3File = fopen(mp3FilePath, "wb+");
    }
    if (mp3File) {
        //init lameClient
        lameClient = lame_init();
        lame_set_in_samplerate(lameClient, sampleRate);//set input sampleRate
        lame_set_out_samplerate(lameClient, sampleRate);// set output sampleRate
        lame_set_num_channels(lameClient, channels); //set channels
        lame_set_brate(lameClient, bitRate);//set bitRate
        lame_set_quality(lameClient, 2); //set transcoding quality high
        lame_init_params(lameClient);//Complete set
    }
    return returnCode;
}



void Mp3Encoder::EncodeFile(){
    //
    printf("start encode \n");
    fseek(pcmFile, 4*1024, SEEK_CUR);
    
    //
    int bufferSize = 256 * 1024;
    short *buffer      = new short[bufferSize/2];
    short *leftBuffer  = new short[bufferSize/4];
    short *rightBuffer = new short[bufferSize/4];
    unsigned char* mp3_buffer = new unsigned char[bufferSize];
    size_t readBufferSize = 0;
    
    while ((readBufferSize = fread(buffer, 2, bufferSize/2, pcmFile))>0) {
        for (int i = 0; i < readBufferSize; i ++) {
            if (i % 2 == 0) {
                leftBuffer[i/2]  = buffer[i];
            }else{
                rightBuffer[i/2] = buffer[i];
            }
        }
        size_t wroteSize = lame_encode_buffer(lameClient, (short int *)leftBuffer, (short int *)rightBuffer, (int)(readBufferSize/2), mp3_buffer, bufferSize);
        fwrite(mp3_buffer, 1, wroteSize, mp3File);

    }
    //set mp3 VBR Tag
    lame_mp3_tags_fid(lameClient, mp3File);
    delete []buffer;
    delete []leftBuffer;
    delete []rightBuffer;
    delete []mp3_buffer;
    printf("finish encode \n");
}

void Mp3Encoder::Destory(){
    if (pcmFile) {
        fclose(pcmFile);
    }
    if (mp3File) {
        fclose(mp3File);
        lame_close(lameClient);
    }
    
}

Mp3Encoder::~Mp3Encoder(){
    
}
