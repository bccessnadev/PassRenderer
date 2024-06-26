#pragma once

#include "resource.h"

/**
 * @mainpage PassPro Engine Documentation
 *
 * @section intro Introduction
 * Welcome to the documentation for the My WIP custom game engine. This engine is being created
 * alongside a 2D RPG in order to facilitate any engine needs. This documentation provides all the
 * necessary information to understand and use the engine effectively.
 *
 * @section getting_started Getting Started
 * To get started with the engine, you need to understand the basic concepts and
 * managers. Below are some key areas to explore:
 *
 * - ObjectManager: Manages all game objects and handles
 *   their creation, deletion, updating, and rendering.
 *	- Object: Represents an entity in the game world. It can have
 *   multiple components attached to it.
 *	- Object2D: A specialized Object for 2D space, including
 *   position, rotation, and scale transformations.
 *	- Component: Defines a piece of functionality that can be
 *   attached to an Object.
 * - LevelManager: Manages what level is currently loaded.
 *	- ILevel: This is where the game is made. All objects, components, and gameplay are created here.
 * - RenderManager: Acts as an interface with DX11 to facilitate drawing to screen.
 * - PhysicsManager: Custom physics engine. Physics objects can be added via a physics component.
 * - InputManager: Used to bind functions to be called when a specific input is pressed
 *
 * @section usage Using the Engine
 * A program implementing this engine will need to:
 * - Create a LevelManager and levels that the run the game
 * - Continuously update and render the LevelManager with a delta time
 * - Initialized the RenderManager with an hWnd
 * - Call HandleKeyPressed and HandleKeyReleased events on the InputManager
 * 
 * Example of level manager implementation:
 * @code
 *   PlaygroundLevel* Playground = new PlaygroundLevel();
 *   LevelManager* PlaygroundManager = new LevelManager(Playground);
 *
 *   // Time point used to track delta time
 *   high_resolution_clock::time_point PreviousTime = high_resolution_clock::now();
 *
 *   // Main message loop:
 *   while (true) // Want rt update loop, not wait for message // GetMessage(&msg, nullptr, 0, 0))
 *   {
 *       PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
 *
 *       if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
 *       {
 *           TranslateMessage(&msg);
 *           DispatchMessage(&msg);
 *       }
 *
 *       if (msg.message == WM_QUIT)
 *       {
 *           break;
 *       }
 *
 *       // Calculate delta time and cache current time to compare against next frame
 *       const duration<double> DeltaTime = duration_cast<duration<double>>(high_resolution_clock::now() - PreviousTime);
 *       PreviousTime = high_resolution_clock::now();
 *
 *       PlaygroundManager->Update(DeltaTime.count());
 *       PlaygroundManager->Render();
 *   }
 *
 *   delete PlaygroundManager;
 *   delete RenderManager::Get();
 *   delete InputManager::Get();
 * @endcode
 *
 * Example of initializing RenderManager:
 * @code
 * BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
 * {
 *    hInst = hInstance; // Store instance handle in our global variable
 * 
 *    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
 *       CW_USEDEFAULT, 0, ScreenWidth, ScreenHeight, nullptr, nullptr, hInstance, nullptr);
 * 
 *    if (!hWnd)
 *    {
 *       return FALSE;
 *    }
 * 
 *    ShowWindow(hWnd, nCmdShow);
 *    UpdateWindow(hWnd);
 *     
 *    // Render manager init
 *    RenderManager::Initialize(hWnd);
 *   
 *    return TRUE;
 * }
 * @endcode
 * 
 * Example of updating InputManager:
 * @code
 * LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 * {
 *     switch (message)
 *     {
 *     case WM_KEYDOWN:
 *     {
 *         if (InputManager* IM = InputManager::Get())
 *         {
 *             IM->HandleKeyPressed((unsigned int)wParam);
 *         }
 *         break;
 *     }
 *     case WM_KEYUP:
 *     {
 *         if (InputManager* IM = InputManager::Get())
 *         {
 *             IM->HandleKeyReleased((unsigned int)wParam);
 *         }
 *         break;
 * @endcode
 * 
 * @subsection creating_objects Creating Objects
 * Objects can be created in a child class of Level. Objects can be created with a variety
 * of components attached to them. These components should be initialized and added to the object
 * before the object is registered with the ObjectManager.
 * Here is an example of an object being created in the InitializeLevel function:
 * @code
 *  PhysicsDummy = new Object2D(Vector2(0.f,-10.f), 0.f, Vector2(5.f, 5.f), "Dummy");
 *  PhysicsComponent2D* PhysicsComponentB = new PhysicsComponent2D(PhysicsDummy, new BoxCollider2D(PhysicsDummy));
 *  PhysicsComponentB->SetDebugDraw(true);
 *  PhysicsComponentB->SetMass(2.f);
 *  PhysicsDummy->AddComponent(PhysicsComponentB);
 *  PhysicsDummy->AddComponent(new MovementComponent2D(PhysicsDummy, 1));
 *  PhysicsDummy->Priority = 2;
 *  Objects->AddObject(PhysicsDummy);
 * @endcode
 */
