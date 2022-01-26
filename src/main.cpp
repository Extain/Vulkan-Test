#include "app.h"


#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    Engine::App app{};

    try
    {
        app.run();
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }

    system("pause");
    return EXIT_SUCCESS;
}

/*
    Each stage takes in input, and converts it to resemble the final image.
    
    Input Assembler - Takes in input and assembles them into geometry
                    |
                   \ /
    Vertex Shader - Processes each vertex individually and performs transformations
                    |
                   \ /
    Rasterization - breaks geometry into fragments for each pixel or triangle overlaps
                    |
                   \ /
    Fragment Shader - processes each fragment individually and outputs values such as colors using interpolated data for lighting, textures, and normals.
                    |
                   \ /
    Color Blending - applies operations to mix values that exist on the same pixel in the final image.
*/