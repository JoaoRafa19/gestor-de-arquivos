//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689

#include "./arquivo/arquivo.h"
#include <gtk/gtk.h>

typedef struct
{
    GtkEntry *entry;
    GtkWidget *lb_message;
    GtkWidget *button;
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error;
    PATRICIA patricia;
} Screen;

int countChars(char *s, char c) ;
static void quit(GtkWidget *widget, gpointer data);
static void get_text(GtkWidget *widget, gpointer data);

void imprimePatriciaGTK(PATRICIA P)
{
    if (P == NULL)
        return;
    if (P->tipo == interno)
        imprimePatriciaGTK(P->no.Ninterno.esq);
    if (P->tipo == externo)
        printf("%s\n", P->no.Nexterno.string);
    if (P->tipo == interno)
        imprimePatriciaGTK(P->no.Ninterno.dir);
}

int main(int argc, char *argv[])
{
    Screen *widgets = g_slice_new(Screen);
    gtk_init(&argc, &argv);
    widgets->builder = gtk_builder_new();
    if (gtk_builder_add_from_file(widgets->builder, "../glade/interface.glade", &widgets->error) == 0)
    {
        g_printerr("Error loading file: %s\n", widgets->error->message);
        g_clear_error(&widgets->error);
        return 1;
    }
    widgets->window = GTK_WIDGET(gtk_builder_get_object(widgets->builder, "window"));
    leArquivo(&widgets->patricia, "entrada.txt");
    widgets->lb_message = GTK_WIDGET(gtk_builder_get_object(widgets->builder, "label"));
    widgets->entry = GTK_ENTRY(gtk_builder_get_object(widgets->builder, "entrada"));
    widgets->button = GTK_WIDGET(gtk_builder_get_object(widgets->builder, "button"));
    g_signal_connect(widgets->button, "clicked", G_CALLBACK(get_text), widgets);
    g_signal_connect(widgets->window, "destroy", G_CALLBACK(quit), widgets);
    gtk_widget_show_all(widgets->window);
    gtk_main();
    return 0;
}

static void quit(GtkWidget *widget,
                 gpointer data)
{
    Screen *widgets = (Screen *)data;
    g_print("Palavras: ");
    imprimePatriciaGTK(widgets->patricia);
    g_print("Saindo...\n");
    gtk_main_quit();
}

static void get_text(GtkWidget *widget,
                     gpointer data)
{
    Screen *widgets = (Screen *)data;
    const char *text = gtk_entry_get_text(widgets->entry);
    String termos = (String) malloc(strlen(text)*sizeof(char));
    strcpy(termos, text);
    int c = countChars(termos, ' ') +1;
    int i = 0;
    char *p = strtok(termos, " ");
    char *array[c];
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok(NULL, " ");
    }
    int nFiles;
    String files = getFiles("entrada.txt", NULL, &nFiles);
    String result;
    gchar *display;
    if(strcmp("", termos)==0){
        return;
    }
    buscaDoc(termos, c, widgets->patricia, array, &result);
    display = g_strdup_printf("%s", result);  
    gtk_label_set_text (GTK_LABEL(widgets->lb_message), display); //set label to "display"
    g_free(display);     
}

int countChars(char *s, char c)
{
    return *s == '\0' ? 0 : countChars(s + 1, c) + (*s == c);
}