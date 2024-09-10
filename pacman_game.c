#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define FIELD_WIDTH 19
#define FIELD_HEIGHT 22
#define DEFAULT_INTERVAL 150 * 1000

typedef enum Item {
    PACMAN = 'c',
    GHOST = 'g',
    WALL = '#',
    POINT = ' ',
    EMPTY_SPACE = 'x',
    GHOST_DOOR = '-'
} Item;

typedef struct Element {
    int x;
    int y;
    Item t;
} Element;

typedef struct Map {
    uint frame;
    Element *map[FIELD_HEIGHT][FIELD_WIDTH];
} Map;

void print_field(Map *m) {
    for(int i = 0; i < FIELD_HEIGHT; i++) {
	for(int j = 0; j < FIELD_WIDTH; j++) {
	    Element *el = m->map[i][j];
	    if (el->t == EMPTY_SPACE) {
		printf(" ");
		continue;
	    }
	    if (el->t == POINT) {
		printf(".");
		continue;
	    }
	    if (el->t == PACMAN) {
		if (m->frame % 2 == 0) {
		    printf("c");
		} else {
		    printf("o");
		}
		continue;
	    }
	    printf("%c", el->t);
	}
	printf("\n");
    }
}

Element *create_element(Item t, int x, int y) {
    Element *el = malloc(sizeof(Element));
    el->t = t;
    el->x = x;
    el->y = y;
    return el;
}

void load_field(
    char *field_bp[FIELD_HEIGHT],
    Element *field[FIELD_HEIGHT][FIELD_WIDTH]
) {
    for(int i = 0; i < FIELD_HEIGHT; i++) {
	for(int j = 0; j < FIELD_WIDTH; j++) {
	    Element *el;
	    switch (field_bp[i][j]) {
		case POINT:
		    el = create_element(POINT, j, i);
		    break;
		case WALL:
		    el = create_element(WALL, j, i);
		    break;
		case EMPTY_SPACE:
		    el = create_element(EMPTY_SPACE, j, i);
		    break;
		case GHOST:
		    el = create_element(GHOST, j, i);
		    break;
		case PACMAN:
		    el = create_element(PACMAN, j, i);
		    break;
		case GHOST_DOOR:
		    el = create_element(GHOST_DOOR, j, i);
		    break;
	    }
	    field[i][j] = el;
	}
    }
}

void clear_field() {
    for(int i = 0; i < FIELD_HEIGHT; i++) {
        printf("\033[A");	    
        printf("\r");
        for(int j = 0; j < FIELD_WIDTH; j++) {
           printf(" ");
        }
        printf("\r");
    }
}

int main(void) {
    char *field_bp[FIELD_HEIGHT] = {
        "###################",
        "#        #        #",
        "# ## ### # ### ## #",
        "# ## ### # ### ## #",
        "#                 #",
        "# ## # ##### # ## #",
        "#    #   #   #    #",
        "#### ### # ### ####",
        "xxx# #       # #xxx",
        "#### # ##-## # ####",
        "       #ggg#       ",
        "#### # ##### # ####",
        "xxx# #       # #xxx",
        "#### # ##### # ####",
        "#        #        #",
        "# ## ### # ### ## #",
        "#  #     c     #  #",
        "## # # ##### # # ##",
        "#    #   #   #    #",
        "# ###### # ###### #",
        "#                 #",
        "###################"
    };

    Map *m = malloc(sizeof(Map));

    load_field(field_bp, m->map);

    while(true) {
	print_field(m);
	usleep(DEFAULT_INTERVAL);
    	clear_field();
	m->frame++;
    }

}
