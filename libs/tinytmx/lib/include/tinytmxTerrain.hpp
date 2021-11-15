#ifndef TINYTMX_TINYTMXTERRAIN_HPP
#define TINYTMX_TINYTMXTERRAIN_HPP

#include <vector>
#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class to contain the information about every terrain in the
    /// tileset/terraintypes element.
    /// FIXME DEPRECATED since 1.5 (soon to most likely be deleted)
    //-------------------------------------------------------------------------
    class Terrain {
    public:
        // Delete copy constructor.
        Terrain(const Terrain &) = delete;
        // Delete move constructor.
        Terrain(Terrain &&) = delete;
        // Delete copy assignment operator.
        Terrain &operator=(const Terrain &) = delete;
        // Delete move assignment operator.
        Terrain &operator=(Terrain &&) = delete;
        
        Terrain();
        ~Terrain();

        /// Parse a terrain type node.
        void Parse(const tinyxml2::XMLNode *terrainNode);

        /// Get the name of the terrain type.
        [[nodiscard]] const std::string &GetName() const { return name; }

        /// Get the local tile-id of the tile that represents the terrain type visually.
        [[nodiscard]] int GetTileID() const { return tileID; }

        /// Get a set of properties re the terrain type.
        [[nodiscard]] const tinytmx::PropertySet* GetProperties() const { return properties; }

    private:
        int tileID;

        tinytmx::PropertySet* properties;

        std::string name;
    };
}

#endif //TINYTMX_TINYTMXTERRAIN_HPP

