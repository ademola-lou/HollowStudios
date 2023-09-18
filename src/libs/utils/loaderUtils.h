#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
// #define TINYOBJLOADER_USE_MAPBOX_EARCUT
// #define TINYOBJLOADER_USE_DOUBLE
#include "tiny_obj_loader.h"
#include <primitives/Mesh.h>
#include "MathUtils.h"
#include <unordered_map>


typedef MeshPrimitive::Vertex Vertex;

namespace {
    struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    };

    MeshData loadObj(const char* path){
    MeshData meshData;
    std::string inputfile = path;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    tinyobj::attrib_t attribs;
    attribs.vertices = attrib.vertices;
    attribs.normals = attrib.normals;
    attribs.texcoords = attrib.texcoords;
    attribs.colors = attrib.colors;

    size_t j = 0, i = 0;
    for (i; i < attribs.vertices.size(); i+=3) {
        float vx = attribs.vertices[i];
        float vy = attribs.vertices[i+1];
        float vz = attribs.vertices[i+2];

        float red = attribs.colors[i];
        float green = attribs.colors[i+1];
        float blue = attribs.colors[i+2];
        uint32_t col = MathUtils::rgbToHex(red, green, blue);

        float u = attribs.texcoords[j];
        float v = attribs.texcoords[j+1];

        // std::cout << "t " << u << " " << v << std::endl;

        meshData.vertices.push_back({vx, vy, vz, col, u, v});

        j += 2;
    };

    //loop indices for single meshes
    for(auto i : shapes[0].mesh.indices) {
        meshData.indices.push_back(i.vertex_index);
        // std::cout << "f " << i.vertex_index;// << "/" << i.texcoord_index << "/" << i.normal_index << std::endl;
    };

    //  SceneManager::loadScene(meshData.vertices, meshData.indices);
     return meshData;
    };

}