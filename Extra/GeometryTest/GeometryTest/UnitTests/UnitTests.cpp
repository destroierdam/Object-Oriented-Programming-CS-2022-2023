#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../GeometryTest/Definitions.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestDefinitionsConstructor)
		{
			Definitions defs;
			defs.add("Otvorena otsechka s kraishta A i B", "");
			Assert::AreEqual(defs.size(), (std::size_t)1);			
		}
	};
}
