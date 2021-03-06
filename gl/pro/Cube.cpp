//
// Created by mnutec on 2021/2/1.
//

#include "Cube.h"

GLM::Cube::Cube() {
     mesh = {
            {{-1, -1, 1,  1}, {0, 0}, {1.0f, 0.2f, 0.2f}, 1},
            {{1,  -1, 1,  1}, {0, 1}, {0.2f, 1.0f, 0.2f}, 1},
            {{1,  1,  1,  1}, {1, 1}, {0.2f, 0.2f, 1.0f}, 1},
            {{-1, 1,  1,  1}, {1, 0}, {1.0f, 0.2f, 1.0f}, 1},
            {{-1, -1, -1, 1}, {0, 0}, {1.0f, 1.0f, 0.2f}, 1},
            {{1,  -1, -1, 1}, {0, 1}, {0.2f, 1.0f, 1.0f}, 1},
            {{1,  1,  -1, 1}, {1, 1}, {1.0f, 0.3f, 0.3f}, 1},
            {{-1, 1,  -1, 1}, {1, 0}, {0.2f, 1.0f, 0.3f}, 1},
    };

     indices={{0,1,2,3},{7,6,5,4},{0,4,5,1},{1,5,6,2},{2,6,7,3},{3,7,4,0}};
}
