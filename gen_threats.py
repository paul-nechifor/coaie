#!/usr/bin/env python2

def trans(ns, mask):
    return ('''\
        {
            {%s},
            {%s},
            %s,
        },''') % (
        ', '.join(map(str, ns)),
        ', '.join('true' if x == 'm' else 'false' for x in mask),
        len(ns),
    )


threats = [
    ('xxxx.', '....m'),
    ('.xxxx', 'm....'),

    ('.ooo.', 'm...m'),
    ('.oooox', 'm.....'),
    ('xoooo.', '.....m'),

    ('.xxx.', 'm...m'),
    ('.xx.', 'm..m'),
    ('.x.', 'm.m'),
    ('x.', '.m'),
    ('.x', 'm.'),
    ('o.', '.m'),
    ('.o', 'm.'),
]

w = []
b = []

m = {'.': 0, 'x': -1, 'o': 1}

for pattern, mask in threats:
    ns = [m[x] for x in pattern]
    w.append(trans(ns, mask))
    ns = [-x for x in ns]
    b.append(trans(ns, mask))


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
};
''' % (
    len(threats),
    len(threats),
    '\n'.join(w),
    '\n'.join('        {},' for x in xrange(len(threats))),
    '\n'.join(b),
)
