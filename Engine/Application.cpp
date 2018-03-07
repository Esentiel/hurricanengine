#include <Window.h>
#include <ShaderManager.h>
#include <Mesh.h>
#include <Texture.h>

#include <UDP/UDPSocketFactory.h>
#include <UDP/SocketAddressFactory.h>
#include <UDP/SocketUtil.h>


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	// network
	auto socket2 = UDPSocketFactory::CreateUDPSocket(SocketAddressFamily::INET);
	auto sockAddr = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:50000");

	if (socket2 == nullptr)
		return 1;
	if (sockAddr == nullptr)
		return -2;

	auto res = socket2->Bind(sockAddr);

	if (res)
		return res;

	socket2->SetNonBlockingMode(true);







	
	// graphics
	std::array<float, 4> color = { 0.0f, 0.0f, 0.4f , 0.0f };
	Window window(1024, 768, "Rendering!", color);
	ShaderManager shaderMgr("../../Resources/shaders/basicShader");
	shaderMgr.Bind();

	Camera camera(Vertex3(0.5f, 0.5f, -3), 70.0f, (float)window.GetWidth() / (float)window.GetHeight(), 0.01f, 100.0f);

	std::vector<Vertex3> vertecies = { Vertex3(-1.0f, -1.0f, 0.f), Vertex3(0.f, 1.0f, 0.f), Vertex3(1.0f, -1.0f, 0.f) };
	std::vector<Vertex3> vertecies2 = { Vertex3(0.f, 1.0f, 0.f), Vertex3(1.0f, 1.0f, 0.f), Vertex3(1.0f, -1.0f, 0.f) };
	std::vector<Vertex3> vertecies3 = { Vertex3(-1.0f, -1.0f, 0.f), Vertex3(-1.0f, 1.0f, 0.f), Vertex3(0.f, 1.0f, 0.f) };
	std::vector<Vertex2> textureCoords = { Vertex2(0.0f, 1.0f - 0.0f), Vertex2(0.5f, 1.0f - 1.0f), Vertex2(1.0f, 1.0f - 0.0f) };
	Texture * texture = new Texture("../../Resources/textures/player.dds");


	Mesh mesh(vertecies, textureCoords, texture, shaderMgr.GetModelLocID());

	//Mesh mesh2(vertecies2, textureCoords, texture, shaderMgr.GetModelLocID());

	//Mesh mesh3(vertecies3, textureCoords, texture, shaderMgr.GetModelLocID());
	float counter = 0.0f;

	mesh.Scale(Vertex3(0.5f, 0.5f, 1));
	while (window.isActive())
	{
		// networking
		char data[1500];
		SocketAddress socketAddress;

		int bytesReceived = socket2->ReceiveFrom(data, sizeof(data), socketAddress);
		if (bytesReceived> 0)
		{
			std::cout << data << std::endl;
			socket2->SendTo("ok!", 3, socketAddress);
		}

		// gl
		window.Clear();

		window.PollEvents();

		if (window.CheckKeyStatus(Window::KeyCode::KEY_UP, Window::KeyStatus::KEY_PRESS))
		{
			mesh.Move(Vertex3(sin(counter), 0, 0));
			mesh.Rotate(Vertex3(0, 0, sin(counter)));
			mesh.Scale(Vertex3(sin(counter), sin(counter), 0));

			counter += 0.01f;
		}
		//mesh.Scale(Vertex3(sin(counter), sin(counter), 1));
		mesh.Draw(camera);
		//mesh2.Draw();
		//mesh3.Draw();
		window.SwapBuffers();


	}

	return 0;
}