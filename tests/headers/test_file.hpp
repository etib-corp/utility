#pragma once

#include <gtest/gtest.h>

namespace tests::utility
{
	class TestFile: public ::testing::Test
	{
		protected:
		void SetUp(void) override
		{
		}
		void TearDown(void) override
		{
		}
	};
}	 // namespace tests::utility
