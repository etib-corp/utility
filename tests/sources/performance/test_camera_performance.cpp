#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>

#include "utility/graphics/camera.hpp"

TEST(PerformanceCamera, ViewRayAndMovementOperationsCompleteWithinBudget) {
  using Clock = std::chrono::steady_clock;

  constexpr std::uint32_t iterations = 250000;
  utility::graphics::Camera<float> camera;
  utility::math::Vector<float, 3> accumulator{0.0F, 0.0F, 0.0F};

  const auto start = Clock::now();
  for (std::uint32_t i = 0; i < iterations; ++i) {
    const float ndcX = static_cast<float>((i % 200U) - 100U) / 100.0F;
    const float ndcY = static_cast<float>((i % 100U) - 50U) / 50.0F;

    const auto ray = camera.viewRay(ndcX, ndcY);
    accumulator += ray.pointAt(1.0F);

    camera.move({0.0005F, -0.00025F, 0.0F});
    if ((i % 10000U) == 0U) {
      const auto position = camera.getPosition();
      camera.lookAt(position +
                    utility::math::Vector<float, 3>{0.0F, 0.0F, -1.0F});
    }
  }
  const auto end = Clock::now();

  const auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  volatile float sink = accumulator[0] + accumulator[1] + accumulator[2];
  (void)sink;

  RecordProperty("camera_view_ray_move_ops_ms", static_cast<int>(elapsed));
  EXPECT_LT(elapsed, 5000);
}
