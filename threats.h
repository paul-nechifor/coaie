int n_threats = 9;

threat_t possible_threats[3][9] = {
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
            {0, -1, -1, -1, 0},
            {true, false, false, false, true},
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
            {0, 1, 1, 1, 0},
            {true, false, false, false, true},
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

