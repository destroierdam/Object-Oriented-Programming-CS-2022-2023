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
		TEST_METHOD(TestGettingRandomTerm) {
			std::ifstream in("../../UnitTests/TestDefinitions.txt");
			Definitions defs(in);
			Definitions::Pair term = defs.getRandomTerm();
		}
		TEST_METHOD(TestAddingDefinitionsWithFileStream) {
			Definitions defs;
			std::ifstream file1("../../UnitTests/TestDefinitions.txt");
			defs.add(file1);
			Assert::AreEqual(defs.size(), (std::size_t)20);
		}
		TEST_METHOD(TestAddingDefinitionsWithStringStream) {
			Definitions defs;
			std::stringstream stream("Отворена отсечка - асдасдкйас");
			std::stringstream stream2("Затворена отсечка - явлкеявлкей");
			defs.add(stream);
			defs.add(stream2);
			Assert::AreEqual(defs.size(), (std::size_t)2);
		}
	};
}
