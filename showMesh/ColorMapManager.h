#pragma once
#include <vtkLookupTable.h>

class ColorMapManager {
public:
    static vtkNew<vtkLookupTable> jet();
};


