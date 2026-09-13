#pragma once

#include <gtest/gtest.h>

#include <utility/ressource_provider.hpp>
#include <utility/system_io/default_system_io.hpp>

namespace tests::utility
{
	class TestRessourceProvider: public ::testing::Test
	{
		protected:
		utility::DefaultSystemIO _systemIO;
		utility::RessourceProvider _provider { _systemIO };
	};
}	 // namespace tests::utility
