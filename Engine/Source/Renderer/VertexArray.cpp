#include <PCH.h>

#include "VertexArray.h"

namespace PetrolEngine {

	VertexArray* VertexArray::create(RRC creator) {
		return creator.newVertexArray();
	}
}