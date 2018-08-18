CFLAGS = -Wall -g -std=c11 `pkg-config --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs gtk+-2.0`

Conecta4: conecta4_gtk2.c
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)
