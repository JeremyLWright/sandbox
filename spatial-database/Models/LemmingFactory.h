#include <stdint.h>
#include "Point.h"
#include "Lemming.h"
#include "SpatialModel.h"

namespace SpatialDB {
    class LemmingFactory {
        public:
           Lemming& get_lemming();
           LemmingFactory();
           ~LemmingFactory();
        protected:
            LemmingFactory(const LemmingFactory&);
            LemmingFactory& operator=(const LemmingFactory&);
            uint64_t _simulated_id;
            SpatialModel* _spatial_model;
    };
}
