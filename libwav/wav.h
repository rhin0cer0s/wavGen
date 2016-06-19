//
// Created by rhinoceros on 6/15/16.
//

#ifndef WAVEGEN_WAVE_H
#define WAVEGEN_WAVE_H

#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define CHANNELS 1
#define FMT_LENGTH 16
#define SAMPLE_RATE 44100
#define SAMPLE_DEPTH 16

/**
 * Take a couple note/octave (A2) and returns its frequence.
 * @param note
 * @param octave
 * @return the note's frequence, -1 on error
 */
double note2Freq(char note, char octave);

/**
 * @param freqs
 * @param notes
 * @param n_notes
 * @return 0 if everything is ok, -1 on error
 */
int notes2Freqs(double * freqs, const char * notes, const int n_notes);

/**
 * Prints the .wav header corresponding to the notes to an open file
 * @param fd an open descriptor in write mode
 * @param bit_depth the bit depth - 8/16/24/32
 * @param sample_rate the sample rate - 8/16/44.1/48kHz
 * @param size
 */
int headerGen(int fd, int bit_depth, int sample_rate, int size);

/*
 * Prints the .wav data corresponding to the notes to an open file
 * @param fd an open descriptof in write mode
 * @param sample_rate the sample rate used in the header
 * @param note_duration the duration of each note in ms
 * @param notes_freq an array containing frequences to write
 * @param n_notes size of the array
 */
int wavGen16bits(int fd, int sample_rate, int note_duration, double *notes_freq, int n_notes);

//int waveGen8bits(int sample_rate, int note_duration, double *notes_freq, int n_notes);
//int waveGen(int bit_depth, int sample_rate, int note_duration, double * notes_freqs, int n_notes);
#endif //WAVEGEN_WAVE_H
