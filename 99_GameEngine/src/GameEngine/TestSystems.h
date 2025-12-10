#pragma once

#include "src/systems/System.h"

#include <iostream> 

namespace Fierce{
	class TestSystem1 :public System{
	public:
		void initSystem(std::string assetDirectory) override { std::cout << "Init System 1" <<"\n"; };
		void linkSystem(System* system) override {};
		void updateSystem() override {};
		void cleanUpSystem() override {};
	};

	class TestSystem2 :public System{
	public:
		void initSystem(std::string assetDirectory) override { std::cout << "Init System 2" << "\n"; };
		void linkSystem(System* system) override {};
		void updateSystem() override {};
		void cleanUpSystem() override {};
	};

	class TestSystem3 :public System{
	public:
		void initSystem(std::string assetDirectory) override { std::cout << "Init System 3" << "\n"; };
		void linkSystem(System* system) override {};
		void updateSystem() override {};
		void cleanUpSystem() override {};
	};
}//end namespace