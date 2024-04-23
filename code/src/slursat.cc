#include "util/CNFFormula.h"
#include "trail.h"

bool slursat(size_t nVars, Trail& trail) {
    for (int i = 1; i <= nVars; i++) {
        if (trail.value(Var(i)) == trail.UNASSIGNED) {
            trail.newLevel();
            trail.push(Lit(i, false));
            if (!trail.propagate()) {
                trail.backtrack();
                trail.newLevel();
                trail.push(Lit(i, true));
                if (!trail.propagate()) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "USAGE: ./slur <path/to/dimacs/cnf/formula>" << std::endl;
		return 0;
	}    

	CNFFormula formula(argv[1]);

	std::cout << "Testing if formula " << argv[1] << " can be satisfied by SLUR algorithm." << std::endl;
	
    Trail trail {};
    if (!trail.init(formula)) {
        std::cout << "Formula is UNSAT." << std::endl;
        return 0;
    }

    if (slursat(formula.nVars(), trail)) {
        std::cout << "Formula is SAT." << std::endl;
    } else {
        std::cout << "GAVE UP. Formula definetly not SLUR." << std::endl;
    }

	return 0;
}