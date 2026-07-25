/*
** ETIB PROJECT, 2026
** xider
** File description:
** primitive
*/

#include <utility/graphic/primitive.hpp>

namespace utility::graphic
{
	Primitive::Primitive(const std::vector<Mesh> &meshes)
		: Renderable(PoseF(), Color32Bit())
	{
		for (const auto &mesh: meshes) {
			addMesh(mesh);
		}
	}

	void Primitive::addMesh(const Mesh &mesh)
	{
		_meshes.push_back(std::make_shared<Mesh>(mesh));
	}
}	 // namespace utility::graphic