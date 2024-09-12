/*
 * Test_Window.cpp
 *
 * Copyright (c) 2015 Lukas Hermanns. All rights reserved.
 * Licensed under the terms of the BSD 3-Clause license (see LICENSE.txt).
 */

#include <LLGL/LLGL.h>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <LLGL/Utils/TypeNames.h>
#include <chrono>


// class WindowEventHandler : public LLGL::Window::EventListener
// {
// public:
//     void OnResize(LLGL::Window& sender, const LLGL::Extent2D& size) override
//     {
//         LLGL::Log::Printf("OnResize: %u x %u\n", size.width, size.height);
//     }
// };

using namespace LLGL;

int main(int argc, char **argv)
{
	try {

		Log::RegisterCallbackStd();
		WindowDescriptor windowDesc;

		windowDesc.title    = "Hello World Window";
		windowDesc.flags    = WindowFlags::Visible | WindowFlags::Centered | WindowFlags::Resizable;
		windowDesc.size     = { 500, 500 };

		auto window = Window::Create(windowDesc);

		Input input{ *window };

		// window->AddEventListener(std::make_shared<WindowEventHandler>());

		// try
		// {
			auto renderer = RenderSystem::Load("OpenGL");
			window->SetTitle(std::string(windowDesc.title.c_str()) + " [ " + std::string(renderer->GetName()) + " ]");
			const LLGL::Display* display = LLGL::Display::GetPrimary();
			const std::uint32_t resScale = (display != nullptr ? static_cast<std::uint32_t>(display->GetScale()) : 1u);
			
			LLGL::SwapChainDescriptor swapChainDesc;
			{
				swapChainDesc.resolution    = { 800 * resScale, 600 * resScale };
				swapChainDesc.depthBits     = 0; // We don't need a depth buffer for this example
				swapChainDesc.stencilBits   = 0; // We don't need a stencil buffer for this example
				#if ENABLE_MULTISAMPLING
				swapChainDesc.samples       = 8; // check if LLGL adapts sample count that is too high
				#endif
			}

			// LLGL::SwapChain* swapChain = renderer->CreateSwapChain(swapChainDesc);
			// const auto& info = renderer->GetRendererInfo();
		// }
		// catch (const std::exception& e)
		// {
		// 	Log::Errorf("%s\n", e.what());
		// }

		Extent2D desktopSize;
		if (auto display = Display::GetPrimary())
			desktopSize = display->GetDisplayMode().resolution;

		while (Surface::ProcessEvents() && !window->HasQuit() && !input.KeyPressed(Key::Escape))
		{
			if (input.KeyPressed(Key::LButton))
			{
				
				window->SetTitle("LButton mouse pressed");
			}
			input.Reset();
		}
	}
	catch (const std::exception& e)
	{
		Log::Errorf("%s\n", e.what());
	}

	return 0;
}
