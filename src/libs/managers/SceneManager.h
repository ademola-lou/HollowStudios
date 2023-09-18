#pragma once

#include <iostream>
#include <vector>
#include <primitives/Mesh.h>
#include <utils/loaderUtils.h>
typedef MeshPrimitive::Mesh Mesh;
// typedef MeshPrimitive::Vertex Vertex;
typedef MeshPrimitive::Vertex Vertex;
typedef MeshPrimitive::Box Box;

namespace SceneManager {
    void loadScene(std::vector<Vertex> vt, std::vector<uint16_t> ind);

    namespace {
        std::vector<Mesh> meshes_heirarchy;
        
        void loadDemoScene1(){
            const size_t n = 5;
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    for(size_t k = 0; k < n; k++) {
                        Box mesh("box", 1, 1, 1);
                        mesh.setPos(i*8, j*8, k*8);
                        meshes_heirarchy.push_back(mesh);
                    }
                }
            }
        };

        void loadDemoScene2(){
            auto meshData = loadObj("bird.obj");
            loadScene(meshData.vertices, meshData.indices);
        };

        void loadDemoScene3(){

//             v -1.000000 0.995356 0.096263
// v 1.000000 0.995356 0.096263
// v -1.000000 -0.995356 -0.096263
// v 1.000000 -0.995356 -0.096263
// vn -0.0000 0.0963 -0.9954
// vt 0.000000 0.000000
// vt 1.000000 0.000000
// vt 1.000000 1.000000
// vt 0.000000 1.000000

            Vertex vertices[] = {
                {-1.000000, 0.995356, 0.096263, 0xFF, 0.000000, 0.000000},
                {1.000000, 0.995356, 0.096263, 0xFF, 1.000000, 0.000000},
                {-1.000000, -0.995356, -0.096263, 0xFF, 1.000000, 1.000000},
                {1.000000, -0.995356, -0.096263, 0xFF, 0.000000, 1.000000}
            };
            uint16_t indices[] = {
                0, 1, 2,
                1, 3, 2
            };

            Mesh mesh;
            mesh.create("loadedMesh", vertices, indices, sizeof(vertices), sizeof(indices));
            meshes_heirarchy.push_back(mesh);
        }
    };


    void loadDemoScene(int scene_num = 1){
        switch(scene_num) {
            case 1:
                loadDemoScene1();
                break;
            case 2:
                loadDemoScene2();
                break;
        }
    }
    void loadScene(std::vector<Vertex> vt, std::vector<uint16_t> ind){
        Vertex vertices[vt.size()];
        uint16_t indices[ind.size()];
        
        std::copy(vt.begin(), vt.end(), vertices);
        
        std::copy(ind.begin(), ind.end(), indices);

        Mesh mesh;
        mesh.create("loadedMesh", vertices, indices, sizeof(vertices), sizeof(indices));
        mesh.setPos(0, 4, 0);
        meshes_heirarchy.push_back(mesh);
    }
    void update(){
        for(auto mesh : meshes_heirarchy) {
            mesh.render();
        }
    }

    void clean(){
        for(auto mesh : meshes_heirarchy) {
            mesh.dispose();
        }
    }
}