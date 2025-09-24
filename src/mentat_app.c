#include "mentat_app.h"
#include "buttons.h"
#include "mentatui.h"
#include "state.h"
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <glibconfig.h>
#include <gtk/gtk.h>

// static char css[] =
// "#text_box{ font: 48px; color: magenta; }";
//

static gboolean event_key_pressed(GtkWidget* window, guint keyval, guint keycode, GdkModifierType state, GtkEventControllerKey* event_controller)
{
    // g_print("%s\n", gdk_keyval_name(keyval));
    if(state & (GDK_CONTROL_MASK | GDK_ALT_MASK))
        return FALSE;
    switch(keyval){
    case GDK_KEY_0:
    case GDK_KEY_KP_0:
        button_0__clicked(NULL, NULL);
        break;
    case GDK_KEY_1:
    case GDK_KEY_KP_1:
        button_1__clicked(NULL, NULL);
        break;
    case GDK_KEY_2:
    case GDK_KEY_KP_2:
        button_2__clicked(NULL, NULL);
        break;
    case GDK_KEY_3:
    case GDK_KEY_KP_3:
        button_3__clicked(NULL, NULL);
        break;
    case GDK_KEY_4:
    case GDK_KEY_KP_4:
        button_4__clicked(NULL, NULL);
        break;
    case GDK_KEY_5:
    case GDK_KEY_KP_5:
        button_5__clicked(NULL, NULL);
        break;
    case GDK_KEY_6:
    case GDK_KEY_KP_6:
        button_6__clicked(NULL, NULL);
        break;
    case GDK_KEY_7:
    case GDK_KEY_KP_7:
        button_7__clicked(NULL, NULL);
        break;
    case GDK_KEY_8:
    case GDK_KEY_KP_8:
        button_8__clicked(NULL, NULL);
        break;
    case GDK_KEY_9:
    case GDK_KEY_KP_9:
        button_9__clicked(NULL, NULL);
        break;
    case GDK_KEY_plus:
    case GDK_KEY_KP_Add:
        button_add__clicked(NULL, NULL);
        break;
    case GDK_KEY_minus:
    case GDK_KEY_KP_Subtract:
        button_sub__clicked(NULL, NULL);
        break;
    case GDK_KEY_multiply:
    case GDK_KEY_KP_Multiply:
        button_mul__clicked(NULL, NULL);
        break;
    case GDK_KEY_division:
    case GDK_KEY_KP_Divide:
        button_div__clicked(NULL, NULL);
        break;
    case GDK_KEY_Return:
    case GDK_KEY_KP_Enter:
        button_enter__clicked(NULL, NULL);
        break;
    case GDK_KEY_period:
    case GDK_KEY_KP_Separator:
        button_dot__clicked(NULL, NULL);
        break;
    case GDK_KEY_Escape:
        button_clear__clicked(NULL, NULL);
        break;
    }
    return TRUE;
}

static GtkWindow* mentat_window_new(MentatApp* app)
{
    GtkBuilder* builder = gtk_builder_new_from_string(UI_STRING, strlen(UI_STRING));
    GtkCssProvider* provider = gtk_css_provider_new();

    GObject* window = gtk_builder_get_object(builder, "mentat_window");
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    GObject* text_view = gtk_builder_get_object(builder, "text_box");
    GtkTextBuffer* text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    GdkDisplay* display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // GBytes* css_bytes = g_bytes_new(css, strlen(css));
    // gtk_css_provider_load_from_bytes(provider, css_bytes);
    //

    GtkEventController* event_controller;
    event_controller = gtk_event_controller_key_new();
    app->state->text_buffer = text_buffer;

    g_signal_connect(event_controller, "key-pressed",
        G_CALLBACK(event_key_pressed),
        GTK_WIDGET(window));

    gtk_widget_add_controller(GTK_WIDGET(window), event_controller);
    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
    g_object_unref(provider);
    return GTK_WINDOW(window);
}

G_DEFINE_TYPE(MentatApp, mentat_app, GTK_TYPE_APPLICATION);

static void mentat_app_init(MentatApp* app)
{
}

static void mentat_app_activate(GApplication* app)
{
    MentatApp* app_m = MENTAT_APP(app);
    mentat_state_initialize();
    MentatAppState* state = mentat_state_ptr();
    app_m->state = state;
    GtkWindow* window = mentat_window_new(app_m);
    // state->input_str = malloc(1);
    // state->input_str[0] = '\0';
    gtk_window_present(GTK_WINDOW(window));
}

static void mentat_app_open(GApplication* app, GFile** files, int n_files, const char* hint)
{
    GtkWindow* window;
    window = mentat_window_new(MENTAT_APP(app));
    gtk_window_present(GTK_WINDOW(window));
}

static void mentat_app_class_init(MentatAppClass* class)
{
    G_APPLICATION_CLASS(class)->activate = mentat_app_activate;
    G_APPLICATION_CLASS(class)->open = mentat_app_open;
}

MentatApp* mentat_app_new(void)
{
    return g_object_new(mentat_app_get_type(),
        "application-id", "org.papieros.mentat",
        "flags", G_APPLICATION_HANDLES_OPEN,
        NULL);
}
