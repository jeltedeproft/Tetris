#ifndef CELL_H_
#define CELL_H_

/*
 * Deze groepen representeren nu de verschillende mogelijke blokken
 */
enum Group {
	O, I, S, Z, L, J, T,H    // H symboliseert een leeg vakje (zwarte kleur)
};

/*
 * In fase 3 is een levende cel een nog bewegend blokje, een dode cell is een er een die deel uitmaakt van de gevorme structuur, en een empty state is een lege cell
 */
enum State {
	ALIVE, DEAD, EMPTY
};

/*
 * Bij fase 3 voeg ik hier een extra enum toe, die de huidige orientatie voorstelt van het blokje waar deze cel deel van uitmaakt.
 */
enum Orientation {
	UP, RIGHT, DOWN, LEFT
};

/*
 * Een cel wordt voorgesteld als een struct die tot een bepaalde groep hoort
 * en een bepaalde staat heeft (levend of dood).
 */
struct Cell {
	enum Group group;
	enum State state;
	enum Orientation orientation;
};

/*
 * De struct blokje representeerd een blokje en word opgeslagen aan de hand van slechts 2 integers, het rotatiecentrum
 */
struct Blokje {
	int rotatiecentrum_x;
	int rotatiecentrum_y;
};


#endif /* CELL_H_ */
