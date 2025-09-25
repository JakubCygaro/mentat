#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>
typedef enum _INPUT_MASK {
    INPUT_MASK_CLEAR = 0 << 0,
    INPUT_MASK_ZERO = 1 << 0,
    INPUT_MASK_NEG = 1 << 1,
    INPUT_MASK_DECIMAL = 1 << 2
}INPUT_MASK ;
typedef struct _MentatAppState {
    int input_mask;
    GtkTextBuffer* text_buffer;
    char* input_buffer;
    size_t input_buffer_len;
    size_t input_buffer_cursor;

    // size_t current_token_len;

    double result;
    double argument;
    char operator;
    char sep;
} MentatAppState;

void mentat_state_initialize(void);
MentatAppState* mentat_state_ptr(void);
void mentat_state_free(void);



#endif
