int n_threats = 23;

threat_t possible_threats[3][23] = {
    {
        {
            {-1, -1, -1, -1, 0},
            {false, false, false, false, true},
            5,
        },
        {
            {0, -1, -1, -1, -1},
            {true, false, false, false, false},
            5,
        },
        {
            {0, 1, 1, 1, 1, -1},
            {true, false, false, false, false, false},
            6,
        },
        {
            {-1, 1, 1, 1, 1, 0},
            {false, false, false, false, false, true},
            6,
        },
        {
            {0, 1, 1, 1, 1},
            {true, false, false, false, false},
            5,
        },
        {
            {1, 0, 1, 1, 1},
            {false, true, false, false, false},
            5,
        },
        {
            {1, 1, 0, 1, 1},
            {false, false, true, false, false},
            5,
        },
        {
            {1, 1, 1, 0, 1},
            {false, false, false, true, false},
            5,
        },
        {
            {1, 1, 1, 1, 0},
            {false, false, false, false, true},
            5,
        },
        {
            {0, 0, 1, 1, 1, 0},
            {false, true, false, false, false, true},
            6,
        },
        {
            {0, 1, 1, 1, 0, 0},
            {true, false, false, false, true, false},
            6,
        },
        {
            {0, 1, 1, 0, 1, 0},
            {true, false, false, true, false, true},
            6,
        },
        {
            {0, 1, 0, 1, 1, 0},
            {true, false, true, false, false, true},
            6,
        },
        {
            {0, -1, -1, -1, 0},
            {true, false, false, false, true},
            5,
        },
        {
            {0, -1, -1, 0, -1, 0},
            {true, false, false, true, false, true},
            6,
        },
        {
            {0, -1, 0, -1, -1, 0},
            {true, false, true, false, false, true},
            6,
        },
        {
            {0, -1, 0, -1, 0},
            {true, false, true, false, true},
            5,
        },
        {
            {0, -1, -1, 0},
            {true, false, false, true},
            4,
        },
        {
            {0, -1, 0},
            {true, false, true},
            3,
        },
        {
            {-1, 0},
            {false, true},
            2,
        },
        {
            {0, -1},
            {true, false},
            2,
        },
        {
            {1, 0},
            {false, true},
            2,
        },
        {
            {0, 1},
            {true, false},
            2,
        },
    },
    {
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
    },
    {
        {
            {1, 1, 1, 1, 0},
            {false, false, false, false, true},
            5,
        },
        {
            {0, 1, 1, 1, 1},
            {true, false, false, false, false},
            5,
        },
        {
            {0, -1, -1, -1, -1, 1},
            {true, false, false, false, false, false},
            6,
        },
        {
            {1, -1, -1, -1, -1, 0},
            {false, false, false, false, false, true},
            6,
        },
        {
            {0, -1, -1, -1, -1},
            {true, false, false, false, false},
            5,
        },
        {
            {-1, 0, -1, -1, -1},
            {false, true, false, false, false},
            5,
        },
        {
            {-1, -1, 0, -1, -1},
            {false, false, true, false, false},
            5,
        },
        {
            {-1, -1, -1, 0, -1},
            {false, false, false, true, false},
            5,
        },
        {
            {-1, -1, -1, -1, 0},
            {false, false, false, false, true},
            5,
        },
        {
            {0, 0, -1, -1, -1, 0},
            {false, true, false, false, false, true},
            6,
        },
        {
            {0, -1, -1, -1, 0, 0},
            {true, false, false, false, true, false},
            6,
        },
        {
            {0, -1, -1, 0, -1, 0},
            {true, false, false, true, false, true},
            6,
        },
        {
            {0, -1, 0, -1, -1, 0},
            {true, false, true, false, false, true},
            6,
        },
        {
            {0, 1, 1, 1, 0},
            {true, false, false, false, true},
            5,
        },
        {
            {0, 1, 1, 0, 1, 0},
            {true, false, false, true, false, true},
            6,
        },
        {
            {0, 1, 0, 1, 1, 0},
            {true, false, true, false, false, true},
            6,
        },
        {
            {0, 1, 0, 1, 0},
            {true, false, true, false, true},
            5,
        },
        {
            {0, 1, 1, 0},
            {true, false, false, true},
            4,
        },
        {
            {0, 1, 0},
            {true, false, true},
            3,
        },
        {
            {1, 0},
            {false, true},
            2,
        },
        {
            {0, 1},
            {true, false},
            2,
        },
        {
            {-1, 0},
            {false, true},
            2,
        },
        {
            {0, -1},
            {true, false},
            2,
        },
    },
};
