#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include "../GeometryTest/Definitions.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(TestDefinitionsConstructor) {
			std::ifstream in("../../UnitTests/TestDefinitions.txt");
			if (in.is_open() == false) {
				throw std::runtime_error("Cannot open test file.");
			}
			Definitions defs(in);
			Assert::AreEqual(defs.size(), (std::size_t)20);
		}
		TEST_METHOD(TestAddingDefinitions) {
			Definitions defs;
			defs.add("Otvorena otsechka s kraishta A i B", "");
			Assert::AreEqual(defs.size(), (std::size_t)1);			
		}
	};
}
