#include <graphics.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5

struct Producto {
    char nombre[50];
    int cantidad;
    float precio;
};

void mostrarInventarioGrafico(struct Producto inventario[], int numProductos) {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(100, 20, "Inventario de la tienda:");

    int y = 60;
    char buffer[100];
    for (int i = 0; i < numProductos; i++) {
        sprintf(buffer, "Producto: %s, Cantidad: %d, Precio: $%.2f", inventario[i].nombre, inventario[i].cantidad, inventario[i].precio);
        outtextxy(100, y, buffer);
        y += 40;
    }

    outtextxy(100, 400, "Presione cualquier tecla para regresar al menu principal.");
    getch();
}

void capturarTexto(int x1, int y1, int x2, int y2, char* buffer) {
    int pos = 0;
    char ch;
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                setfillstyle(SOLID_FILL, BLACK);
                bar(x1 + 5, y1 + 5, x2 - 5, y2 - 5);
                outtextxy(x1 + 5, y1 + 5, buffer);
            }
        } else {
            buffer[pos] = ch;
            pos++;
            buffer[pos] = '\0';
            outtextxy(x1 + 5, y1 + 5, buffer);
        }
    }
}

void agregarProductoGrafico(struct Producto inventario[], int cantidadesPrecios[][2], int *numProductos) {
    if (*numProductos >= MAX_PRODUCTS) {
        outtextxy(100, 400, "No se pueden agregar más productos. El inventario está lleno.");
        getch();
        return;
    }

    char nombre[50] = "";
    int cantidad;
    float precio;
    char buffer[50];

    cleardevice();
    outtextxy(100, 20, "Agregar Producto");

    outtextxy(100, 60, "Ingrese el nombre del producto:");
    rectangle(100, 80, 400, 110);
    capturarTexto(100, 80, 400, 110, nombre);

    outtextxy(100, 120, "Ingrese la cantidad del producto:");
    rectangle(100, 140, 400, 170);
    capturarTexto(100, 140, 400, 170, buffer);
    cantidad = atoi(buffer);

    outtextxy(100, 180, "Ingrese el precio del producto:");
    rectangle(100, 200, 400, 230);
    capturarTexto(100, 200, 400, 230, buffer);
    precio = atof(buffer);

    strcpy(inventario[*numProductos].nombre, nombre);
    inventario[*numProductos].cantidad = cantidad;
    inventario[*numProductos].precio = precio;

    cantidadesPrecios[*numProductos][0] = cantidad;
    cantidadesPrecios[*numProductos][1] = (int)(precio * 100);

    (*numProductos)++;

    outtextxy(100, 400, "Producto agregado. Presione cualquier tecla para regresar al menu principal.");
    getch();
}

void actualizarProductoGrafico(struct Producto inventario[], int cantidadesPrecios[][2], int numProductos) {
    char nombre[50] = "";
    int cantidad;
    float precio;
    char buffer[50];

    cleardevice();
    outtextxy(100, 20, "Actualizar Producto");

    outtextxy(100, 60, "Ingrese el nombre del producto a actualizar:");
    rectangle(100, 80, 400, 110);
    capturarTexto(100, 80, 400, 110, nombre);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            outtextxy(100, 120, "Ingrese la nueva cantidad del producto:");
            rectangle(100, 140, 400, 170);
            capturarTexto(100, 140, 400, 170, buffer);
            cantidad = atoi(buffer);

            outtextxy(100, 180, "Ingrese el nuevo precio del producto:");
            rectangle(100, 200, 400, 230);
            capturarTexto(100, 200, 400, 230, buffer);
            precio = atof(buffer);

            inventario[i].cantidad = cantidad;
            inventario[i].precio = precio;

            cantidadesPrecios[i][0] = cantidad;
            cantidadesPrecios[i][1] = (int)(precio * 100);

            outtextxy(100, 400, "Producto actualizado. Presione cualquier tecla para regresar al menu principal.");
            getch();
            return;
        }
    }

    outtextxy(100, 240, "Producto no encontrado.");
    getch();
}

void dibujarBoton(int x1, int y1, int x2, int y2,  char* texto) {
    rectangle(x1, y1, x2, y2);
    outtextxy((x1 + x2) / 2 - textwidth(texto) / 2, (y1 + y2) / 2 - textheight(texto) / 2, texto);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    struct Producto inventario[MAX_PRODUCTS];
    int cantidadesPrecios[MAX_PRODUCTS][2];
    int numProductos = 0;
    int opcion;

    do {
        cleardevice();
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(100, 20, "Menu:");

        dibujarBoton(100, 60, 400, 100, "Mostrar inventario");
        dibujarBoton(100, 120, 400, 160, "Agregar producto");
        dibujarBoton(100, 180, 400, 220, "Actualizar producto");
        dibujarBoton(100, 240, 400, 280, "Salir");

        int x, y;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
            delay(50);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x >= 100 && x <= 400) {
            if (y >= 60 && y <= 100) {
                opcion = 1;
            } else if (y >= 120 && y <= 160) {
                opcion = 2;
            } else if (y >= 180 && y <= 220) {
                opcion = 3;
            } else if (y >= 240 && y <= 280) {
                opcion = 4;
            } else {
                opcion = 0;
            }
        } else {
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                mostrarInventarioGrafico(inventario, numProductos);
                break;
            case 2:
                agregarProductoGrafico(inventario, cantidadesPrecios, &numProductos);
                break;
            case 3:
                actualizarProductoGrafico(inventario, cantidadesPrecios, numProductos);
                break;
            case 4:
                outtextxy(100, 300, "Saliendo del programa...");
                getch();
                break;
            default:
                outtextxy(100, 300, "Opción no válida. Intente de nuevo.");
                getch();
        }
    } while (opcion != 4);

    closegraph();
    return 0;
}

