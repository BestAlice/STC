//
// Created by User on 12/4/2023.
//
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "wav.h"

std::vector<short> karplus_strong_synthesis(const std::vector<int> & freqs, int sampling_rate, int t ){
    //calculate number of samples
    int sample_count = t*sampling_rate;
    //extinction coefficient
    int ext_coef = 97; // in percents

    // generate white noise
    std::vector<int> white_noise(30); //sampling_rate/ min_freq
    std::generate( white_noise.begin(), white_noise.end(), [freqs]()->int{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(-1000,1000);
        return dist(gen)/freqs.size();
    });

    std::vector<int> int_out(t*sampling_rate);
    int sample;
    int sample_time;
    int length;

    //Karplus-Strong string synthesis for every frequency
    for (int current_freq : freqs) {
        sample_time = sampling_rate/current_freq;
        length = current_freq * t;

        // create vector for one of frequencies
        std::vector<int> current_freq_samples(length);

        //insert white noise
        if (white_noise.size() < length)
            current_freq_samples.insert(current_freq_samples.begin(), white_noise.begin(), white_noise.end());
        else
            current_freq_samples.insert(current_freq_samples.begin(), white_noise.begin(), white_noise.begin()+length);

        //filter work
        for (auto sample_num = white_noise.size(); sample_num < length; ++sample_num) {
            sample =  current_freq_samples[sample_num - white_noise.size()] * ext_coef /100;
            current_freq_samples[sample_num] = sample;
            for (int i = 0; i < sample_time; ++i) {
                int_out[sample_num*sample_time + i] += sample;
            }
        }
    }

    //output signal
    std::vector<short> out(t*sampling_rate);

    //norm and cast to in16 (short)
    int norm = *max_element ( int_out.begin() , int_out.end() ,
                              [](int a , int b)->bool{ return abs(a) < abs(b); });
    for (int i = 0; i < sample_count; ++i) {
        out[i]  = (short)(int_out[i] * 32767 / norm);
    }

    return out;
}



bool save_data_to_wav(const std::vector<short> & data, int sampling_rate, const std::string & title){

    //output stream
    std::ofstream out(title + ".wav", std::ifstream::binary);

    //vars for header
    WAV_HEADER wav_hdr;
    size_t file_size = data.size()*sizeof(short) + 44;
    wav_hdr.ChunkSize = file_size - 8;
    wav_hdr.Subchunk1Size = 16;
    wav_hdr.AudioFormat = 1;
    wav_hdr.NumOfChan = 1;
    wav_hdr.SamplesPerSec = sampling_rate;
    wav_hdr.bytesPerSec = sampling_rate * 2;
    wav_hdr.blockAlign = 2;
    wav_hdr.bitsPerSample = 16;
    wav_hdr.Subchunk2Size = data.size()*sizeof(short);

    //write header
    out.write(reinterpret_cast<const char *>(&wav_hdr), sizeof(wav_hdr));

    //write data
    short buff;
    for (int i = 0; i <data.size(); ++i) {
        buff = data[i];
        out.write(reinterpret_cast<char *>(&buff), sizeof(short));
    }

    return true;
}


int main(){
    //create freq vector
    std::vector<int> freqs {2000, 500};
    std::vector<short> signal = karplus_strong_synthesis(freqs, 48000, 4);
    save_data_to_wav(signal, 48000,  "best_music");
    return 0;
}