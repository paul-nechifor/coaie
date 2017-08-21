#!/usr/bin/env python2


def trans(ns, mask, score):
    return ('''\
        {
            {%s},
            {%s},
            %s,
            %s,
        },''') % (
        ', '.join(map(str, ns)),
        ', '.join('true' if x == 'm' else 'false' for x in mask),
        len(ns),
        str(score),
    )


threats = [
    (500000, 'xxxx.', '....m'),
    (500000, '.xxxx', 'm....'),

    (-500000, '.oooox', 'm.....'),
    (-500000, 'xoooo.', '.....m'),

    (-500000, '.oooo', 'm....'),
    (-500000, 'o.ooo', '.m...'),
    (-500000, 'oo.oo', '..m..'),
    (-500000, 'ooo.o', '...m.'),
    (-500000, 'oooo.', '....m'),

    (-50000, '..ooo.', '.m...m'),
    (-50000, '.ooo..', 'm...m.'),
    (-50000, '.oo.o.', 'm..m.m'),
    (-50000, '.o.oo.', 'm.m..m'),

    (50000, '..xxx.', '.m...m'),
    (50000, '.xxx..', 'm...m.'),
    (50000, '.xx.x.', 'm..m.m'),
    (50000, '.x.xx.', 'm.m..m'),

    (100, '.xx.', 'm..m'),
    (100, 'x.x.', '.m.m'),
    (100, '.x.x', 'm.m.'),
    (40, '.x.', 'm.m'),
    (40, '.xx', 'm..'),
    (40, 'xx.', '..m'),

    (-100, '.oo.', 'm..m'),
    (-100, 'o.o.', '.m.m'),
    (-100, '.o.o', 'm.m.'),
    (-100, '.o.', 'm.m'),
    (-100, '.oo', 'm..'),
    (-100, 'oo.', '..m'),

    (1, 'x.', '.m'),
    (1, '.x', 'm.'),
    (1, 'o.', '.m'),
    (1, '.o', 'm.'),
]

w = []
b = []

m = {'.': 0, 'x': -1, 'o': 1}

for score, pattern, mask in threats:
    ns = [m[x] for x in pattern]
    w.append(trans(ns, mask, score))
    ns = [-x for x in ns]
    b.append(trans(ns, mask, score))


print '''int n_threats = %s;

threat_t possible_threats[3][%s] = {
    {
%s
    },
    {
%s
    },
    {
%s
    },
};''' % (
    len(threats),
    len(threats),
    '\n'.join(w),
    '\n'.join('        {},' for x in xrange(len(threats))),
    '\n'.join(b),
)
