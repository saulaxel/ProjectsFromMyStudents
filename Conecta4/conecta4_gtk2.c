#include <gtk/gtk.h>
#include <stdio.h>

void clic_poner_pieza (GtkWidget *boton, gpointer num_boton);
void empezar_nuevo (GtkWidget *boton, gpointer num_boton);

enum { COLUMNAS = 7, FILAS = 6 };

int alturas[COLUMNAS] = { 0 };
unsigned turno_jugador = 0;

GtkWidget *ventana; // Ventana
GtkWidget *vbox_contenedorPrincipal, *hbox_tablero, *vbox_columnas[COLUMNAS]; // Contenedores
GtkWidget *btn_nuevo_juego, *btn_poner_pieza[COLUMNAS]; // Botones
GtkWidget *img_pos[COLUMNAS][FILAS]; // Imágenes

int main (int argc, char *argv[]) {
    gtk_init(&argc,&argv);

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(ventana, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    btn_nuevo_juego = gtk_button_new_with_mnemonic("Empezar de nuevo");
    g_signal_connect(btn_nuevo_juego, "clicked", G_CALLBACK(empezar_nuevo), NULL);

    int dato[COLUMNAS];
    hbox_tablero = gtk_hbox_new(0,0);
    for (int col = 0; col < COLUMNAS; col++) {
        char etiqueta[] = { '_', col + '1', '\0' };
        btn_poner_pieza[col] = gtk_button_new_with_mnemonic(etiqueta);
        dato[col] = col;
        g_signal_connect(btn_poner_pieza[col], "clicked", G_CALLBACK(clic_poner_pieza), &dato[col]);

        vbox_columnas[col] = gtk_vbox_new(0, 0);
        gtk_box_pack_start(GTK_BOX(vbox_columnas[col]), btn_poner_pieza[col], 1, 1, 0);
        for (int fila = 0; fila < FILAS; fila++) {
            img_pos[col][fila] = gtk_image_new_from_file("blanco.png");
            gtk_box_pack_start(GTK_BOX(vbox_columnas[col]), img_pos[col][fila], 1, 1, 0);
        }
        gtk_box_pack_start(GTK_BOX(hbox_tablero), vbox_columnas[col], 1, 1, 0);
    }

    vbox_contenedorPrincipal = gtk_vbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(vbox_contenedorPrincipal), btn_nuevo_juego, 1, 1 ,0);
    gtk_box_pack_start(GTK_BOX(vbox_contenedorPrincipal), hbox_tablero, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER(ventana), vbox_contenedorPrincipal);
    gtk_widget_show_all(ventana);
    gtk_main();
}

void clic_poner_pieza (GtkWidget *boton, gpointer num_boton) {
    (void)boton; // No se usa el argumento boton

    const char * nombre_imagen = (turno_jugador % 2 ? "rojo.png" : "negro.png");
    int col = *(int *)num_boton;
    int fila = FILAS - alturas[col] - 1;

    if (alturas[col] != FILAS) {
        // Solamente se inserta una pieza si no está llena la columna
        gtk_image_set_from_file(GTK_IMAGE(img_pos[col][fila]), nombre_imagen);

        turno_jugador += 1; // Cambia de turno
        alturas[col] += 1;  // Se metió una pieza, la altura aumenta en la columna
    }
}

void empezar_nuevo (GtkWidget *boton, gpointer num_boton) {
    (void)boton, (void)num_boton; // No se usan los argumentos

    turno_jugador = 0;
    for (int col = 0; col < COLUMNAS; col++) {
        alturas[col] = 0;
        for (int fila = 0; fila < FILAS; fila++) {
            gtk_image_set_from_file(GTK_IMAGE(img_pos[col][fila]), "blanco.png");
        }
    }
}
