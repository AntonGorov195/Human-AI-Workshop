#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct E {
    struct E* n;
    float v;
} E;

typedef struct {
    E* s;
} L;

L new() {
    L l = { 0 };
    return l;
}
L from(float* a, int c) {
    L l;
    if(c < 1) {
        return l;
    }
    E* cur = malloc(sizeof(E));
    assert(cur);
    l.s = cur;
    l.s->v = a[0];
    for(int i = 1; i < c; i++) {
        E* n = calloc(1, sizeof(E));
        assert(n);
        n->v = a[i];
        cur->n = n;
        cur = n;
    }
    return l;
}
void put(L* list, float v) {
    E* h = malloc(sizeof(E));
    assert(h);
    h->v = v;
    E* s = list->s;
    list->s = h;
    h->n = s;
}
E* add_far(L* l, float v) {
    if(!l->s) {
        put(l,v);
        return l->s;
    }
    E* t = calloc(1, sizeof(E));
    assert(t);
    E* cur = l->s;
    while(cur->n) {
        cur = cur->n;
    }
    cur->n = t;
    return t;
}
E* get(L* l, float v) {
    E* cur = l->s;
    while(cur) {
        if(cur->v == v) {
            return cur;
        }
        cur = cur->n;
    }
    return NULL;
}
typedef bool(RemF)(E* e, void* d);
size_t rem(L* l, RemF f, void* d) {
    int rem = 0;
    if(!l->s) {
        return;
    }
    E tmp = { 0 };
    tmp.n = l->s;
    E* p = &tmp;
    E* cur = p->n;
    while(cur) {
        if(f(cur, d)) {
            rem++;
            p->n = cur->n;
            E* temp = cur;
            cur = cur->n;
            free(temp);
            continue;
        }
        cur = cur->n;
    }
    return rem;
}
int len(L* l) {
    int c = 0;
    E* cur = l->s;
    while(cur) {
        c++;
        cur = cur->n;
    }
    return c;
}
void end(L* l) {
    E* cur = l->s;
    while(cur) {
        E* tmp = cur;
        cur = cur->n;
        free(tmp);
    }
    l->s = NULL;
}
void out(L* l) {
    printf("List");
    E* cur = l->s;
    while(cur) {
        printf("->%.3f", cur->v);
        cur = cur->n;
    }
    printf("\n");
    return;
}