
#include "test_singleton.hpp"
#include "utility/singleton.hpp"

namespace tests::utility {

struct DummySingleton {
  int value = 42;
};

using DummySingletonType = ::utility::Singleton<DummySingleton>;

TEST_F(TestSingleton, SingletonReturnsSameInstance) {
  DummySingleton &instance1 = DummySingletonType::getInstance();
  DummySingleton &instance2 = DummySingletonType::getInstance();
  EXPECT_EQ(&instance1, &instance2);
}

TEST_F(TestSingleton, SingletonValuePersists) {
  DummySingleton &instance = DummySingletonType::getInstance();
  instance.value = 123;
  DummySingleton &instance2 = DummySingletonType::getInstance();
  EXPECT_EQ(instance2.value, 123);
}

} // namespace tests::utility
