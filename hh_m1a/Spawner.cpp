#include "Spawner.h"
Spawner::Spawner(int x, int y, int limit, int delay) {
	Spawner::x = x;
	Spawner::y = y;
	Spawner::limit = limit;
	Spawner::delay = delay;
}

void Spawner::update(Combat* c, list<Box*> boxes, list<Platform*> platforms) {
	if (crabs.size() < limit) spawn_crab();
	update_crabs(c, boxes, platforms);
	kicked_collision();
	remove_inactive_crabs();
}

void Spawner::update_crabs(Combat* mc, list<Box*> boxes, list<Platform*> platforms) {
	for (Crab* c : crabs) c->update(mc, boxes, platforms);
}

void Spawner::kicked_collision() {
	for (Crab* c : crabs)
		for (Crab* k : crabs)
			if (c != k && c->kicked && !k->kicked && c->collides(k)) {
				k->durability = 0;
				k->drop = true;
			}
}

void Spawner::spawn_crab() {
	if (counter++ > delay) {
		crabs.add(new Crab(x, y));
		counter = 0;
	}
}

void Spawner::remove_inactive_crabs() {
	for (Crab* c : crabs) if (!c->active) { crabs.remove(c); break; }
}

void Spawner::draw_crabs(HDC context) {
	for (Crab* c : crabs) {
		c->draw(context);
		c->draw_bullets(context);
	}
}
