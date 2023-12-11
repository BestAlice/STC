//
// Created by User on 12/11/2023.
//

#ifndef STC_WAV_H
#define STC_WAV_H

#endif //STC_WAV_H

typedef struct WAV_HEADER {
    /* RIFF Chunk Descriptor */
    unsigned char RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
    unsigned long ChunkSize;                     // RIFF Chunk Size
    unsigned char WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
    /* "fmt" sub-chunk */
    unsigned char fmt[4] = {'f', 'm', 't', ' '}; // FMT header
    unsigned long Subchunk1Size = 16;           // Size of the fmt chunk
    unsigned short AudioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
    // Mu-Law, 258=IBM A-Law, 259=ADPCM
    unsigned short NumOfChan = 1;   // Number of channels 1=Mono 2=Sterio
    unsigned long SamplesPerSec = 16000;   // Sampling Frequency in Hz
    unsigned long bytesPerSec = 16000 * 2; // bytes per second
    unsigned short blockAlign = 2;          // 2=16-bit mono, 4=16-bit stereo
    unsigned short bitsPerSample = 16;      // Number of bits per sample
    /* "data" sub-chunk */
    unsigned char Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
    unsigned long Subchunk2Size;                        // Sampled data length
} ;