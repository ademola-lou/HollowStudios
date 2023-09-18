#pragma once
#include <SDL2/SDL.h>
#include <bx/math.h>
#include <iostream>

namespace CamController {
    struct FirstPersonControls {
        int prevMouseX = 0;
        int prevMouseY = 0;
        float speed = 0.001f;
        float camYaw = 0.f;
        float camPitch = 0.f;
        float camRoll = 0.f;
        float zoom = 1.f;
        bx::Vec3 forward = { 0.0f, 0.0f, 0.0f };
        bx::Vec3 right = { 0.0f, 0.0f, 0.0f };
        bx::Vec3 up = { 0.0f, 0.0f, 0.0f };
        const bx::Vec3 at  = { 0.0f, 0.0f, 0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, -zoom };

        bx::Vec3 m_at = { 0.0f, 0.0f, 0.0f };
        bx::Vec3 m_up = { 0.0f, 0.0f, 0.0f };

        float view[16];
        int controlReadyFlag = 0;

        void init(int mouseX, int mouseY){
            const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
            if((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
            {
                int deltaX = mouseX - prevMouseX;
                int deltaY = mouseY - prevMouseY;
                camYaw += float(-deltaX) * speed;
                camPitch -= float(-deltaY) * speed;

                forward = { 
                    bx::cos(camPitch) * bx::sin(camYaw), 
                    bx::sin(camPitch),
                    bx::cos(camPitch) * bx::cos(camYaw) 
                };
                right = { 
                    bx::sin(camYaw - bx::kPiHalf),
                    0.0f,
                    bx::cos(camYaw - bx::kPiHalf)
                };
                up = bx::cross(right, forward);
                controlReadyFlag = 1;
            }
            prevMouseX = mouseX;
            prevMouseY = mouseY;
        }

        float * update(){
            if(controlReadyFlag == 1) {
                m_at = bx::add(eye, forward);
                m_up = bx::cross(right, forward);
                bx::mtxLookAt(view, eye, m_at, m_up);
            }else{
                //defualt view
                bx::mtxLookAt(view, eye, at);
            }
            
            return view;
        }
    };

    struct OrbitControls {

    };
}