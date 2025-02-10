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