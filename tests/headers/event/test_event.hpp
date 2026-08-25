#pragma once

#include <gtest/gtest.h>

namespace tests::utility::event
{
	class TestEvent: public ::testing::Test
	{
		protected:
		void SetUp(void) override
		{
		}
		void TearDown(void) override
		{
		}
	};
}	 // namespace tests::utility::event
