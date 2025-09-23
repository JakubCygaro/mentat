#include "state.h"
#include <math.h>
#include <stdlib.h>
#include <locale.h>

static MentatAppState _state = {0};

MentatAppState* mentat_state_ptr(){
    return &_state;
}

void mentat_state_initialize(void){
    _state.operator = '\0';
    _state.argument = NAN;
    _state.result = NAN;
    _state.input_buffer = malloc(256);
    _state.input_buffer_len = 256;
    _state.input_buffer_cursor = 0;
    _state.input_buffer[_state.input_buffer_cursor] = '\0';
    _state.state = MENTAT_ARG1_PENDING;
    struct lconv* locale = localeconv();
    _state.sep = *locale->decimal_point;
}
void mentat_state_free(void) {
    free(_state.input_buffer);
}
