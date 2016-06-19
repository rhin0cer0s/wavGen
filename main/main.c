//
// Created by rhinoceros on 6/15/16.
//

#include "main.h"

int main(int argc, char * argv[]) {
    char    *notes = NULL;
    int     n_notes = 0;
    int     note_duration = 0;
    int     num_samples = 0;
    int     data_size = 0;

    double * freqs = NULL;

    if(argc != 3){
        fprintf(stderr,"%s duration notes\n",argv[0]);
        fprintf(stderr, "duration\tduration of each notes in ms.\n");
        fprintf(stderr, "notes\tnotes to play, eg:A0B0C0D0E0F0__.\n");
        return EXIT_FAILURE;
    }

    notes = argv[2];
    note_duration = atoi(argv[1]);

    n_notes = (int)strlen(notes)/2;
    num_samples = n_notes * note_duration * SAMPLE_RATE / 1000;
    data_size = num_samples * CHANNELS * SAMPLE_DEPTH / 8;

    freqs = malloc(n_notes * sizeof(double));
    if (freqs == NULL) {
        return EXIT_FAILURE;
    }

    if (notes2Freqs(freqs, notes, n_notes) < 0){
        return EXIT_FAILURE;
    }

    headerGen(1, SAMPLE_DEPTH, SAMPLE_RATE, data_size);
    wavGen16bits(1, SAMPLE_RATE, note_duration, freqs, n_notes);

    if(freqs != NULL){
        free(freqs);
    }

    return EXIT_SUCCESS;
}