//
// Created by rhinoceros on 6/15/16.
//

#include "wav.h"

double musicFreqs[8][7] = {
        {32.70,     36.71,      41.20,      43.65,      49.00,      55.00,      61.74},
        {65.41,     73.42,      82.41,      87.31,      98.00,      110.00,     123.47},
        {130.81,    146.83,     164.81,     174.61,     196.00,     220.00,     246.94},
        {261.63,    293.66,     329.63,     349.23,     392.00,     440.00,     493.88},
        {523.25,    587.33,     659.25,     698.46,     783.99,     880.00,     987.77},
        {1046.50,   1174.66,    1318.51,    1396.91,    1567.98,    1760.00,    1975.53},
        {2093.00,   2349.32,    2637.02,    2793.83,    3135.96,    3520.00,    3951.07},
        {4186.01,   4698.63,    5274.04,    5587.65,    6271.93,    7040.00,    7902.13}
};

double note2Freq(char note, char octave) {
    if(note == '_'){
        if(octave == '_'){
            return 0.0;
        }
        return -1;
    }

    if(note < 'A' || note > 'G' ) {
        return -1;
    }

    if(octave < '0' || octave > '7') {
        return -1;
    }
    return musicFreqs[octave-48][note-65];
}

int notes2Freqs(double * freqs, const char * notes, const int n_notes) {
    char note = 0;
    char octave = 0;
    double freq = 0.0;

    int i = 0;

    if(n_notes <= 0){
        fprintf(stderr, "Bad input: the number of notes is incoherent %d.\n", n_notes);
        return -1;
    }

    for(i=0; i < n_notes * 2; i+=2) {
        note = notes[i];
        octave = notes[i+1];
        freq = note2Freq(note, octave);

        if(freq < 0){
            fprintf(stderr,"Bad input:%d %c %c\n", i, note, octave);
            return -1;
        } else {
            freqs[i/2] = freq;
        }
    }

    return 0;
}

int headerGen(int fd, int bit_depth, int sample_rate, int data_size) {
    char header[44];
    int length_fmt = FMT_LENGTH;
    short type = 1;
    short channels = CHANNELS;
    short bit_per_sample = (short)bit_depth;
    short block_align = bit_per_sample * channels / (short)8;
    int byte_rate = sample_rate * bit_per_sample * channels / 8;
    int total_size = data_size + 44;
    ssize_t count = 0;

    memset(header, 0, 44 * sizeof(char));

    memcpy(header, "RIFF", 4 * sizeof(char));
    memcpy(header + 4, &total_size, sizeof(int));

    memcpy(header + 8, "WAVE", 4 * sizeof(char));
    memcpy(header + 12, "fmt ", 4 * sizeof(char));
    memcpy(header + 16, &length_fmt, sizeof(int));
    memcpy(header + 20, &type, sizeof(short));
    memcpy(header + 22, &channels, sizeof(short));
    memcpy(header + 24, &sample_rate, sizeof(int));
    memcpy(header + 28, &byte_rate, sizeof(int));
    memcpy(header + 32, &block_align, sizeof(short));
    memcpy(header + 34, &bit_per_sample, sizeof(short));

    memcpy(header + 36, "data", 4 * sizeof(char));
    memcpy(header + 40, &data_size, sizeof(int));

    count = write(fd, header, 44 * sizeof(char));
    if(count < 0) {
        perror("write");
        return -1;
    }

    return 0;
}

int wavGen16bits(int fd, int sample_rate, int note_duration, double *notes_freq, int n_notes) {
    int n_samples = sample_rate * note_duration / 1000;
    double wavelength = 0.0;
    double amplitude_max = 0.0;
    short wave_value = 0;
    ssize_t count = 0;

    int i = 0;
    int j = 0;

    for(i=0; i < n_notes; i++) {
        wavelength = sample_rate / notes_freq[i];
        for(j=0; j < n_samples; j++) {
            amplitude_max = 32767 * sin(M_PI * j / n_samples);
            wave_value = (short)round(amplitude_max * sin(2 * M_PI * (j / wavelength)));

            count = write(fd, &wave_value, sizeof(short));
            if(count < 0){
                perror("write");
                return -1;
            }
        }
    }

    return -1;
}