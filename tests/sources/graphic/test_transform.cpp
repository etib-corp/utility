#include "graphic/test_transform.hpp"

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "utility/graphic/model.hpp"
#include "utility/graphic/primitive.hpp"
#include "utility/graphic/transform.hpp"
#include "utility/system_io/file.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

namespace
{
	constexpr float kPi = 3.14159265358979323846f;

	void expectMatrixNear(const glm::mat4 &actual, const glm::mat4 &expected,
						  float tolerance = 1e-5f)
	{
		for (int column = 0; column < 4; ++column) {
			for (int row = 0; row < 4; ++row) {
				EXPECT_NEAR(actual[column][row], expected[column][row],
							tolerance)
					<< "mismatch at column " << column << ", row " << row;
			}
		}
	}
}	 // namespace

TEST_F(TestTransform, IdentityPoseYieldsIdentityMatrix)
{
	expectMatrixNear(poseToMatrix(PoseF()), glm::mat4(1.0f));
}

TEST_F(TestTransform, TranslationIsStoredInTheFourthColumn)
{
	const PoseF pose(PositionF(1.0f, 2.0f, 3.0f), OrientationF());

	expectMatrixNear(
		poseToMatrix(pose),
		glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)));
}

TEST_F(TestTransform, OrientationIsStoredAsRotation)
{
	const float half = std::sin(kPi / 4.0f);
	const PoseF pose(PositionF(), OrientationF(0.0f, half, 0.0f, half));

	expectMatrixNear(
		poseToMatrix(pose),
		glm::rotate(glm::mat4(1.0f), kPi / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
}

TEST_F(TestTransform, ModelMatrixComposesTranslationRotationAndScale)
{
	const float half = std::sin(kPi / 4.0f);
	const PoseF pose(PositionF(1.0f, 2.0f, 3.0f),
					 OrientationF(0.0f, half, 0.0f, half));
	const ScaleF scale(2.0f, 3.0f, 4.0f);

	const glm::mat4 expected =
		glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f))
		* glm::rotate(glm::mat4(1.0f), kPi / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));

	expectMatrixNear(modelMatrix(pose, scale), expected);
}

TEST_F(TestTransform, RenderableModelMatrixMatchesItsPose)
{
	Primitive primitive(std::vector<Mesh> {});
	const PoseF pose(PositionF(4.0f, 5.0f, 6.0f), OrientationF(0.0f, 0.0f, 0.0f, 1.0f));
	primitive.setPose(pose);

	expectMatrixNear(primitive.getModelMatrix(), poseToMatrix(pose));
}

TEST_F(TestTransform, ModelStoresVerticesInLocalSpace)
{
	const std::string obj = "v 1.0 2.0 3.0\n"
							"v 4.0 5.0 6.0\n"
							"v 7.0 8.0 9.0\n"
							"f 1 2 3\n";

	auto asset = std::make_shared<::utility::File>("inline.obj", obj);
	const PoseF pose(PositionF(10.0f, 20.0f, 30.0f), OrientationF());

	Model model(asset, Model::ModelType::OBJ, pose, 0);

	auto meshes = model.getMeshes();
	ASSERT_EQ(meshes.size(), 1u);

	const std::vector<VertexF> &vertices = meshes.front()->getVertices();
	ASSERT_EQ(vertices.size(), 3u);

	// The pose must not be baked into the stored geometry.
	EXPECT_FLOAT_EQ(vertices[0].getPosition().getX(), 1.0f);
	EXPECT_FLOAT_EQ(vertices[0].getPosition().getY(), 2.0f);
	EXPECT_FLOAT_EQ(vertices[0].getPosition().getZ(), 3.0f);
	EXPECT_FLOAT_EQ(vertices[2].getPosition().getX(), 7.0f);
	EXPECT_FLOAT_EQ(vertices[2].getPosition().getY(), 8.0f);
	EXPECT_FLOAT_EQ(vertices[2].getPosition().getZ(), 9.0f);
}
