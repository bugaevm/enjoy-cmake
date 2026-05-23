#include "image_loader.h"

#include <string>

class ImageLoader {
public:
    ImageLoader(const char *resource_path);
    ~ImageLoader();

    void load() const;
    GtkWidget *get();

private:
    GtkWidget *_picture;
};


static void stream_playing(GObject *object, GParamSpec *pspec, gpointer data) {
    GtkMediaStream *media_stream = GTK_MEDIA_STREAM(object);
    GtkWidget *pic = GTK_WIDGET(data);

    if (gtk_media_stream_get_playing(media_stream)) {
        gtk_widget_remove_css_class(pic, "transparent");
    } else {
        gtk_widget_add_css_class(pic, "transparent");
    }
}

ImageLoader::ImageLoader(const char *resource_path)
    : _resource_path(resource_path)
    , _picture(nullptr)
{ }

ImageLoader::~ImageLoader() { }

void ImageLoader::load() const {
    GtkMediaStream *media_stream = gtk_media_file_new_for_resource(_resource_path.c_str());
    _picture = gtk_picture_new_for_paintable(GDK_PAINTABLE(media_stream));

    gtk_picture_set_content_fit(GTK_PICTURE(_picture), GTK_CONTENT_FIT_FILL);

    gtk_widget_add_css_class(_picture, "transparent");
    g_signal_connect(media_stream, "notify::playing", G_CALLBACK(stream_playing), _picture);

    g_object_unref(media_stream);
}

GtkWidget *ImageLoader::get() {
    return _picture;
}

GtkWidget *load_bg_image() {
    auto loader = ImageLoader();
    loader.set_resource_path("/example/EnjoyCMake/background.gif");
    loader.load();
    return loader.get();
}
