#include "state.h"
#include <math.h>
#include <stdlib.h>

static MentatAppState _state = {0};

MentatAppState* mentat_state_ptr(){
    return &_state;
}

void mentat_state_initialize(void){
    _state.operator = '\0';
    _state.argument_1 = NAN;
    // _state.argument_2 = NAN;
    _state.result = 0;
    _state.input_buffer = malloc(256);
    _state.input_buffer_len = 256;
    _state.input_buffer_cursor = 0;
    _state.input_buffer[_state.input_buffer_cursor] = '\0';
}
void mentat_state_free(void) {
    free(_state.input_buffer);
}
