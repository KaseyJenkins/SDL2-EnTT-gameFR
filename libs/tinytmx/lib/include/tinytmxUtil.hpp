#ifndef TINYTMX_TINYTMXUTIL_HPP
#define TINYTMX_TINYTMXUTIL_HPP

#include <string>

namespace tinytmx::Util
{
        /// Trim both leading and trailing whitespace from a string.
        void Trim(std::string &str);

        /// Decode a base-64 encoded string.
        std::string DecodeBase64(const std::string &str);

        /// Decompress a gzip encoded byte array.
        char* DecompressGZIP(const char *data, uint32_t dataSize, uint32_t expectedSize);
}

#endif //TINYTMX_TINYTMXUTIL_HPP

