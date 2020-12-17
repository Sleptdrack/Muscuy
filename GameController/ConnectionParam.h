#pragma once  
using namespace System;
namespace SalesController {
	[Serializable]
	public ref class ConnectionParam
	{
	public:
		property String^ server;
		property String^ database;
		property String^ user;
		property String^ password;
	};
}
