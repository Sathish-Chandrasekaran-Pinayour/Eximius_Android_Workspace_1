#include "RenderScript.h"

using namespace android;
using namespace RSC;

static const uint32_t dimX = 7, dimY = 5, dimZ = 3;

void testAllocationCreation(sp<RS> rs, sp<const Element> e, uint32_t nDims) {
    Type::Builder tb(rs, e);
    tb.setX(dimX);
    if (nDims >= 2)
        tb.setY(dimY);
    if (nDims >= 3)
        tb.setZ(dimZ);

    sp<const Type> t = tb.create();
    sp<Allocation> alloc = Allocation::createTyped(rs, t);
}

int main(int , char** )
{
    sp<RS> rs = new RS();

    bool r = rs->init("/system/bin");

    // Test ability to create 1D, 2D and 3D allocations of f16 scalars and
    // vectors
    sp<const Element> half = Element::F16(rs);
    sp<const Element> half2 = Element::F16_2(rs);
    sp<const Element> half3 = Element::F16_3(rs);
    sp<const Element> half4 = Element::F16_4(rs);

    for (uint32_t nDims = 1; nDims <= 3; nDims ++) {
        testAllocationCreation(rs, half, nDims);
        testAllocationCreation(rs, half2, nDims);
        testAllocationCreation(rs, half3, nDims);
        testAllocationCreation(rs, half4, nDims);
    }

    printf("Test successful!");
}
