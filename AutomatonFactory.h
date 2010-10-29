#include <stdint.h>
#include "Point.h"
#include "Automaton.h"
#include "SpatialModel.h"

namespace SpatialDB {
    class AutomatonFactory {
        public:
           Automaton& get_automaton();
           AutomatonFactory();
           ~AutomatonFactory();
        protected:
            AutomatonFactory(const AutomatonFactory&);
            AutomatonFactory& operator=(const AutomatonFactory&);
            uint64_t _simulated_id;
            SpatialModel* _spatial_model;
    };
}
