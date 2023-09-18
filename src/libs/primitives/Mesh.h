#pragma once

#include <iostream>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <memory>
#include <vector>
#include <utils/MathUtils.h>
#include <shaders/Materials.h>

typedef MathUtils::Vec3<float> Vec3;

namespace MeshPrimitive {
    namespace {
        bgfx::ShaderHandle loadShader(const char* _name) {
            char* data = new char[2048];
            std::ifstream file;
            size_t fileSize;
            file.open(_name);
            if(file.is_open()) {
                file.seekg(0, std::ios::end);
                fileSize = file.tellg();
                file.seekg(0, std::ios::beg);
                file.read(data, fileSize);
                file.close();
            }
            const bgfx::Memory* mem = bgfx::copy(data,fileSize+1);
            mem->data[mem->size-1] = '\0';
            bgfx::ShaderHandle handle = bgfx::createShader(mem);
            bgfx::setName(handle, _name);
            return handle;
        }
    }

    struct Vertex {
        float x, y, z;
        uint32_t m_abgr;
        float u, v;

        static void init() {
            // start the attribute declaration
            ms_decl
                .begin()
                // Has three float values that denote position
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                // and a uint8 color value that denotes color
                .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
                // add texcoord
                .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
                .end();
        };

        static bgfx::VertexLayout ms_decl;
    };
    bgfx::VertexLayout Vertex::ms_decl;
    typedef Materials::Material Material;
    struct Mesh {
        Vertex* vertices;
        const uint16_t* indices;
        const char* name;
        size_t numVertices;
        size_t numIndices;
        std::shared_ptr<Material> material = std::make_shared<Material>();
        Vec3 position;

    void create(const char* nm, Vertex* vt, const uint16_t* ind, const size_t& numV, const size_t& numI){
        Vertex::init();
        name = nm;
        vertices = vt;
        indices = ind;
        numVertices = numV;
        numIndices = numI;
        setBuffer();
        material->create();
    }
    void setBuffer(){
        m_vbh = bgfx::createVertexBuffer(
            bgfx::copy(vertices, numVertices),
            Vertex::ms_decl
        );

        m_ibh = bgfx::createIndexBuffer(
            bgfx::copy(indices, numIndices)
        );
    }
    int setPos(const Vec3& pos){
        position = pos;
        return 0;
    }
    int setPos(const float& x, const float& y, const float& z){
        position = Vec3(x, y, z);
        return 0;
    }
    
    void render(){
        float mtx[16];
        float ang = bx::kPi;
        bx::mtxRotateY(mtx, ang);

        // position x,y,z
        mtx[12] = position.x;
        mtx[13] = position.y;
        mtx[14] = position.z;

        // Set model matrix for rendering.
        bgfx::setTransform(mtx);

        bgfx::setVertexBuffer(0, m_vbh);
        bgfx::setIndexBuffer(m_ibh);

        uint64_t state = 0
                | BGFX_STATE_WRITE_R
                | BGFX_STATE_WRITE_G
                | BGFX_STATE_WRITE_B
                | BGFX_STATE_WRITE_A
                | BGFX_STATE_WRITE_Z
                | BGFX_STATE_DEPTH_TEST_LESS
                | BGFX_STATE_MSAA
                ;
        bgfx::setState(state);
        // bgfx::setState(BGFX_STATE_DEFAULT);
        material->update();
    }
    
    void setMaterial(const Material& mat){
        material = std::make_shared<Material>(mat);
    }

    void dispose(){
        bgfx::destroy(m_vbh);
        bgfx::destroy(m_ibh);
        material->dispose();
    }

    private:
        bgfx::VertexBufferHandle m_vbh;
        bgfx::IndexBufferHandle m_ibh;
    };

    struct Plane : Mesh {
        Plane(const char* nm, const float& width, const float& height, const float& depth){
            Vertex vertices[] = {
                {-width, height, depth, 0xff0000ff},
                {width, height, depth, 0xff0000ff},
                {width, -height, depth, 0xff0000ff},
                {-width, -height, depth, 0xff0000ff}
            };
            uint16_t indices[] = {0, 1, 2, 0, 2, 3};
            create(nm, vertices, indices, sizeof(vertices), sizeof(indices));
        }
    };

    struct Box : Mesh {
        Box(const char* nm, const float& width, const float& height, const float& depth){
            Vertex vertices[] = {
                {-width, height, depth, 0xff000000}, {width, height, depth, 0xff0000ff},
                {-width, -height, depth, 0xff00ff00}, {width, -height, depth, 0xff00ffff},
                {-width, height, -depth, 0xffff0000}, {width, height, -depth, 0xffff00ff},
                {-width, -height, -depth, 0xffffff00}, {width, -height, -depth, 0xffffffff},
            };
            uint16_t indices[] = {
                0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
                1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
            };
            create(nm, vertices, indices, sizeof(vertices), sizeof(indices));
        }
    };

    struct Cone : Mesh {
        Cone(const char * nm, const float& radius, const float& height, const float& depth){
            Vertex vertices[] = {
                {0, height, 0, 0xff0000ff},
                {radius, -height, depth, 0xff0000ff},
                {-radius, -height, depth, 0xff0000ff},
                {radius, -height, -depth, 0xff0000ff},
                {-radius, -height, -depth, 0xff0000ff}
            };
            uint16_t indices[] = {
                0, 1, 2,
                0, 3, 4,
                0, 1, 3,
                0, 2, 4,
                1, 2, 3,
                2, 3, 4
            };
            create(nm, vertices, indices, sizeof(vertices), sizeof(indices));
        }
    };
};