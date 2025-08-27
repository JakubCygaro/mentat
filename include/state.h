#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>
typedef struct _MentatAppState {
    GtkTextBuffer* text_buffer;
    char* input_buffer;
    size_t input_buffer_len;
    size_t input_buffer_cursor;

    // size_t current_token_len;

    double result;
    double argument_1;
    char operator;
} MentatAppState;

void mentat_state_initialize(void);
MentatAppState* mentat_state_ptr(void);
void mentat_state_free(void);



#endif
