#ifndef TINYTMX_TINYTMXTILEOFFSET_HPP
#define TINYTMX_TINYTMXTILEOFFSET_HPP

#include <string>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{
    //-------------------------------------------------------------------------
    /// A class to specify an offset in pixels
    /// to be applied when drawing a tile from the related tileset.
    /// When not present, no offset is applied.
    //-------------------------------------------------------------------------
    class TileOffset
    {
    public:
        TileOffset();

        /// Parses a tileoffset element.
        void Parse(const tinyxml2::XMLNode *tileOffsetNode);

        /// Get the value of the x attribute of the tile offset. Horizontal offset in pixels.
        [[nodiscard]] int GetX() const { return x; }

        /// Get the value of the y attribute of the tile offset. Vertical offset in pixels (positive is down).
        [[nodiscard]] int GetY() const { return y; }

    private:

        // TODO maybe Vector2i
        int x;
        int y;
    };
}

#endif //TINYTMX_TINYTMXTILEOFFSET_HPP

