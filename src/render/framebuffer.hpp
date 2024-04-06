#pragma once

#include <unordered_map>

namespace rac {



struct Framebuffer {
    std::unordered_map<GLenum, FramebufferAttachment>
};

}
