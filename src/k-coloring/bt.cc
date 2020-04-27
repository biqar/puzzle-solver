//
// Created by Islam, Abdullah Al Raqibul on 4/23/20.
//

#include "core/base.h"
#include "core/bt.h"

class BtMapColorSolver : public Solver {
public:
    BtMapColorSolver(void *_parameter) {
        BtMapColorSolver::init(_parameter);
    }

    int init(void *_parameter);

    int run();

    void destroy();

private:
    MapColorBase *map_color;
    bool print_graph = false;
};

int BtMapColorSolver::init(void *_parameter) {
    map_color = new MapColorBacktracking(((MapColoringInitParam *)_parameter)->file_name_,
                                         ((MapColoringInitParam *)_parameter)->max_colors_);
    print_graph = ((MapColoringInitParam *)_parameter)->print_graph_;
    return 1;
}

int BtMapColorSolver::run() {
    map_color->do_coloring();
    if(print_graph) map_color->print_colored_map();
    return 1;
}

void BtMapColorSolver::destroy() {
    //
}