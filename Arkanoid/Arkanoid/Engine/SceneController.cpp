#include "pch.h"
#include "SceneController.h"
#include "GameEngine.h"
#include "Camera.h"

using namespace Engine;

SceneController::SceneController()
	: GameObject( )
{
}


SceneController::~SceneController()
{
}

void SceneController::OnWindowResizeEvent()
{
	GameEngine::Instance()->GetActiveCamera()->CreateWindowSizeDependentResources();
	doOnWindowsResizeEvent();
}


bool SceneController::doRender()
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = GameEngine::Instance()->CommandList();
	std::shared_ptr<DX::DeviceResources> deviceResources = GameEngine::Instance()->DeviceResources();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature = GameEngine::Instance()->RootSignature();
	std::shared_ptr<Camera> currentCamera = GameEngine::Instance()->GetActiveCamera();

	DX::ThrowIfFailed(deviceResources->GetCommandAllocator()->Reset());

	// The command list can be reset anytime after ExecuteCommandList() is called.
	DX::ThrowIfFailed(commandList->Reset(deviceResources->GetCommandAllocator(), nullptr));

	// Set the graphics root signature and descriptor heaps to be used by this frame.
	commandList->SetGraphicsRootSignature(rootSignature.Get());

	// Indicate this resource will be in use as a render target.
	CD3DX12_RESOURCE_BARRIER renderTargetResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(deviceResources->GetRenderTarget(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	commandList->ResourceBarrier(1, &renderTargetResourceBarrier);

	// Record drawing commands.
	D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView = deviceResources->GetRenderTargetView();
	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = deviceResources->GetDepthStencilView();
	commandList->ClearRenderTargetView(renderTargetView, DirectX::Colors::CornflowerBlue, 0, nullptr);
	commandList->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	commandList->OMSetRenderTargets(1, &renderTargetView, false, &depthStencilView);

	// Set the viewport and scissor rectangle.
	D3D12_VIEWPORT viewport = deviceResources->GetScreenViewport();
	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &(currentCamera->GetScissorRect()));


	return true;
	
}

bool SceneController::doLateRender()
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = GameEngine::Instance()->CommandList();
	std::shared_ptr<DX::DeviceResources> deviceResources = GameEngine::Instance()->DeviceResources();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature = GameEngine::Instance()->RootSignature();

	// Indicate that the render target will now be used to present when the command list is done executing.
	CD3DX12_RESOURCE_BARRIER presentResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(deviceResources->GetRenderTarget(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	commandList->ResourceBarrier(1, &presentResourceBarrier);

	DX::ThrowIfFailed(commandList->Close());

	// Execute the command list.
	ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
	deviceResources->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	return true;

}
