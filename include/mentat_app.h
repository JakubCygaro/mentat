#ifndef MENTAT_APP_H
#define MENTAT_APP_H
#include "state.h"
#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MentatApp, mentat_app, MENTAT, APP, GtkApplication);


struct _MentatApp {
    GtkApplication parent;
    MentatAppState* state;
};

MentatApp* mentat_app_new(void);
#endif
