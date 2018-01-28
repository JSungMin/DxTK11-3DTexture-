#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

namespace _3DTexture
{
	struct FileInfo
	{
	public:
		HANDLE hFind;
		WIN32_FIND_DATA ffd;
	public:
		bool IsFileHandleEmpty()
		{
			if (INVALID_HANDLE_VALUE == hFind)
				return true;
			return false;
		}
	};

	// 이 샘플 렌더러는 기본 렌더링 파이프라인을 인스턴스화합니다.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void LoadTexture();
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }


	private:
		void Rotate(float radians);
	private:
		// 장치 리소스에 대한 캐시된 포인터입니다.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		ID3D11Device3* m_device;

		// 큐브 기하 도형의 Direct3D 리소스입니다.
		//	쉐이더 리소스 객체 Block
		std::vector<ComPtr<ID3D11ShaderResourceView>> m_MRI_texture_vector;
		
		//	Texture Sampler
		ComPtr<ID3D11SamplerState> m_samplerState;
		//	Constant Buffers
		ComPtr<ID3D11Buffer> m_constantBufferNeverChanges;
		ComPtr<ID3D11Buffer> m_constantBufferChangeOnResize;
		ComPtr<ID3D11Buffer> m_constantBufferChangesEveryFrame;
		ComPtr<ID3D11Buffer> m_constantBufferChangesEveryPrim;

		ComPtr<ID3D11InputLayout>	m_inputLayout;
		ComPtr<ID3D11Buffer>		m_vertexBuffer;
		ComPtr<ID3D11Buffer>		m_indexBuffer;
		ComPtr<ID3D11VertexShader>	m_vertexShader;
		ComPtr<ID3D11PixelShader>	m_pixelShader;
		ComPtr<ID3D11Buffer>		m_constantBuffer;

		// 큐브 기하 도형의 시스템 리소스입니다.
		ModelViewProjectionConstantBuffer	m_constantBufferData;
		uint32	m_indexCount;

		// 렌더링 루프에 사용되는 변수입니다.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}

