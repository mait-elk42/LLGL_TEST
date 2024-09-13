

#include <iostream>
#include <LLGL/LLGL.h>
#include <LLGL/Utils/VertexFormat.h>
#include <CoreFoundation/CoreFoundation.h>

// Helper function to check if a shading language is supported
bool IsSupported(LLGL::ShadingLanguage lang, std::unique_ptr<LLGL::RenderSystem, LLGL::RenderSystemDeleter> &myRenderer) {
	const auto& supportedLangs = myRenderer->GetRenderingCaps().shadingLanguages;
	return (std::find(supportedLangs.begin(), supportedLangs.end(), lang) != supportedLangs.end());
}

int main() {
	/*************************************************/
	/*				DEFINE THE RENDERER				*/
	/*												*/
		auto Renderer = LLGL::RenderSystem::Load("OpenGL");
	/*************************************************/


	/*************************************************/
	/*				DEFINE THE WINDOW				*/
	/*												*/
		LLGL::WindowDescriptor WindowDescriptor;
		WindowDescriptor.title = "Mujassam Engine";
		WindowDescriptor.size = { 1200, 700 };
		WindowDescriptor.flags = LLGL::WindowFlags::Visible | LLGL::WindowFlags::Resizable;
		std::shared_ptr<LLGL::Window> window = LLGL::Window::Create(WindowDescriptor);
	/*************************************************/


	/*************************************************/
	/*				DEFINE SWAPCHAIN				*/
	/*												*/
		LLGL::SwapChainDescriptor mySwapChainDesc;
		mySwapChainDesc.resolution  = window->GetSize();
		mySwapChainDesc.fullscreen  = false;
		mySwapChainDesc.samples     = 3;
		LLGL::SwapChain* mySwapChain = Renderer->CreateSwapChain(mySwapChainDesc, window);

	/*************************************************/


	/*************************************************/
	/*			DEFINE VERTEX BUFFER DESCRIPTOR		*/
	/*												*/
		LLGL::VertexFormat myVertexFormat;
		myVertexFormat.AppendAttribute({ "position", LLGL::Format::RG32Float });
		myVertexFormat.AppendAttribute({ "color", LLGL::Format::RGBA8UNorm });
		struct MyVertex {
			float   position[2];
			uint8_t color[4];
		};

		MyVertex myVertices[3] = {
			//	|- - - x - - - - - - - - - - - - - - - >//
			//	|					A					//
			//	y				*		*				//
			//	|			*				*			//
			//	|		*						*		//
			//	|	B	*	*	*	*	*	*	*	C	//
			//	v										//

			{ {  0.0f,  0.5f }, {	255,	255,	255,	255	} }, // A
			{ { -0.5f, -0.5f }, {	255,	255,	255,	255	} }, // B
			{ {  0.5f, -0.5f }, {	255,	255,	255,	255	} }, // C
		};
		LLGL::BufferDescriptor		VertexBufferDescriptor;
		VertexBufferDescriptor.size			= sizeof(myVertices);
		VertexBufferDescriptor.bindFlags		= LLGL::BindFlags::VertexBuffer;
		VertexBufferDescriptor.vertexAttribs	= myVertexFormat.attributes;
		LLGL::Buffer* VertexBuffer = Renderer->CreateBuffer(VertexBufferDescriptor, myVertices);
	/*************************************************/


	/*************************************************/
	/*		DEFINE SHADERS {VERTEX AND FRAGMENT}	*/
	/*												*/
		LLGL::ShaderDescriptor VSD = { LLGL::ShaderType::Vertex,   "shader.vert" };
		VSD.vertex.inputAttribs = myVertexFormat.attributes;
		LLGL::Shader* VertexShader   = Renderer->CreateShader(VSD);
		LLGL::Shader* FragmentShader = Renderer->CreateShader({ LLGL::ShaderType::Fragment,   "shader.frag" });
	/*************************************************/


	/*************************************************/
	/*			DEFINE GPIPELINE DESCRIPTOR			*/
	/*												*/
		LLGL::GraphicsPipelineDescriptor				PipeLineDescriptor;
		PipeLineDescriptor.vertexShader						= VertexShader;
		PipeLineDescriptor.fragmentShader					= FragmentShader;
		PipeLineDescriptor.rasterizer.multiSampleEnabled	= false;
		LLGL::PipelineState* myPipeline = Renderer->CreatePipelineState(PipeLineDescriptor);
	/*************************************************/


	/*************************************************/
	/*				DEFINE CMD BUFFER				*/
	/*												*/
		LLGL::CommandBuffer* myCmdBuffer = Renderer->CreateCommandBuffer(LLGL::CommandBufferFlags::ImmediateSubmit);
	/*************************************************/
	
	
	while (window->ProcessEvents() && !window->HasQuit()) {
		myCmdBuffer->Begin();
		myCmdBuffer->SetVertexBuffer(*VertexBuffer);
		myCmdBuffer->BeginRenderPass(*mySwapChain);
		myCmdBuffer->SetViewport(mySwapChain->GetResolution());
		myCmdBuffer->Clear(LLGL::ClearFlags::Color);
		myCmdBuffer->SetPipelineState(*myPipeline);
		myCmdBuffer->Draw(3, 0);
		myCmdBuffer->EndRenderPass();
		myCmdBuffer->End();
		mySwapChain->Present();
	}

	return 0;
}
