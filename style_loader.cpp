#include "style_loader.h"

GtkCssProvider *load_css_provider() {
    GtkCssProvider *css_provider = gtk_css_provider_new();

    gtk_css_provider_load_from_resource("/example/EnjoyCMake/style.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default,
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    return css_provder;
}
