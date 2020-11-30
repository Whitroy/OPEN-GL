#include "test.h"
#include "im_gui/imgui.h"
namespace test {

	TestMenu::TestMenu(Test*& CurrentTest)
		: m_CurrentTest(CurrentTest) {

	}

	void TestMenu::OnImGuiRender() {
		
		for (auto& test : m_Tests) {
			if(ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}