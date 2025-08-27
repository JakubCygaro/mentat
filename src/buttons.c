#include <gtk/gtk.h>
#include "state.h"

#define NUM_BUTTON_CLICKED(N) \
void button_## N ##__clicked(GtkButton* button, gpointer data){\
    MentatAppState* state = mentat_state_ptr();\
    state->input_buffer[state->input_buffer_cursor++] = '0' + N;\
    state->input_buffer[state->input_buffer_cursor] = '\0';\
    g_print("%s\n", state->input_buffer);\
    gtk_text_buffer_insert_at_cursor(state->text_buffer, #N, 1);\
}\

void button_0__clicked(GtkButton* button, gpointer data){
    MentatAppState* state = mentat_state_ptr();
    if(state->input_buffer_cursor == 0){
        state->input_buffer[state->input_buffer_cursor++] = '0';
        state->input_buffer[state->input_buffer_cursor] = '\0';
        g_print("%s\n", state->input_buffer);
        gtk_text_buffer_insert_at_cursor(state->text_buffer, "0", 1);
    }
}

NUM_BUTTON_CLICKED(1)
NUM_BUTTON_CLICKED(2)
NUM_BUTTON_CLICKED(3)
NUM_BUTTON_CLICKED(4)
NUM_BUTTON_CLICKED(5)
NUM_BUTTON_CLICKED(6)
NUM_BUTTON_CLICKED(7)
NUM_BUTTON_CLICKED(8)
NUM_BUTTON_CLICKED(9)
