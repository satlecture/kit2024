extern "C" {
    #include "ipasir.h"
}

#include "util/CNFFormula.h"

class Trail {

    std::vector<Lit> trail; // Trail
    std::vector<unsigned> trail_lim; // Stack of trail limits
    std::vector<uint8_t> val; // Assignment (0 = unassigned, 1 = true, 2 = false)
    std::vector<For> occ; // Occurence list
    int head = 0; // Head of the trail which is not yet propagated

public:
    // value constants
    const uint8_t UNASSIGNED = 0;
    const uint8_t TRUE = 1;
    const uint8_t FALSE = 2;

    Trail() : occ(), val(), trail(), trail_lim() { }

    void clear() {
        occ.clear();
        val.clear();
        trail.clear();
        trail_lim.clear();
    }

    bool init(CNFFormula& formula) {
        clear();
        occ.resize(2*formula.nVars()+2);
        val.resize(formula.nVars()+1);
        trail_lim.push_back(0);
        for (Cl* cls : formula) {
            if (cls->size() == 1 && !push((*cls)[0])) {
                return false;
            }
            for (Lit lit : *cls) {
                occ[lit].push_back(cls);
            }
        }
        return propagate();
    }

    bool propagate() {
        while (head < trail.size()) {
            Lit lit = trail[head];
            head++;
            for (Cl* cls : occ[lit]) {
                Lit unit = Lit();
                for (Lit lit : *cls) {
                    if (val[lit.var()] == TRUE) {
                        break; // clause is satisfied
                    } 
                    else if (val[lit.var()] == UNASSIGNED) {
                        if (unit != 0) {
                            break; // more than one unassigned literal
                        }
                        unit = lit;
                    }
                }
                if (unit != 0 && !push(unit)) {
                    return false;
                }
            }
        }
        return true;
    }

    uint8_t value(Var var) {
        return val[var];
    }

    bool push(Lit lit) {
        uint8_t new_val = lit.sign() ? FALSE : TRUE;
        if (val[lit.var()] != 0) {
            return val[lit.var()] == new_val;
        }
        val[lit.var()] = new_val;
        trail.push_back(lit);
        return true;
    }

    void newLevel() {
        trail_lim.push_back(trail.size());
    }

    void backtrack() {
        if (!trail_lim.empty()) {
            for (int i = trail.size(); i > trail_lim.back(); i--) {
                val[trail[i].var()] = UNASSIGNED;
            }
            trail.resize(trail_lim.back());
            trail_lim.pop_back();
        }
    }

    Lit operator[](int i) {
        return trail[i];
    }

    int size() {
        return trail.size();
    }
};

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

	std::cout << "Testing if formula can be satisfied by SLUR algorithm." << std::endl;
	
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