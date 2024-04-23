#include <iostream>
#include <string>

#include "ipasir.h"

class VariableAllocator {
    unsigned next = 1;

public:
    unsigned allocate() {
        return next++;
    }

    unsigned* allocate(unsigned n) {
        unsigned* result = new unsigned[n];
        for (unsigned i = 0; i < n; i++) {
            result[i] = allocate();
        }
        return result;
    }

    unsigned** allocate(unsigned n, unsigned m) {
        unsigned** result = new unsigned*[n];
        for (unsigned i = 0; i < n; i++) {
            result[i] = new unsigned[m];
            for (unsigned j = 0; j < m; j++) {
                result[i][j] = allocate();
            }
        }
        return result;
    }

};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <npigeons>" << std::endl;
        return 1;
    }

    int npigeons = std::stoi(argv[1]);
    int nholes = npigeons - 1;

    std::cout << "Testing if " << npigeons << " pigeons can be placed in " << nholes << " holes." << std::endl;

    void* solver = ipasir_init();

    VariableAllocator va;
    unsigned** p2h = va.allocate(npigeons, nholes);

    // Each pigeon is placed in at least one hole
    for (int i = 0; i < npigeons; i++) {
        for (int j = 0; j < nholes; j++) {
            ipasir_add(solver, p2h[i][j]);
        }
        ipasir_add(solver, 0);
    }

    // Each hole can only contain one pigeon
    for (int j = 0; j < nholes; j++) {
        for (int i = 0; i < npigeons; i++) {
            for (int k = i + 1; k < npigeons; k++) {
                ipasir_add(solver, -p2h[i][j]);
                ipasir_add(solver, -p2h[k][j]);
                ipasir_add(solver, 0);
            }
        }
    }

    int res = ipasir_solve(solver);

    if (res == 10) {
        std::cout << "Satisfiable." << std::endl;
    } else if (res == 20) {
        std::cout << "Unsatisfiable." << std::endl;
    } else {
        std::cout << "Unknown." << std::endl;
    }

    return 0;
}