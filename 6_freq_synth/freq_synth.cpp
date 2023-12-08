//
// Created by User on 12/4/2023.
//
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include "math.h"



std::shared_ptr<std::vector<int>> freq_synth(const std::vector<int> & data, int sampling_rate, int t ){
    //calculate number of samples
    int sample_count = t*sampling_rate;
    int freq_size = data.size();

    std::vector<int> out;
    //fill out until the filter starts working
    for (int i = 0; i < freq_size; ++i) {
        out.push_back(data[i%freq_size]);
    }

    //Karplus-Strong string synthesis
    for (int i = freq_size; i < sample_count; ++i) {

        out.push_back(
                data[i%freq_size]
                +
                out[i-freq_size]*3/4  // filter
                );
    }

    return std::make_shared<std::vector<int>>(out);
}



bool save_data_to_wav(const std::vector<int> & data, int sampling_rate, const char* title){

    FILE *fp;

    //create filename
    char filename[100];
    std::strcpy(filename, title);
    std::strcat(filename, ".wav");

    fp = fopen(filename, "wb");

    if(fp == NULL) {
        std::cerr << "file can't be opened\n";
        return 0;
    }

    //vars for header
    size_t file_size = data.size()*sizeof(short) + 44;
    unsigned long chunkSize = file_size - 8;
    unsigned long subchunk1Size = 16;
    unsigned long audioFormat = 1;
    unsigned short numChannels = 1;
    unsigned long sampleRate = sampling_rate;
    unsigned long byteRate = sampling_rate * 2;
    unsigned short blockAlign = 2;
    unsigned short bitsPerSample = 16;
    unsigned long subchunk2Size = data.size()*sizeof(short);

    //write Header
    fwrite("RIFF",4,1,fp);
    fwrite(&chunkSize,4,1,fp);
    fwrite("WAVE",4,1,fp);
    fwrite( "fmt ",4,1,fp);
    fwrite( &subchunk1Size,4,1,fp);
    fwrite( &audioFormat,4,1,fp);
    fwrite( &numChannels,2,1,fp);
    fwrite(&sampleRate,4,1,fp);
    fwrite(&byteRate,4,1,fp);
    fwrite(&blockAlign,2,1,fp);
    fwrite(&bitsPerSample,2,1,fp);
    fwrite("data" ,4,1,fp);
    fwrite(&subchunk2Size,4,1,fp);

    //write data
    short buff;
    for (int i = 0; i < data.size(); ++i) {
        buff = (short)data[i];
        fwrite(&buff,sizeof(short),1,fp);
    }
    fclose(fp);

    return 1;
}


int main(){
    //create freq vector
    std::vector<int> data {800, 750, 764, 851};
    std::vector<int> new_data = *freq_synth(data, 100, 1);

    for (int i = 0; i < new_data.size(); ++i) {
        std::cout << new_data[i] << std::endl;
    }

    save_data_to_wav(new_data, 100,  "best_music");
    return 0;
}