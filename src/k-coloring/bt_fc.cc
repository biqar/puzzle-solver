//
// Created by Islam, Abdullah Al Raqibul on 4/23/20.
//

#include "core/base.h"
#include "core/bt_fc.h"

class BtFcMapColorSolver : public Solver {
public:
    BtFcMapColorSolver(void *_parameter) {
        BtFcMapColorSolver::init(_parameter);
    }

    int init(void *_parameter);

    int run();

    void destroy();

private:
    MapColorBase *map_color;
    bool print_graph = false;
};

int BtFcMapColorSolver::init(void *_parameter) {
    map_color = new MapColorBacktrackingFC(((MapColoringInitParam *)_parameter)->file_name_,
                                            ((MapColoringInitParam *)_parameter)->max_colors_);
    print_graph = ((MapColoringInitParam *)_parameter)->print_graph_;
    return 1;
}

int BtFcMapColorSolver::run() {
    map_color->do_coloring();
    if(print_graph) map_color->print_colored_map();
    return 1;
}

void BtFcMapColorSolver::destroy() {
    //
}