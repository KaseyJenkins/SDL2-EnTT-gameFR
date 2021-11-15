#ifndef TINYTMX_TINYTMXWANGCOLOR_HPP
#define TINYTMX_TINYTMXWANGCOLOR_HPP

#include <string>
#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLElement;
}

namespace tinytmx {

    //-------------------------------------------------------------------------
    /// A class to store the information about a color that can be used to define
    /// the corner and/or edge of a Wang tile.
    //-------------------------------------------------------------------------

    class WangColor {
    public:

        // Delete copy constructor.
        WangColor(const WangColor &) = delete;
        // Delete move constructor.
        WangColor(WangColor &&) = delete;
        // Delete copy assignment operator.
        WangColor &operator=(const WangColor &) = delete;
        // Delete move assignment operator.
        WangColor &operator=(WangColor &&) = delete;


        WangColor();
        ~WangColor();

        void Parse(const tinyxml2::XMLElement *wangColorElement);

        /// Get the name of this color.
        [[nodiscard]] const std::string &GetName() const { return name; }

        /// Get the color.
        [[nodiscard]] const Color& GetColor() const noexcept { return color; } // FIXME check all noexcept functions

        /// Get the tile ID  of the tile representing this color.
        [[nodiscard]] int GetTileID() const { return tileID; }

        /// Get the relative probability that this color is chosen over others in case of multiple options.
        /// Defaults to 0;
        [[nodiscard]] float GetProbability() const { return probability; }

        /// Get a set of properties re the wangcolor.
        [[nodiscard]] const tinytmx::PropertySet* GetProperties() const { return properties; }

    private:
        int tileID;
        float probability;
        tinytmx::Color color;
        tinytmx::PropertySet* properties;
        std::string name;
    };

}
#endif //TINYTMX_TINYTMXWANGCOLOR_HPP
